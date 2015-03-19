#ifndef GETCHILDREN_HPP
#define GETCHILDREN_HPP

#include<cstdio>
#include<string>
#include<vector>
#include "JsonNode.hpp"
#include "JSON_TYPE.hpp"
#include "DiliverContext.hpp"
#include "Serialization.hpp"

namespace MEOJ
{
	std::vector<JsonNode*> getChildren(const std::string& context);
	void dealString(JsonNode* nowNode,const std::string& str);
	void dealBoolean(JsonNode* nowNode,const std::string& str);
	void dealNumberic(JsonNode* nowNode,const std::string& str);
	void dealObject(JsonNode* nowNode,const std::string& str);
	void dealArray(JsonNode* nowNode,const std::string& str);
}
#endif // GETCHILDREN_HPP
