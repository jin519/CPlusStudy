#pragma once

#include <stdexcept>

class Var 
{
public:
	Var(); 

	template <typename T>
	Var(const T& value); 

	~Var(); 

	template <typename T>
	Var& operator=(const T& value); 

	template <typename T>
	const T& get() const; 

private:
	size_t __typeHashCode = 0ULL;

	size_t __memSize = 8ULL; 
	unsigned char* __pMemory;

	void __malloc(); 
	void __free();

	template <typename T>
	void __setValue(const T& value); 
};

template <typename T>
inline Var::Var(const T& value) : 
	__memSize{ sizeof(value) }
{
	__malloc(); 
	operator=(value); 
}

template<typename T>
inline Var& Var::operator=(const T& value)
{
	const type_info& typeInfo = typeid(T);
	__typeHashCode = typeInfo.hash_code(); 

	__setValue(value); 

	return *this; 
}

template<typename T>
inline const T& Var::get() const
{
	if (__typeHashCode != typeid(T).hash_code())
		throw std::exception{ "types do not match." };

	return *reinterpret_cast<T*>(__pMemory);
}

template<typename T>
inline void Var::__setValue(const T& value)
{
	new (__pMemory) T(value); 
}