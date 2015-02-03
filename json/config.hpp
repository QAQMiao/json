#ifndef CONFIG_HPP
#define CONFIG_HPP

//判断是否为cxx11，如果是则定义如下的宏作为判断
#if __cplusplus>=201103U
#define COMPILE_CXX11
#define NIL nullptr
#else
#define NIL NULL
#endif

#endif // CONFIG_HPP
