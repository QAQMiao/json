#include"FileSystem.hpp"
#include"Serialization.hpp"
#include"JsonParser.hpp"
#include<string>
#include<iostream>
using namespace std;
using namespace MEOJ;

int main()
{
	bool success = true;
	try
	{
		JsonParser ps;
		auto ret = ps.getRootNodeFromFile("testFile.txt");
		ret -> display();
		delete ret;
	}
	catch(const MyException& err)
	{
		success = false;
		cout << err.what() << endl;
	}
	if(success)
		std::cout << "Done." << std::endl;
	return 0;
}
