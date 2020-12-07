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

	/*!
	\brief class for controlling enemies
	*/
	class EnemyManager : std::enable_shared_from_this<EnemyManager>
	{
	private:
		inline static std::shared_ptr<Graphics> sGraphics;
		inline static std::shared_ptr<Landscape> sLandscape;
		
	public:
		/*!
		\brief set graphics for enemies
		\return void
		*/
		inline static void setGraphics(std::shared_ptr<Graphics> graphics) noexcept { sGraphics = std::move(graphics); }

		/*!
		\brief set landscape for enemies
		\return void
		*/
		inline static void setLandscape(std::shared_ptr<Landscape> landscape) noexcept { sLandscape = std::move(landscape); }

	private:
		/*!
		\brief create route for enemies
		\return pointer to class Route
		*/
		std::shared_ptr<Route> createRoute(const PosF& from, RouteType routeType);

		/*!
		\brief create all routes
		\return void
		*/
		void createRoutes(const Lair* lair);

		/*!
		\brief update routes for enemies
		\return void
		*/
		void updateRoutes();

		/*!
		\brief update existing routes for enemies
		\return void
		*/
		void updateExistingRoutes();

	public:
		/*!
		\brief get enemies around one enemy
		\return pointer to vector of Enemy
		*/
		[[nodiscard]] MyVector<std::shared_ptr<Enemy>> getEnemiesAround(const PosF& pos, const float r) const;

		[[nodiscard]] inline auto getCastle() const noexcept { return m_castle; }

		/*!
		\brief set position for castle
		\return void
		*/
		void setCastle(std::shared_ptr<Castle> castle)
		{
			m_castle = std::move(castle);

			updateRoutes();
			updateExistingRoutes();
		}

		/*!
		\brief update information for all enemies
		\return void
		*/
		void update(const float dt);

		/*!
		\brief add enemy to map
		\return void
		*/
		void add(std::shared_ptr<Enemy> enemy, const Lair* lairId);
		
	private:
		std::shared_ptr<Castle>             m_castle;
		MyVector<std::shared_ptr<Enemy>> m_enemies;
		std::map<const Lair*, Routes>       m_routes;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_MANAGER_HPP_INCLUDED__ */