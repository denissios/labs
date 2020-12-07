#ifndef __LANDSCAPE_HPP_INCLUDED__
#define __LANDSCAPE_HPP_INCLUDED__

#include "Castle.hpp"
#include "Field.hpp"
#include "Tower.hpp"
#include "EnemyManager.hpp"
#include "Lair.hpp"
#include "Enemy.hpp"
#include "MyVector.hpp"

#include <set>
#include <memory>

namespace TowerDefence
{
	/*!
	\brief class for landscape on map
	*/
	class Landscape
	{
	private:
		template<typename _T>
		using matrix_t = MyVector<MyVector<_T>>;

	private:
		/*!
		\brief can we do anything here?
		\return bool (can or can't)
		*/
		template<typename _Pred>
		inline bool canDoHere(const PosF& pos, _Pred pred) const
		{
			return std::find_if(std::begin(m_cells), std::end(m_cells),
				[&pos, p = std::move(pred)](const std::shared_ptr<Cell>& cell)
			{
				if (cell->getPos() != pos || typeid(*cell) != typeid(Field))
					return false;

				return p(std::dynamic_pointer_cast<Field>(cell));
			}) != std::end(m_cells);
		}

	public:
		inline Landscape(const unsigned width, const unsigned height) :
			m_width(width),
			m_height(height),
			m_entities(),
			m_cells(),
			m_castle{},
			m_enemyManager(std::make_shared<EnemyManager>())
		{
			Lair::setEnemyManager(m_enemyManager);
			Enemy::setEnemyManager(m_enemyManager);
		}

		~Landscape()
		{
			Lair::setEnemyManager(nullptr);
			Enemy::setEnemyManager(nullptr);
		}

		[[nodiscard]] inline constexpr auto getWidth() const noexcept { return m_width; }

		[[nodiscard]] inline constexpr auto getHeight() const noexcept { return m_height; }

		[[nodiscard]] inline const auto& getEntities() const noexcept { return m_entities; }

		[[nodiscard]] inline const std::shared_ptr<Cell> getCell(const PosF& pos) const noexcept
		{
			const auto cell = std::find_if(std::cbegin(m_cells), std::cend(m_cells), [&pos](const auto& el) { return el->getPos() == pos; });
			if (cell == std::end(m_cells)) [[unlikely]]
				return nullptr;

			return *cell;
		}

		/*!
		\return reference on Cell
		*/
		[[nodiscard]] inline const auto& getCells() const noexcept { return m_cells; }

		/*!
		\return pointer on Castle
		*/
		[[nodiscard]] inline auto getCastle() const noexcept { return m_castle; }

		/*!
		\return pointer on EnemyManager
		*/
		[[nodiscard]] inline auto getEnemyManager() const noexcept { return m_enemyManager; }

		/*!
		\brief Is this position on field?
		\return bool (yes or no)
		*/
		inline bool isInField(const PosF& pos) const noexcept { return pos.x >= 0.f && pos.x < m_width&& pos.y >= 0.f && pos.y <= m_height; }

		/*!
		\brief update information about landscape
		\return void
		*/
		void update(const float dt);

		/*!
		\brief add a new entity
		\return reference to new entity
		*/
		template<typename _EntityType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Entity, _EntityType>>>
		inline auto& addEntity(_Args&&... args)
		{
			auto& entity = *m_entities.emplace(std::make_shared<_EntityType>(std::forward<_Args>(args)...)).first;

			if constexpr (std::is_same_v<_EntityType, Castle>)
			{
				m_castle = std::dynamic_pointer_cast<Castle>(entity);

				m_enemyManager->setCastle(m_castle);
			}

			return entity;
		}

		/*!
		\brief add a new cell
		\return reference to new cell
		*/
		template<typename _CellType, typename... _Args, typename = std::enable_if_t<std::is_base_of_v<Cell, _CellType>>>
		inline auto& addCell(_Args&&... args)
		{
			return *m_cells.emplace(std::make_shared<_CellType>(std::forward<_Args>(args)...)).first;
		}

		/*!
		\brief can we build here?
		\return bool (can or can't)
		*/
		inline bool canBuildHere(const PosF& pos) const
		{
			return canDoHere(pos,
				[&](const auto& field)
				{
					return !field->isBusy() && m_castle->hasMoney(PropsManager::getTowerProps().price); // TODO: enemy should move than
				});
		}

		/*!
		\brief can we upgrade this?
		\return bool (can or can't)
		*/
		inline bool canUpgradeHere(const PosF& pos) const
		{
			return canDoHere(pos,
				[&](const auto& field)
				{
					const auto ptr = std::dynamic_pointer_cast<UpgradableBuilding>(field->getBuilding());

					return field->isBusy() && ptr && ptr->canUpgrade() && m_castle->hasMoney(ptr->getUpgradePrice());
				});
		}

		/*!
		\brief can we repair this?
		\return bool (can or can't)
		*/
		inline bool canRepairHere(const PosF& pos) const
		{
			return canDoHere(pos, [](const auto&) { return false; });
		}

		/*!
		\brief build anything
		\return void
		*/
		inline void build(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
			{
				m_castle->withdraw(PropsManager::getTowerProps().price);

				auto tower = addEntity<Tower>(pos);
				field->build(std::dynamic_pointer_cast<Building>(tower));
			}
		}

		/*!
		\brief upgrade anything
		\return void
		*/
		inline void upgrade(const PosF& pos)
		{
			if (auto field = std::dynamic_pointer_cast<Field>(getCell(pos)); field)
				if (auto upgradable = std::dynamic_pointer_cast<UpgradableBuilding>(field->getBuilding()); upgradable && upgradable->canUpgrade())
				{
					m_castle->withdraw(upgradable->getUpgradePrice());

					upgradable->upgrade();
				}
		}

		inline void repair(const PosF& pos)
		{

		}

	private:
		unsigned                          m_width;
		unsigned                          m_height;
		std::set<std::shared_ptr<Entity>> m_entities;
		std::set<std::shared_ptr<Cell>>   m_cells;
		std::shared_ptr<Castle>           m_castle;
		std::shared_ptr<EnemyManager>     m_enemyManager;
	};
} // namespace TowerDefence

#endif /* !__LANDSCAPE_HPP_INCLUDED__ */