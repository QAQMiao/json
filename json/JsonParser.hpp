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
			return rootNode;
		}
		JsonNode* getRootNodeFromFile(const char* fileName)
		{
			JsonNode* rootNode = new JsonNode;
			rootNode = getRootNodeFromString(FileSystem::readFileContext(fileName));
			return rootNode;
		}
	};
}
#endif // JSONPARSER_HPP
