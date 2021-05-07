#include "pch.h"
#include "../Var/Var.h"
#include <iostream>

using namespace std; 

TEST(VarTest, case1)
{
	// 빈 var 변수 생성
	Var var;

	// int 값을 대입
	var = 1;
	EXPECT_EQ(var.get<int>(), 1); 

	// float 값으로 재설정
	var = 10.234f;
	EXPECT_FLOAT_EQ(var.get<float>(), 10.234f); 
}