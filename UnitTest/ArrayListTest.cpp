#include "pch.h"
#include "../ArrayList/ArrayList.h"

using namespace std; 

TEST(ArrayListTest, copy_constructor) 
{
	ArrayList<float> arr1{ 1.f, 2.f, 3.f }; 
	ArrayList<float> arr2{ arr1 };
	
	const size_t size = arr1.getSize(); 

	EXPECT_EQ(size, arr2.getSize());

	for (size_t i = 0ULL; i < size; ++i)
		EXPECT_FLOAT_EQ(arr1[i], arr2[i]); 
}

TEST(ArrayListTest, move_constructor) 
{
	ArrayList<int> arr1{ 1, 2, 3 }; 
	ArrayList<int> arr2{ move(arr1) };

	EXPECT_EQ(arr2.getSize(), 3ULL); 

	EXPECT_EQ(arr2[0], 1);
	EXPECT_EQ(arr2[1], 2);
	EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayListTest, copy_assign_operator) 
{
	ArrayList<unsigned int> arr1{ 1U, 2U }; 
	ArrayList<unsigned int> arr2{ 10U, 20U, 30U, 40U }; 

	arr1 = arr2; 

	EXPECT_EQ(arr1.getSize(), arr2.getSize()); 

	EXPECT_EQ(arr1[0], 10U);
	EXPECT_EQ(arr1[1], 20U);
	EXPECT_EQ(arr1[2], 30U);
	EXPECT_EQ(arr1[3], 40U);
}

TEST(ArrayListTest, move_assign_operator) 
{
	ArrayList<double> arr1{ 1.0, 2.0 }; 
	ArrayList<double> arr2{ 10.0, 20.0, 30.0, 40.0 }; 

	arr1 = move(arr2); 

	EXPECT_EQ(arr1.getSize(), 4ULL);

	EXPECT_DOUBLE_EQ(arr1[0], 10.0);
	EXPECT_DOUBLE_EQ(arr1[1], 20.0);
	EXPECT_DOUBLE_EQ(arr1[2], 30.0);
	EXPECT_DOUBLE_EQ(arr1[3], 40.0);
}