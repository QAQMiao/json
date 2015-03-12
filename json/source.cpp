#include"FileSystem.hpp"
#include"JsonNode.hpp"
#include"Serialization.hpp"
#include<iostream>
using namespace std;
using namespace MEOJ;

std::vector<std::string> splitObject(std::string src)
{
	std::vector<std::string> result;
	std::string piece;
	src += ',';
	bool insideString = false;
	bool insideArray = false;
	bool insideObject = false;
	for(std::string::size_type i = 0;i < src.length();i++)
	{
		if(src[i] == '\"')
		{
			insideString = !insideString;
		}
		if(src[i] == '[' || src[i] == ']')
		{
			insideArray = !insideArray;
		}
		if(src[i] == '{' || src[i] == '}')
		{
			insideObject = !insideObject;
		}
		if(insideString == false &&
			insideArray == false &&
			insideObject == false &&
			src[i] == ',')
		{
			result.push_back(piece);
			piece = "";
			continue;
		}
		piece += src[i];
	}
	result.push_back(piece);
	return result;
}

std::vector<std::string> splitArray()
{
	std::vector<std::string> result;
	return result;
}

void parseRecursive(JsonNode* pNode,const string& src)
{
	auto nodes = splitObject(src);
	for(decltype(nodes)::size_type i = 0;i < nodes.size();i++)
	{
		const std::string& piece = nodes[i];
		JsonNode* currentNode = new JsonNode;
		auto jsonType = currentNode->parseJsonType(piece);
		pNode->addChild(currentNode);

		if(piece[0] == '\"')
		{
			std::string key;
			std::string::size_type i;
			for(i = 1;i < piece.length() && piece[i] != '\"';i++)
			{
				key += piece[i];
			}
			currentNode->setKey(key);
			i += 2;
			if(jsonType == JSON_OBJECT)
			{
				std::string nextContext;
				for(;i < piece.length() && piece[i] != '}';i++)
				{
					nextContext += piece[i];
				}
				nextContext = nextContext.substr(1);
				nextContext.pop_back();
				parseRecursive(currentNode,nextContext);
			}
			else if(jsonType == JSON_ARRAY)
			{
				std::string nextContext;
	//			parseRecursive();
			}
			else if(jsonType == JSON_STRING)
			{
			}
			else if(jsonType == JSON_BOOLEAN)
			{
			}
			else
			{
			}
		}
	}
}

JsonNode* parse(const string& src)
{
	JsonNode* rootNode = new JsonNode;
	std::string context;
	bool isInsideString = false;
	for(std::string::size_type i=0;i<src.length();i++)
	{
		if(src[i] != ' ' &&
			src[i] != '\n' &&
			src[i] != '\t' &&
			src[i] != '\r' &&
			src[i] != EOF)
		{
			if(src[i] == '\"')
				isInsideString = !isInsideString;
			context += src[i];
		}
		else
		{
			if(isInsideString)
				context += src[i];
		}
	}
	context = context.substr(1);
	context.pop_back();
	parseRecursive(rootNode,context);
	return rootNode;
}

int main()
{
	bool success = true;
	try
	{
		FileSystem fs;
		fs.readFileContext("testFile.txt");
		auto ret = parse(fs.getFileContext());
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
