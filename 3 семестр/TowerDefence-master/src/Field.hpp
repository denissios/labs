#ifndef __FIELD_HPP_INCLUDED__
#define __FIELD_HPP_INCLUDED__

#include "Cell.hpp"
#include "Building.hpp"

#include <memory>

namespace TowerDefence
{
	/*!
	\brief class for field
	*/
	class Field final : public Cell
	{
	public:
		inline constexpr Field(const PosF& pos) noexcept :
			Cell(pos),
			m_building{}
		{ }

		inline ~Field() noexcept override = default;

		/*!
		\brief get building
		\return pointer on Building
		*/
		[[nodiscard]] inline const auto getBuilding() const noexcept { return m_building; }

		/*!
		\brief has this cell busy or no?
		\return bool (busy or no)
		*/
		inline bool isBusy() const noexcept { return m_building != nullptr; }

		/*!
		\brief build field
		\return void
		*/
		inline void build(std::shared_ptr<Building> building) noexcept
		{
			if (!isBusy())
				m_building = std::move(building);
		}

	private:
		std::shared_ptr<Building> m_building;
	};
} // namespace TowerDefence

#endif /* !__FIELD_HPP_INCLUDED__ */