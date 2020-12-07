#ifndef __ENEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__

#include "Entity.hpp"
#include "ObjectWithHP.hpp"
#include "EnemyProps.hpp"
#include "Route.hpp"
#include "MyVector.hpp"

#include <memory>

namespace TowerDefence
{
	class EnemyManager;
	class Aura;

	/*!
	\brief class for all enemies
	*/
	class Enemy : public Entity, public ObjectWithHP
	{
	private:
		inline static std::shared_ptr<EnemyManager> sEnemyManager;

	public:
		inline static void setEnemyManager(std::shared_ptr<EnemyManager> enemyManager) noexcept { sEnemyManager = std::move(enemyManager); }

	private:
		/*!
		\brief for enemy attack
		\return void
		*/
		void attack();
		
		/*!
		\brief for enemy movement
		\return void
		*/
		void move(const float dt);

		/*!
		\brief for enemy regenerate
		\return void
		*/
		void regenerate();

		/*!
		\brief for using auras for enemy
		\return void
		*/
		void useAuras();

	public:
		inline Enemy(std::shared_ptr<EnemyProps> props) noexcept :
			ObjectWithHP(props->maxHealth),
			m_props(std::move(props))
		{}

		inline virtual ~Enemy() noexcept override = default;

		inline int getMaxHealth() const noexcept final { return m_props->maxHealth; }

		/*!
		\brief update information about own enemy
		\return void
		*/
		void update(const float dt) override final;

		/*!
		\brief set route for own enemy
		\return void
		*/
		inline void setRoute(Route route) noexcept { m_route = std::move(route); }

		/*!
		\brief set properties for own enemy
		\return void
		*/
		inline void setProperties(std::shared_ptr<EnemyProps> props) noexcept { m_props = std::move(props); }

	protected:
		std::shared_ptr<EnemyProps>        m_props;
		Route                              m_route;
		MyVector<std::shared_ptr<Aura>> m_auras;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_HPP_INCLUDED__ */