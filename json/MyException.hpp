#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP
#include<exception>
#include<string>

namespace MEOJ
{
	class MyException : public std::exception
	{
	public:
		MyException(){}
		MyException(const char* information)
		{
			error = information;
		}
		const char* what() const
		{
			return error.c_str();
		}
	private:
		std::string error;
	};
}


#endif // MYEXCEPTION_HPP
