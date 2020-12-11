// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "EnemyManager.hpp"
#include "Enemies.hpp"
#include "Graphics.hpp"
#include "Cells.hpp"
#include "Landscape.hpp"
#include "PropsManager.hpp"
#include "Bullet.hpp"

#include <algorithm>

namespace detail
{
	namespace TD = TowerDefence;
	bool checkByType(TD::RouteType type, std::shared_ptr<TD::Cell> cell)
	{
		if (!cell)
			return false;

		if (type == TD::RouteType::Air)
			return typeid(*cell) != typeid(TD::Mountain);
		else if (auto field = std::dynamic_pointer_cast<TD::Field>(cell); type == TD::RouteType::Heavy && field)
			return !field->getBuilding() || (field->getBuilding() && typeid(*field->getBuilding()) != typeid(TD::Tower));
		else if (type == TD::RouteType::Light && field)
			return !field->getBuilding();

		return false;
	}
}

namespace TowerDefence
{
	std::shared_ptr<Route> EnemyManager::createRoute(const PosF& from, RouteType routeType)
	{
		PosF to = m_castle ? m_castle->getPos() : from;

		std::map<PosF, bool> used;
		std::map<PosF, PosF> prev;
		std::queue<PosF>     queue;

		auto wasUsed = [&](const PosF& coord) { return used.find(coord) != std::end(used); };

		auto tryAdd = [&](const PosF& cur, const PosF& coord)
		{
			if (auto cell = sLandscape->getCell(coord); sLandscape->isInField(coord) &&
				!wasUsed(coord) &&
				cell &&
				(coord == to || detail::checkByType(routeType, cell))
				)
			{
				queue.push(coord);

				used.emplace(coord, true);

				prev.emplace(coord, cur);
			}
		};

		queue.push(from);
		used.emplace(from, true);
		prev.insert({ from, { -1, -1 } });
		while (!queue.empty())
		{
			auto cur = queue.front();
			queue.pop();

			tryAdd(cur, { cur.x - 1, cur.y }); // left
			tryAdd(cur, { cur.x    , cur.y + 1 }); // below
			tryAdd(cur, { cur.x + 1, cur.y }); // right
			tryAdd(cur, { cur.x    , cur.y - 1 }); // above
		}

		if (prev.find(to) == std::end(prev))
			return { };

		PosF cur = to;
		MyVector<PosF> revPath;
		while (prev.at(cur) != PosF{ -1, -1 })
		{
			revPath.push_back(cur);
			cur = prev.at(cur);
		}

		std::queue<PosF> path;
		for (auto it = std::rbegin(revPath); it != std::rend(revPath); ++it)
			path.push(*it);

		return std::make_shared<Route>(to, std::move(path));
	}
	
	void EnemyManager::createRoutes(const Lair* lair)
	{
		auto from = lair->getPos();

		m_routes.try_emplace(lair, Routes{ createRoute(from, RouteType::Light), createRoute(from, RouteType::Heavy), createRoute(from, RouteType::Air) });
	}

	void EnemyManager::updateRoutes()
	{
		std::for_each(std::begin(m_routes), std::end(m_routes),
			[&](auto& p)
			{
				p.second.heavy = createRoute(p.first->getPos(), RouteType::Heavy);
				p.second.light = createRoute(p.first->getPos(), RouteType::Light);
			}
		);
	}

	void EnemyManager::updateExistingRoutes()
	{
		std::for_each(std::begin(m_enemies), std::end(m_enemies),
			[&](auto& enemy)
			{
				enemy->setRoute(*createRoute(enemy->getPos(), RouteType::Light));
			}
		);
	}

	MyVector<std::shared_ptr<Enemy>> EnemyManager::getEnemiesAround(const PosF& pos, const float r) const
	{
		MyVector<std::shared_ptr<Enemy>> res;
		for (size_t i{}; i < m_enemies.size(); i++)
			if (Distance(m_enemies[i]->getPos(), pos) <= r)
				res.push_back(m_enemies[i]);

		return res;
	}

	const std::shared_ptr<Enemy> EnemyManager::getNearestEnemy(const PosF& pos, const float r) const noexcept
	{
		float minDist = std::numeric_limits<float>::max();
		std::shared_ptr<Enemy> target;
		for (size_t i{}; i < m_enemies.size(); i++)
			if (auto dist = Distance(m_enemies[i]->getPos(), pos); dist < r && dist < minDist)
			{
				minDist = dist;
				target = m_enemies[i];
			}

		return target;
	}
	
	void EnemyManager::update(const float dt)
	{
		m_enemies.erase(
			std::remove_if(std::begin(m_enemies), std::end(m_enemies), [](const auto& enemy) { return !enemy->isAlive(); }),
			std::end(m_enemies));

		m_bullets.erase(
			std::remove_if(std::begin(m_bullets), std::end(m_bullets), [](const auto& bullet) { return !bullet->isAlive(); }),
			std::end(m_bullets));

		std::for_each(std::begin(m_enemies), std::end(m_enemies), [dt](auto& enemy) { enemy->update(dt); });
		std::for_each(std::begin(m_bullets), std::end(m_bullets), [dt](auto& bullet) { bullet->update(dt); });
	}

	void EnemyManager::add(std::shared_ptr<Enemy> enemy, const Lair* lair)
	{
		m_enemies.emplace_back(enemy);

		if (m_routes.find(lair) == std::end(m_routes))
			createRoutes(lair);

		if (typeid(*enemy) == typeid(AirEnemy))
			enemy->setRoute(*m_routes.at(lair).air);
		else if (typeid(*enemy) == typeid(HeavyEnemy))
			enemy->setRoute(*m_routes.at(lair).heavy);
		else if (typeid(*enemy) == typeid(LightEnemy))
			enemy->setRoute(*m_routes.at(lair).light);

		sGraphics->add(enemy);
	}

	void EnemyManager::addBullet(const int damage, const PosF& pos, std::shared_ptr<Enemy> target)
	{
		sGraphics->add(m_bullets.emplace_back(std::make_shared<Bullet>(damage, pos, target)));
	}

	std::shared_ptr<ObjectWithHP> EnemyManager::getTargetAt(const PosF& pos) const
	{
		if (sLandscape && std::ceil(pos.x) == pos.x && std::ceil(pos.y) == pos.y)
			if (auto field = std::dynamic_pointer_cast<Field>(sLandscape->getCell(pos)); field)
				return std::static_pointer_cast<ObjectWithHP>(std::dynamic_pointer_cast<Wall>(field->getBuilding()));

		return nullptr;
	}
} // namespace TowerDefence