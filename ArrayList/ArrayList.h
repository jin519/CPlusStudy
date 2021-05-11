#pragma once

#include <stdexcept>
#include <initializer_list>
#include <type_traits>
#include <iostream>
#include <string>

template <typename T>
class ArrayList
{
public:
	ArrayList() = default;

	template <typename = typename std::enable_if_t<!std::is_integral_v<T>>>
	explicit ArrayList(const size_t size) noexcept;
	
	explicit ArrayList(const std::initializer_list<T> args) noexcept;

	~ArrayList() noexcept;

	void add(const T& value);
	void remove(const size_t removeIndex);
	void insert(const size_t insertIndex, const T& value);

	size_t getSize() const;
	const T& get(const size_t index) const;

	const T* const getRaw() const;
	T* const getRaw();

	T& operator[](const size_t index);

	void show(const std::string& name) const;

private:
	T* __pMemory = nullptr;

	size_t __size = 0ULL;
	size_t __capacity = 0ULL;

	void __free();
	void __malloc(const size_t size); 
	void __init(const std::initializer_list<T>& args); 
};

template <typename T>
template <typename>
ArrayList<T>::ArrayList(const size_t size) noexcept 
{
	__malloc(size); 
}

template<typename T>
ArrayList<T>::ArrayList(const std::initializer_list<T> args) noexcept
{
	__init(args);
}

template <typename T>
ArrayList<T>::~ArrayList() noexcept
{
	__size = 0ULL;
	__capacity = 0ULL;

	__free();
}

template <typename T>
void ArrayList<T>::add(const T& value)
{
	const size_t last = __size;

	++__size;

	if (__capacity < __size)
	{
		__capacity = __size;

		T* pMemory = new T[__capacity];

		for (size_t i = 0; i < last; ++i)
			pMemory[i] = __pMemory[i];

		__free();

		__pMemory = pMemory;
	}

	__pMemory[last] = value;
}

template<typename T>
void ArrayList<T>::remove(const size_t removeIndex)
{
	if (removeIndex >= __size)
		throw std::out_of_range("index is out of range.");

	--__size;

	for (size_t i = removeIndex; i < __size; ++i)
		__pMemory[i] = __pMemory[(i + 1)];
}

template<typename T>
inline void ArrayList<T>::insert(const size_t insertIndex, const T& value)
{
	++__size;

	if (insertIndex >= __capacity)
	{
		__capacity = (insertIndex + 1ULL);
		
		T* pMemory = new T[__capacity];

		for (size_t i = (__size - 1ULL); i > insertIndex; i--)
			pMemory[i] = __pMemory[(i - 1)];

		__free();

		__pMemory = pMemory;
	}
	else 
	{
		for (size_t i = (__size - 1ULL); i > insertIndex; i--)
			__pMemory[i] = __pMemory[(i - 1)];
	}

	__pMemory[insertIndex] = value;
}

template <typename T>
size_t ArrayList<T>::getSize() const
{
	return __size;
}

template<typename T>
const T& ArrayList<T>::get(const size_t index) const
{
	return __pMemory[index];
}

template <typename T>
const T* const ArrayList<T>::getRaw() const
{
	return __pMemory;
}

template<typename T>
T* const ArrayList<T>::getRaw()
{
	return __pMemory;
}

template <typename T>
T& ArrayList<T>::operator[](const size_t index)
{
	if (index >= __capacity)
		throw std::out_of_range("index is out of range.");

	return __pMemory[index];
}

template<typename T>
void ArrayList<T>::show(const std::string& name) const
{
	std::cout << "# " << name << std::endl;

	for (size_t i = 0; i < __size; ++i)
		std::cout << __pMemory[i] << std::endl;

	std::cout << std::endl;
}

template<typename T>
void ArrayList<T>::__free()
{
	if (__pMemory)
	{
		delete[] __pMemory;
		__pMemory = nullptr;
	}
}

template<typename T>
void ArrayList<T>::__malloc(const size_t size)
{
	__capacity = size; 
	__size = size; 

	__pMemory = new T[size]; 
}

template<typename T>
void ArrayList<T>::__init(const std::initializer_list<T>& args)
{
	__malloc(args.size()); 

	size_t index = 0ULL;
	for (const auto& arg : args)
		__pMemory[index++] = arg;
}