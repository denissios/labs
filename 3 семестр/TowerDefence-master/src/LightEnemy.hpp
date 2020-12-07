#ifndef __LIGHT_ENEMY_HPP_INCLUDED__
#define __LIGHT_ENEMY_HPP_INCLUDED__

#include "Enemy.hpp"

namespace TowerDefence
{
	/*!
	\brief class for light enemy
	*/
	class LightEnemy : public Enemy
	{
	public:
		inline LightEnemy(std::shared_ptr<EnemyProps> props) noexcept :
			Enemy(props)
		{}

		inline ~LightEnemy() noexcept override = default;
	};
} // namespace TowerDefence

#endif /* !__LIGHT_ENEMY_HPP_INCLUDED__ */