#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include<cstdio>
#include<string>
#include "FileSystem.hpp"
#include "JsonNode.hpp"
#include "GetChildren.hpp"

namespace MEOJ
{
	class JsonParser
	{
	public:
		JsonNode* getRootNodeFromString(const std::string& source)
		{
			std::string context(source);
			if(source.empty())
				return nullptr;
			JsonNode* rootNode = new JsonNode;
			rootNode->addChild(getChildren(source));

//			std::string::size_type i;
//            while(source[i] != '\"')
//				i++;
//			std::string key;
//			while(context[++i] != '\"')
//				key+=context[i];
//			nowNode -> setKey(key);
//			JSON_TYPE jsonType = JsonNode::parseJsonType(context);
//			if(jsonType == 0)
//			{
//				;
//			}
//			if(jsonType == 1)
//			{
//				;
//			}
			return nullptr;
		}
		JsonNode* getRootNodeFromFile(const char* fileName)
		{
			return nullptr;
		}
	};
}
#endif // JSONPARSER_HPP
