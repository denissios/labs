#ifndef __ROUTE_HPP_INCLUDED__
#define __ROUTE_HPP_INCLUDED__

#include "Pos.hpp"

#include <queue>

namespace TowerDefence
{
	/*!
	\brief class for own route	
	*/
	class Route
	{
	public:
		Route() = default;

		inline Route(const PosF& to, std::queue<PosF> path) noexcept :
			m_to(to),
			m_path(std::move(path))
		{ }

		/*!
		\brief get the next position
		*/
		[[nodiscard]] inline auto getNext() noexcept
		{
			if (!m_path.empty())
			{
				auto&& val = m_path.front();
				m_path.pop();

				return val;
			}

			return m_to;
		}

		/*!
		\brief find the next position on road
		*/
		[[nodiscard]] inline auto next() const noexcept
		{
			if (m_path.empty())
				return m_to;

			return m_path.front();
		}

		/*!
		\brief position where to go
		\return position
		*/
		[[nodiscard]] inline constexpr auto to() const noexcept { m_to; }

		/*!
		\brief is object finished of no?
		\return bool (finished or no)
		*/
		inline bool isFinished() const noexcept { return m_path.empty(); }

		operator bool() const noexcept { return !m_path.empty(); }

	private:
		PosF m_to;
		std::queue<PosF> m_path;
	};
} // namespace TowerDefence

#endif /* !__ROUTE_HPP_INCLUDED__ */