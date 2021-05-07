#pragma once

#include "OperationType.h"

template<typename T, T lhs, T rhs, OperationType operationType>
class StaticCalculator 
{
public:
	static constexpr T calc();

private:
	StaticCalculator() = delete; 
};

template<typename T, T lhs, T rhs, OperationType operationType>
inline constexpr T StaticCalculator<T, lhs, rhs, operationType>::calc()
{
	T retVal; 

	if constexpr (operationType == OperationType::PLUS) 
		retVal = (lhs + rhs);
	else if constexpr (operationType == OperationType::MINUS)
		retVal = (lhs - rhs);
	else if constexpr (operationType == OperationType::PRODUCT)
		retVal = (lhs * rhs);
	else if constexpr (operationType == OperationType::DIVIDE)
		retVal = (lhs / rhs);
	else 
		static_assert(false, "invalid operation type.");
	
	return retVal; 
}