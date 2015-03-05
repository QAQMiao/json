#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include<cstdio>
#include<string>
#include "FileSystem.hpp"
#include "JsonNode.hpp"

namespace MEOJ
{
	class JsonParser
	{
	public:
		JsonNode* getRootNodeFromString(const std::string& source)
		{
			std::string context(source);
			if(source.empty())
				return false;
			std::string::size_type i;
            while(context[i] != "\"")
				i++;
			context.substr(i);
			JsonNode* nowNode = new JsonNode;
			std::string key;
			while(context[++i] != "\"")
				key+=context[i];
			nowNode -> setKey(key);
			JSON_TYPE jsonType = nowNode -> parseJsonType(context);
			if(jsonType == 0)
			{
				;
			}
			if(jsonType == 1)
			{
				;
			}
		}
		JsonNode* getRootNodeFromFile(const char* fileName)
		{
			;
		}
	}
}
#endif // JSONPARSER_HPP
