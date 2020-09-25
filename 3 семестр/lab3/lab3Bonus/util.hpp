#ifndef __UTIL_HPP_INCLUDED__
#define __UTIL_HPP_INCLUDED__

#include <iostream>
#include <concepts>

namespace std
{
	template<typename _Ty>
	concept numeric = is_arithmetic_v<_Ty>;
} // namespace std

template <std::numeric _Ty>
_NODISCARD
_Ty GetNumber(const std::string_view msg)
{
	std::cout << msg;
	_Ty element{};

	while (!(std::cin >> element))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cerr << "Error! Wrong input!" << std::endl << msg;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return element;
}

#endif /* !__UTIL_HPP_INCLUDED__ */