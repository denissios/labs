#ifndef __ENTITY_HPP_INCLUDED__
#define __ENTITY_HPP_INCLUDED__

#include "Pos.hpp"

namespace TowerDefence
{
	/*!
	\brief calss for all entites
	*/
	class Entity
	{
	public:
		inline constexpr Entity() noexcept :
			m_pos{}
		{ }

		inline explicit constexpr Entity(const PosF& pos) noexcept :
			m_pos(pos)
		{ }

		inline virtual ~Entity() noexcept = default;

		/*!
		\brief get position on OX axis
		\return x position
		*/
		[[nodiscard]] inline constexpr auto getX() const noexcept { return m_pos.x; }

		/*!
		\brief get position on OY axis
		\return y position
		*/
		[[nodiscard]] inline constexpr auto getY() const noexcept { return m_pos.y; }

		/*!
		\brief position of cell
		\return OX axis and OY axis position of cell
		*/
		[[nodiscard]] inline constexpr auto getPos() const noexcept { return m_pos; }

		/*!
		\brief set position of own entity
		\return void
		*/
		inline constexpr void setPos(const PosF& pos) noexcept { m_pos = pos; }

		/*!
		\brief update information about entity
		\return void
		*/
		virtual void update(const float dt) = 0;
		
	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__ENTITY_HPP_INCLUDED__ */