#include "Var.h"

Var::Var()
{
	__malloc(); 
}

Var::~Var()
{
	delete[] __pMemory; 
	__pMemory = nullptr; 
}

void Var::__malloc()
{
	__pMemory = new unsigned char[__memSize]; 
}

void Var::__free()
{
	delete[] __pMemory;
	__pMemory = nullptr;
}