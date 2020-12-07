#ifndef __MAP_LOADER_HPP_INCLUDED__
#define __MAP_LOADER_HPP_INCLUDED__

#include <filesystem>
#include <memory>

namespace TowerDefence
{
	class Landscape;

	/*!
	\brief class for loading map
	*/
	class MapLoader
	{
	public:
		/*!
		\brief load information about map
		\return pointer on Landscape
		*/
		static std::shared_ptr<Landscape> load(const std::filesystem::path& path);
	};
} // namespace MobileRobots

#endif /* !__MAP_LOADER_HPP_INCLUDED__ */