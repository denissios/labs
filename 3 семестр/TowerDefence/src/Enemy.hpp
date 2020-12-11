#ifndef __ENEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__

#include "Entity.hpp"
#include "ObjectWithHP.hpp"
#include "EnemyProps.hpp"
#include "Route.hpp"
#include "Aura.hpp"

#include "MyVector.hpp"
#include <memory>

namespace TowerDefence
{
	class EnemyManager;
	class Enemy : public Entity, public ObjectWithHP
	{
	protected:
		inline static std::shared_ptr<EnemyManager> sEnemyManager;

	public:
		inline static void setEnemyManager(std::shared_ptr<EnemyManager> enemyManager) noexcept { sEnemyManager = std::move(enemyManager); }

	protected:
		void attack(std::shared_ptr<ObjectWithHP> object) const noexcept;

		void move(const float dt);

		void regenerate();

		void useAuras();

	public:
		inline Enemy(std::shared_ptr<EnemyProps> props, MyVector<std::shared_ptr<Aura>>&& auras) noexcept :
			ObjectWithHP(props->maxHealth),
			m_props(std::move(props)),
			m_auras(std::move(auras)),
			m_buffs{}
		{}

		inline virtual ~Enemy() noexcept override = default;

		inline int getMaxHealth() const noexcept final { return m_props->maxHealth; }

		void update(const float dt) override;

		[[nodiscard]] inline const auto& getAuras() const noexcept { return m_auras; }

		[[nodiscard]] inline auto& getBuffs() noexcept { return m_buffs; }

		inline void setRoute(Route route) noexcept { m_route = std::move(route); }

		inline void setProperties(std::shared_ptr<EnemyProps> props) noexcept { m_props = std::move(props); }

	protected:
		std::shared_ptr<EnemyProps>        m_props;
		Route                              m_route;
		MyVector<std::shared_ptr<Aura>> m_auras;
		Buffs                              m_buffs;
	};
} // namespace TowerDefence

#endif /* !__ENEMY_HPP_INCLUDED__ */