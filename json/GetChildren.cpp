#include "GetChildren.hpp"

namespace MEOJ{
/*大致就是，先把用户需要解析的string给flcl一遍，分出第一层子节点，然后根据
每段的具体类型，继续划分，直至每个结点都为string、numberic、boolean类型或
最简的array类型【这个我也形容不好，佛曰只可意会不可言传～】*/
	std::vector<JsonNode*> getChildren(std::string context)
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
			JSON_TYPE nowType = nowNode->parseJsonType(smallPart[i]);
			smallPart[i].substr(position);
			switch(nowType)
			{
				case JSON_STRING:
					dealString(nowNode,smallPart[i]);break;
				case JSON_BOOLEAN:
					dealBoolean(nowNode,smallPart[i]);break;
				case JSON_NUMERIC:
					dealNumberic(nowNode,smallPart[i]);break;
				case JSON_OBJECT:
					dealObject(nowNode,smallPart[i]);break;
				case JSON_ARRAY:
					dealArray(nowNode,smallPart[i]);break;
				default:
					break;

			}

		}

	}
	void dealString(JsonNode* nowNode,const std::string& str)
	{
		std::string::size_type poi = 0;
		while(str[poi] != '\"')
			poi++;
		std::string value;
		while(poi < str.size())
		{
			if(str[++poi] == '\"' && str[poi - 1] != '\\')
				break;
			value += str[poi];
		}
		nowNode->setValue(getDataSerialization(value));

	}
	void dealBoolean(JsonNode* nowNode,const std::string& str)
	{
		;
	}
	void dealNumberic(JsonNode* nowNode,const std::string& str)
	{
		;
	}
	void dealObject(JsonNode* nowNode,const std::string& str)
	{
		;
	}
	void dealArray(JsonNode* nowNode,const std::string& str)
	{
		;
	}
}










































