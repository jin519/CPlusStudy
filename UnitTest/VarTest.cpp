#include "pch.h"
#include "../Var/Var.h"
#include <iostream>

using namespace std; 

TEST(VarTest, case1)
{
	// �� var ���� ����
	Var var;

	// int ���� ����
	var = 1;
	EXPECT_EQ(var.get<int>(), 1); 

	// float ������ �缳��
	var = 10.234f;
	EXPECT_FLOAT_EQ(var.get<float>(), 10.234f); 
}