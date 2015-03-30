#ifndef MEOJMACROS_HPP
#define MEOJMACROS_HPP
#include<iostream>

//miao版debug，如果不需要debug了，把第一条语句注释掉就可以了～
//#define OPEN_DEBUG_FUNCTION
#ifdef OPEN_DEBUG_FUNCTION
#define mmDBG(x) do{std::cout << x << std::endl;}while(0)
#else
#define mmDBG(x)
#endif // OPEN_DEBUG_FUNCTION


#endif // MEOJMACROS_HPP
