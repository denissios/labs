#ifndef __HP_HPP_INCLUDED__
#define __HP_HPP_INCLUDED__

#include "Pos.hpp"

#include <memory>

class QGraphicsScene;
class QGraphicsRectItem;

namespace TowerDefence
{
	class HP final
	{
	public:
		inline static constexpr auto WIDTH{ 30 };
		inline static constexpr auto HEIGHT{ 10 };

	public:
		inline constexpr HP() noexcept :
			m_back{},
			m_front{}
		{ }

		HP(std::shared_ptr<QGraphicsScene> scene, const PosI& size = { HP::WIDTH, HP::HEIGHT });

		~HP() noexcept;

		void setPos(const PosF& pos) noexcept;

		void setHP(const float percent) noexcept;

	private:
		std::shared_ptr<QGraphicsScene>    m_scene;
		std::shared_ptr<QGraphicsRectItem> m_back;
		std::shared_ptr<QGraphicsRectItem> m_front;
	};
} // namespace TowerDefence

#endif /* !__HP_HPP_INCLUDED__ */