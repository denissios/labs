#ifndef __PROPS_MANAGER_HPP_INCLUDED__
#define __PROPS_MANAGER_HPP_INCLUDED__

#include "CastleProps.hpp"
#include "TowerProps.hpp"
#include "EnemyProps.hpp"

#include <map>
#include <filesystem>

namespace TowerDefence
{
	/*!
	\brief class for props of all entities
	*/
	class PropsManager final
	{
	private:
		inline static std::map<int, CastleProps> sCastleProps;
		inline static std::map<int, TowerProps> sTowerProps;
		inline static std::map<std::string, std::shared_ptr<EnemyProps>> sEnemyProps;

	public:
		/*!
		\brief load castle properties
		\throw invalid_argument("Path to castle props does not exist"), runtime_error("Cannot open castle props file")
		\return void
		*/
		static void loadCastleProps(const std::filesystem::path& path);

		/*!
		\brief load tower properties
		\throw invalid_argument("Path to tower props does not exist"), runtime_error("Cannot open tower props file")
		\return void
		*/
		static void loadTowerProps(const std::filesystem::path& path);

		/*!
		\brief load enemies properties
		\throw invalid_argument("Path to enemy props does not exist"), runtime_error("Cannot open tower props file")
		\return void
		*/
		static void loadEnemyProps(const std::filesystem::path& path);

		/*!
		\brief can we upgrade castle?
		\return bool (can of can't)
		*/
		inline static bool canCastleUpgrade(const int lvl) { return sCastleProps.contains(lvl); }

		/*!
		\brief can we upgrade tower?
		\return bool (can of can't)
		*/
		inline static bool canTowerUpgrade(const int lvl) { return sTowerProps.contains(lvl); }

		/*!
		\brief get castle properties
		*/
		inline static auto getCastleProps(const int lvl = 1) { return sCastleProps.at(lvl); }

		/*!
		\brief get tower properties
		*/
		inline static auto getTowerProps(const int lvl = 1) { return sTowerProps.at(lvl); }

		/*!
		\brief get enemies properties
		*/
		inline static auto getEnemyProps(const std::string& enemy) { return sEnemyProps.at(enemy); }
	};
} // namespace TowerDefence

#endif /* !__PROPS_MANAGER_HPP_INCLUDED__ */
