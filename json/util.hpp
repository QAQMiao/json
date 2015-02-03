#ifndef UTIL_HPP
#define UTIL_HPP

#include<type_traits>

namespace MEOJ
{
	//获取一个左值的指针
	template<typename T>
	T* getAddressOf(T& lval)
	{
		return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(lval)));
	}

	template<typename T>
	void swap(T& a,T& b)
	{
		T c = a;
		a = b;
		b = c;
	}
}

#endif // UTIL_HPP
