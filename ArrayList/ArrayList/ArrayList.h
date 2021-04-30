#pragma once

#include <stdexcept>
#include <initializer_list>
#include <type_traits>

template <typename T>
class ArrayList
{
public:
	ArrayList() = default;
	ArrayList(const std::initializer_list<T>& args) noexcept;

	~ArrayList() noexcept;

	void add(const T& value);
	void remove(const size_t removeIndex);
	void insert(const size_t insertIndex, const T& value);

	size_t getSize() const;
	const T& get(const size_t index) const;

	const T* const getRaw() const;
	T* const getRaw();

	T& operator[](const size_t index);

private:
	T* __pMemory = nullptr;

	size_t __size = 0ULL;
	size_t __capacity = 0ULL;

	void __free();
};

template<typename T>
ArrayList<T>::ArrayList(const std::initializer_list<T>& args) noexcept
{
	const size_t size = args.size();

	if ((size == 1ULL) && std::is_integral<T>::value)
	{
		memcpy(&__capacity, args.begin(), sizeof(T));
		__size = __capacity;

		__pMemory = new T[__capacity];
	}
	else
	{
		__capacity = size;
		__size = size;

		__pMemory = new T[__capacity];

		size_t index = 0ULL;
		for (const auto& arg : args)
			__pMemory[index++] = arg;
	}
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
	if (insertIndex >= __capacity)
		throw std::out_of_range("index is out of range.");

	++__size;

	for (size_t i = (__size - 1ULL); i > insertIndex; i--)
		__pMemory[i] = __pMemory[(i - 1)];

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
void ArrayList<T>::__free()
{
	if (__pMemory)
	{
		delete[] __pMemory;
		__pMemory = nullptr;
	}
}