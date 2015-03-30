#include "GetChildren.hpp"
using namespace MEOJ;
/*大致就是，先把用户需要解析的string给flcl一遍，分出第一层子节点，然后根据
每段的具体类型，继续划分，直至每个结点都为string、numberic、boolean类型或
最简的array类型【这个我也形容不好，佛曰只可意会不可言传～】*/

//叫着getChildren,实际上却是getValue的功能，鉴于实在不相信哈士奇的捣乱，觉得勉强这么叫着
//上一条注释是错的。。。就是getChildren。。逻辑一下子没捋明白- -
std::vector<JsonNode*> MEOJ::getChildren(const std::string& context)
{
	std::string::size_type poi = 0,fpoi = context.size() - 1;
	//std::cout << context << std::endl;
	while(context[poi] == ' ' || context[poi] == '\n' || context[poi] == '\r' || context[poi] == '\t')
		poi++;
	if(context[poi] == '{')
	{
		poi++;
		while(context[fpoi] != '}')
			fpoi--;
	}
	else
	{
		fpoi = context.size() + 1;
		poi--;
	}
	std::vector<JsonNode*>childrens;
	std::vector<std::string>smallPart = diliverContext(context.substr(poi + 1,fpoi - poi - 1));
//	for(std::vector<std::string>::size_type i = 0;i < smallPart.size();i++)
//		std::cout<<smallPart[i]<<std::endl;
	for(std::vector<std::string>::size_type i = 0;i < smallPart.size();i++)
	{
		JsonNode* nowNode = new JsonNode;
		std::string key = "";
		std::string::size_type position = 0;
		while(smallPart[i][position++] != '\"');
		while(smallPart[i][position++] != '\"')
			key += smallPart[i][position - 1];
		nowNode->setKey(key);
		JSON_TYPE nowType = JsonNode::parseJsonType(smallPart[i]);
		nowNode->setJsonType(nowType);
		smallPart[i] = smallPart[i].substr(position);
		switch(nowType)
		{
			case JSON_STRING:
				childrens.push_back(dealString(nowNode,smallPart[i]));
				break;
			case JSON_BOOLEAN:
				childrens.push_back(dealBoolean(nowNode,smallPart[i]));
				break;
			case JSON_NUMERIC:
				childrens.push_back(dealNumberic(nowNode,smallPart[i]));
				break;
			case JSON_OBJECT:
				childrens.push_back(dealObject(nowNode,smallPart[i]));
				break;
			case JSON_ARRAY:
				childrens.push_back(dealArray(nowNode,smallPart[i]));
				break;
			case JSON_UNKNOWN:
				std::cout<<"这是什么鬼"<<std::endl;break;
			default:
				break;
		}
//        for(std::vector<JsonNode*>::size_type i = 0;i < childrens.size();i++)
//			std::cout<<childrens[i]->value[0]<<std::endl;
	}
	return childrens;
}

std::vector<unsigned char> MEOJ::getArrayValue(const std::string& context)
{
	std::cout<<context<<std::endl;
	std::vector<std::string> smallPart = diliverContext(context);
	std::vector<JsonNode*> value;
//	std::cout<<"----------------------"<<std::endl;
//	std::cout<<smallPart.size()<<std::endl;
	for(std::vector<std::string>::size_type i = 0 ;i < smallPart.size();i++)
		std::cout << smallPart[i] << std::endl;
	for(std::vector<std::string>::size_type i = 0 ;i < smallPart.size();i++)
	{
		JsonNode* nowNode = new JsonNode;
		std::string tmp = "\"aa\":" + smallPart[i];
		JSON_TYPE nowType = JsonNode::parseJsonType(tmp);
		std::cout << nowType << std::endl;
		switch(nowType)
		{
			case JSON_STRING:
				value.push_back(dealString(nowNode,smallPart[i]));
				break;
			case JSON_BOOLEAN:
				value.push_back(dealBoolean(nowNode,smallPart[i]));
				break;
			case JSON_NUMERIC:
				value.push_back(dealNumberic(nowNode,smallPart[i]));
				break;
			case JSON_OBJECT:
				value.push_back(dealObject(nowNode,smallPart[i]));
				break;
			case JSON_ARRAY:
				value.push_back(dealArray(nowNode,smallPart[i]));
				break;
			case JSON_UNKNOWN:
				std::cout << "这是什么鬼" << std::endl;
				break;
			default:
				break;
		}
//		for(std::vector<JsonNode*>::size_type i = 0;i < value.size();i++ )
//			std::cout << value[i] -> key << std::endl;
		std::cout<<"----"<<std::endl;
		return getDataSerialization(value);

	}
}

JsonNode* MEOJ::dealString(JsonNode* nowNode,const std::string& str)
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
		std::cout << value << std::endl;
	}
	nowNode->setValue(getDataSerialization(value));
	return nowNode;
}

JsonNode* MEOJ::dealBoolean(JsonNode* nowNode,const std::string& str)
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

JsonNode* MEOJ::dealNumberic(JsonNode* nowNode,const std::string& str)
{
	std::string::size_type poi = 0;
	while(str[poi] < '0' || str[poi] > '9')
		poi++;
	double value = 0;
	while(poi < str.size() && (str[poi] >= '0' && str[poi] <= '9') || str[poi] == '.')
		value = value * 10 + str[poi++] - '0';
	//std::cout<<value<<std::endl;
	nowNode->setValue(getDataSerialization(value));
	return nowNode;
}

JsonNode* MEOJ::dealObject(JsonNode* nowNode,const std::string& str)
{
	std::string::size_type poi = 0,fpoi = str.size() - 1;
	while(str[poi] != '{')
		poi++;
	while(str[fpoi] != '}')
		fpoi--;
	nowNode->addChild(getChildren(str.substr(poi + 1,fpoi - poi - 1)));
	return nowNode;
}

JsonNode* MEOJ::dealArray(JsonNode* nowNode,const std::string& str)
{
//	std::vector<JsonNode*> value;
	std::string::size_type poi = 0,fpoi = str.size() -1;
	while(str[poi] != '[')
		poi++;
	while(str[fpoi] != ']')
		fpoi--;
//	value = getChildren(str.substr(poi+1,fpoi - poi - 1));
	nowNode->setValue(getArrayValue(str.substr(poi+1,fpoi - poi - 1)));
	return nowNode;
}


