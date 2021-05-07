#pragma once

#include <type_traits>

template <typename T>
class Number 
{
	static_assert(std::is_arithmetic_v<T>, "invalid type.");

public:
	constexpr Number(const T value); 

	constexpr T getValue() const;

private:
	T __value; 
};

template <typename T>
inline constexpr Number<T>::Number(const T value) :
	__value{ value }
{}

template<typename T>
inline constexpr T Number<T>::getValue() const
{
	return __value; 
}