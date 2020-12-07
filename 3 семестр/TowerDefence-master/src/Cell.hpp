#ifndef __CELL_HPP_INCLUDED__
#define __CELL_HPP_INCLUDED__

#include "Pos.hpp"

namespace TowerDefence
{
	/*!
	\brief class for cell
	*/
	class Cell
	{
	public:
		inline constexpr Cell(const PosF& pos) noexcept :
			m_pos(pos)
		{ }

		virtual ~Cell() noexcept = default;

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

	protected:
		PosF m_pos;
	};
} // namespace TowerDefence

#endif /* !__CELL_HPP_INCLUDED__ */