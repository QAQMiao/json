#include "GetChildren.hpp"

using namespace MEOJ;


/*大致就是，先把用户需要解析的string给flcl一遍，分出第一层子节点，然后根据
每段的具体类型，继续划分，直至每个结点都为string、numberic、boolean类型或
最简的array类型【这个我也形容不好，佛曰只可意会不可言传～】*/

//叫着getChildren,实际上却是getValue的功能，鉴于实在不相信哈士奇的捣乱，觉得勉强这么叫着
std::vector<JsonNode*> getChildren(const std::string& context)
{
	std::vector<JsonNode*>childrens;
	//std::vector<>::size_type cnt = 0;
	std::vector<std::string>smallPart = diliverContext(context);
	for(std::vector<std::string>::size_type i = 0;i < smallPart.size();i++)
	{
		JsonNode* nowNode = new JsonNode;
		std::string key = "";
		std::string::size_type position = 0;
		while(smallPart[i][position++] != '\"')
			key += smallPart[i][position - 1];
		nowNode->setKey(key);
		JSON_TYPE nowType = JsonNode::parseJsonType(smallPart[i]);
		nowNode->setJsonType(nowType);
		smallPart[i] = smallPart[i].substr(position);
		switch(nowType)
		{
			case JSON_STRING:
				childrens.push_back(dealString(nowNode,smallPart[i]));break;
			case JSON_BOOLEAN:
				childrens.push_back(dealBoolean(nowNode,smallPart[i]));break;
			case JSON_NUMERIC:
				childrens.push_back(dealNumberic(nowNode,smallPart[i]));break;
			case JSON_OBJECT:
				childrens.push_back(dealObject(nowNode,smallPart[i]));break;
			case JSON_ARRAY:
				childrens.push_back(dealArray(nowNode,smallPart[i]));break;
			case JSON_UNKNOWN:
				std::cout<<"这是什么鬼"<<std::endl;
			default:
				break;

		}

	}
	return childrens;
}

std::vector<unsigned char> getArrayValue(const std::string& context)
{
	std::vector<std::string>smallPart = diliverContext(context);
	for(std::vector<std::string>::size_type i = 0 ;i < smallPart.size();i++)
	{
		std::string tmp = "\"aa\":" + smallPart[i];
		JSON_TYPE nowType = JsonNode::parseJsonType(context);
	}
}

JsonNode* dealString(JsonNode* nowNode,const std::string& str)
{
	std::string::size_type poi = 0;
	while(str[poi] != '\"')
		poi++;
	std::string value;
	while(poi < str.size())
	{
		if(str[++poi] == '\"')
			break;
		value += str[poi];
	}
	nowNode->setValue(getDataSerialization(value));
	return nowNode;
}

JsonNode* dealBoolean(JsonNode* nowNode,const std::string& str)
{
	std::string::size_type poi = 0;
	while(str[poi] != 't' && str[poi] != 'f')
		poi++;
	bool value;
	if(str[poi] == 't')
		value = true;
	else
		value = false;
	nowNode->setValue(getDataSerialization(value));
	return nowNode;
}

JsonNode* dealNumberic(JsonNode* nowNode,const std::string& str)
{
	std::string::size_type poi = 0;
	while(str[poi] < '0' || str[poi] > '9')
		poi++;
	int value = 0;
	while(str[poi] >= '0' && str[poi] <= '9' || str[poi] == '.')
		value = value * 10 + str[poi];
	nowNode->setValue(getDataSerialization(value));
	return nowNode;
}

JsonNode* dealObject(JsonNode* nowNode,const std::string& str)
{
	std::string::size_type poi = 0,fpoi = str.size() - 1;
	while(str[poi] != '{')
		poi++;
	while(str[fpoi] != '}')
		fpoi--;
	nowNode->addChild(getChildren(str.substr(poi + 1,fpoi - poi - 1)));
	return nowNode;
}

JsonNode* dealArray(JsonNode* nowNode,const std::string& str)
{
	std::vector<JsonNode*> value;
	std::string::size_type poi = 0,fpoi = str.size() -1;
	while(str[poi] != '[')
		poi++;
	while(str[fpoi] != ']')
		fpoi--;
	value = getChildren(str.substr(poi+1,fpoi - poi - 1));
	nowNode->setValue(getDataSerialization(value));
	return nowNode;
}





























