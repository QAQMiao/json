#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP
#include<exception>
#include<string>

namespace MEOJ
{
	class MyException : public std::exception
	{
	public:
		MyException() noexcept{}
		MyException(const char* information) noexcept
		{
			error = information;
		}
		const char* what() const noexcept
		{
			return error.c_str();
		}
	private:
		std::string error;
	};
}


#endif // MYEXCEPTION_HPP
