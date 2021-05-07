#include "pch.h"
#include "../StaticCalculator/StaticCalculator.h"
#include "../StaticCalculator/Number.h"
#include <string>

using namespace std;

TEST(StaticCalculatorTest, case1)
{
	constexpr double result1 =
		StaticCalculator<double, 30.0, 10.0, OperationType::DIVIDE>::calc(); 

	EXPECT_DOUBLE_EQ(result1, 3.0);

	constexpr Number<int> num1{ 30 };
	constexpr Number<int> num2{ 10 }; 

	constexpr int result2 =
		StaticCalculator<int, num1.getValue(), num2.getValue(), OperationType::PRODUCT>::calc(); 

	EXPECT_EQ(result2, 300); 
}

TEST(StaticCalculatorTest, case2)
{
	constexpr Number<int> num1{ 10 }; 
	ASSERT_EQ(num1.getValue(), 10); 
}