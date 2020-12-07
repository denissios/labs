#ifndef __TOWER_PROPS_HPP_INCLUDED__
#define __TOWER_PROPS_HPP_INCLUDED__

#include <iostream>

namespace TowerDefence
{
	/*!
	\brief struct for properties of own tower
	*/
	struct TowerProps
	{
		float r;
		int damage;
		float attackSpeed;
		int price;
	};

	inline std::istream& operator>>(std::istream& istr, TowerProps& props)
	{
		return istr >> props.r >> props.damage >> props.attackSpeed >> props.price;
	}
} // namespace TowerDefence

#endif /* !__TOWER_PROPS_HPP_INCLUDED__ */