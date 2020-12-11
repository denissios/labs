#ifndef __ENEMY_MANAGER_HPP_INCLUDED__
#define __ENEMY_MANAGER_HPP_INCLUDED__

#include "Pos.hpp"
#include "Routes.hpp"

#include "MyVector.hpp"
#include <memory>
#include <map>

namespace TowerDefence
{
	class Enemy;
	class Graphics;
	class Castle;
	class Lair;
	class Landscape;
	class ObjectWithHP;
	class Bullet;
	class EnemyManager : std::enable_shared_from_this<EnemyManager>
	{
	private:
		inline static std::shared_ptr<Graphics> sGraphics;
		inline static std::shared_ptr<Landscape> sLandscape;
		
	public:
		inline static void setGraphics(std::shared_ptr<Graphics> graphics) noexcept { sGraphics = std::move(graphics); }

		inline static void setLandscape(std::shared_ptr<Landscape> landscape) noexcept { sLandscape = std::move(landscape); }

	private:
		std::shared_ptr<Route> createRoute(const PosF& from, RouteType routeType);

		void createRoutes(const Lair* lair);

		void updateRoutes();

		void updateExistingRoutes();

	public:
		[[nodiscard]] MyVector<std::shared_ptr<Enemy>> getEnemiesAround(const PosF& pos, const float r) const;

		[[nodiscard]] const std::shared_ptr<Enemy> getNearestEnemy(const PosF& pos, const float r) const noexcept;

		[[nodiscard]] inline auto getCastle() const noexcept { return m_castle; }

		void setCastle(std::shared_ptr<Castle> castle)
		{
			m_castle = std::move(castle);

			updateRoutes();
			updateExistingRoutes();
		}

		void update(const float dt);

		void add(std::shared_ptr<Enemy> enemy, const Lair* lairId);

		void addBullet(const int damage, const PosF& pos, std::shared_ptr<Enemy> target);
		
		std::shared_ptr<ObjectWithHP> getTargetAt(const PosF& pos) const;

	private:
		std::shared_ptr<Castle>              m_castle;
		MyVector<std::shared_ptr<Enemy>>  m_enemies;
		std::map<const Lair*, Routes>        m_routes;
		MyVector<std::shared_ptr<Bullet>> m_bullets;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_MANAGER_HPP_INCLUDED__ */