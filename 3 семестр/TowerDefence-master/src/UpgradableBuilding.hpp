#ifndef __UPGRADABLE_BUILDING_HPP_INCLUDED__
#define __UPGRADABLE_BUILDING_HPP_INCLUDED__

#include "Building.hpp"

namespace TowerDefence
{
	/*!
	\brief class for building that can upgrade
	*/
	class UpgradableBuilding : virtual public Building
	{
	public:
		inline UpgradableBuilding(const PosF& pos, const int lvl = 1) noexcept :
			Building(pos),
			m_lvl(lvl)
		{ }

		inline virtual ~UpgradableBuilding() noexcept override = default;

		/*!
		\brief can building upgrade?
		\return bool (can upgrade or no)
		*/
		virtual bool canUpgrade() const = 0;

		/*!
		\brief has building upgrated?
		\return bool (upgrade or no)
		*/
		virtual bool upgrade() noexcept = 0;

		virtual int getUpgradePrice() const noexcept = 0;

	protected:
		int m_lvl;
	};
}

#endif /* !__UPGRADABLE_BUILDING_HPP_INCLUDED__ */