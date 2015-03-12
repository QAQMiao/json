#include "GetChildren.hpp"
#include "JsonNode.hpp"
#include "JSON_TYPE.hpp"

namespace MEOJ{
/*大致就是，先把用户需要解析的string给flcl一遍，分出第一层子节点，然后根据
每段的具体类型，继续划分，直至每个结点都为string、numberic、boolean类型或
最简的array类型【这个我也形容不好，佛曰只可意会不可言传～】*/
	std::vector<JsonNode*> getChildren(std::string context)
	{
		std::vector<JsonNode*>childrens;
		std::vector::size_type cnt = 0;
		std::vector<std::string>smallPart = DiliverContext(context);
		for(std::vector::size_type i = 0;i < smallPart.size();i++)
		{
            JsonNode* nowNode = new JsonNode;
			std::string key = "";
			std::string::size_type position = 0;
			while(smallPart[i][position++] != '\"')
				key += smallPart[i][position - 1];
			setkey(key);
			JSON_TYPE nowType = parseJsonType();
			smallPart[i].substr(position);
			switch(nowType)
			{
				case JSON_STRING:
					dealString(smallPart[i]);break;
				case JSON_BOOLEAN:
					dealBoolean(smallPart[i]);break;
				case JSON_NUMERIC:
					dealNumberic(smallPart[i]);break;
				case JSON_OBJECT:
					dealObject(smallPart[i]);break;
				case JSON_ARRAY:
					dealArray(smallPart[i]);break;
				default:
					break;

			}

		}
		void dealString(const string& str)
		{
			if()
		}
		void dealBoolean(const string& str)
		void dealNumberic(const string& str)
		void dealObject(const string& str)
		void dealArray(const string& str)
	}

}
