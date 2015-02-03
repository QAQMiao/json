#include"FileSystem.hpp"
#include"Serialization.hpp"
#include<iostream>
using namespace std;
using namespace MEOJ;



int main()
{
	FileSystem fs;
	fs.setFileContext("memeda");
	if(!fs.writeFileContext("testFile.txt"))
	{
		cout<<"write file failed."<<endl;
	}
	fs.readFileContext("testFile.txt");
	if(fs.readFileContext("testFile.txt"))
	{
		cout<<"The File Context is : "<<fs.getFileContext()<<endl;
	}
	else
	{
		cout<<"Read File Failed."<<endl;
	}
	return 0;
}
