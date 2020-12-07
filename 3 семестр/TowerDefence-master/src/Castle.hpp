#ifndef __CASTLE_HPP_INCLUDED__
#define __CASTLE_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"
#include "ObjectWithHP.hpp"
#include "PropsManager.hpp"

namespace TowerDefence
{
	/*!
	\brief class for castle
	*/
	class Castle final : public UpgradableBuilding, public ObjectWithHP
	{
	private:
		inline static constexpr auto REPAIR_AMOUNT{ 9 };

	public:
		inline Castle(const int startMoney, const PosF& pos) :
			UpgradableBuilding(pos),
			ObjectWithHP(PropsManager::getCastleProps().maxHealth),
			Building(pos),
			m_money(startMoney),
			m_props(PropsManager::getCastleProps())
		{ }

		inline ~Castle() noexcept override = default;

		/*!
		\brief can castle upgrade?
		\return bool (can upgrade or no)
		*/
		bool canUpgrade() const override { return PropsManager::canCastleUpgrade(m_lvl + 1); }

		/*!
		\brief has castle upgrated?
		\return bool (upgrade or no)
		*/
		bool upgrade() noexcept override;

		/*!
		\brief update information about castle
		\return void
		*/
		void update(const float dt) override;

		[[nodiscard]] inline int getUpgradePrice() const noexcept override { return m_props.price; }

		[[nodiscard]] inline int getMaxHealth() const noexcept override { return m_props.maxHealth; }

		[[nodiscard]] inline constexpr auto getMoney() const noexcept { return m_money; }

		/*!
		\throw runtime_error("Not enought money")
		\return void
		*/
		void withdraw(const int amount);

		inline bool hasMoney(const int amount) const noexcept { return m_money >= amount; }

	private:
		int m_money;
		CastleProps m_props;
	};
}

#endif /* !__CASTLE_HPP_INCLUDED__ */