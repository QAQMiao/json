#ifndef GETCHILDREN_HPP
#define GETCHILDREN_HPP

#include<cstdio>
#include<string>
#include<vector>
#include<iostream>
#include "JsonNode.hpp"
#include "JSON_TYPE.hpp"
#include "DiliverContext.hpp"
#include "Serialization.hpp"

namespace MEOJ
{
	std::vector<JsonNode*> getChildren(const std::string& context);
	JsonNode* dealString(JsonNode* nowNode,const std::string& str);
	JsonNode* dealBoolean(JsonNode* nowNode,const std::string& str);
	JsonNode* dealNumberic(JsonNode* nowNode,const std::string& str);
	JsonNode* dealObject(JsonNode* nowNode,const std::string& str);
	JsonNode* dealArray(JsonNode* nowNode,const std::string& str);
}
#endif // GETCHILDREN_HPP
