#ifndef __TOWER_HPP_INCLUDED__
#define __TOWER_HPP_INCLUDED__

#include "UpgradableBuilding.hpp"
#include "PropsManager.hpp"

namespace TowerDefence
{
	/*!
	\brief class for tower
	*/
	class Tower final : public UpgradableBuilding
	{
	public:
		inline Tower(const PosF& pos) :
			UpgradableBuilding(pos),
			Building(pos),
			m_shotTimer{},
			m_props(PropsManager::getTowerProps())
		{ }

		inline ~Tower() noexcept override = default;

		/*!
		\brief can tower upgrade?
		\return bool (can upgrade or no)
		*/
		inline bool canUpgrade() const override { return PropsManager::canTowerUpgrade(m_lvl + 1); }

		/*!
		\brief has tower upgrated?
		\return bool (upgrade or no)
		*/
		bool upgrade() noexcept override;

		/*!
		\brief update information about tower
		\return void
		*/
		void update(float dt) override;

		[[nodiscard]] inline int getUpgradePrice() const noexcept override { return m_props.price; }

		/*!
		\brief get radius
		\return void
		*/
		[[nodiscard]] inline auto getR() const noexcept { return m_props.r; }

	private:
		float m_shotTimer;
		TowerProps m_props;
	};
} // namespace TowerDefence

#endif /* !__TOWER_HPP_INCLUDED__ */
