#include"FileSystem.hpp"
#include"Serialization.hpp"
#include"JsonParser.hpp"
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
		ret->display();
		delete ret;
	}
	catch(const MyException& err)
	{
		success = false;
		cout<<err.what()<<endl;
	}
	if(success)
		printf("哇塞！你好幸运！居然在如此渣渣的代码下成功了！恭喜你～\n");
	return 0;
}
