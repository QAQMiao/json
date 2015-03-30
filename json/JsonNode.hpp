#ifndef JSONNODE_HPP
#define JSONNODE_HPP

#include "config.hpp"
#include "JSON_TYPE.hpp"
#include "MyException.hpp"
#include "Serialization.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<cstdio>
namespace MEOJ
{
    class JsonNode
    {
	private:
		//Helper方法 ，递归地输出，
		//@param tabs  制表符缩进个数
		//@param pNode 当前遍历的节点
		void displayRecursive(int tabs,JsonNode* pNode)
		{
			std::string typeString;
			switch(pNode -> jsonType)
			{
			case JSON_ARRAY:
				typeString = "jsonArray";break;
			case JSON_STRING:
				typeString = "jsonString";break;
			case JSON_NUMERIC:
				typeString = "jsonNumber";break;
			case JSON_BOOLEAN:
				typeString = "jsonBoolean";break;
			case JSON_OBJECT:
				typeString = "jsonObject";break;
            default:
            	typeString = "jsonUnknown";break;
			}
			for(int i = 0;i < tabs;i++)
			{
				printf("\t");
			}
			std::printf("<node name=\"%s\" type=\"%s\">",
						pNode -> key.c_str(),
						typeString.c_str());
			if(pNode->hasChildren())
				printf("\n");
			if(pNode->jsonType == JSON_ARRAY)
			{
				auto values = pNode -> getValue();
				auto jsonNodes = getVectorDataFromSerialization<JsonNode*>(values);
				if(!jsonNodes.empty())
				{
					printf("\n");
				}
				for(decltype(jsonNodes)::size_type i = 0;i < jsonNodes.size();i++)
				{
					for(int j = 0;j < tabs + 1;j++)
					{
						printf("\t");
					}
					printf("<elem index=\"%d\">\n",i);
					displayRecursive(tabs + 2,jsonNodes[i]);
					for(int j = 0;j < tabs + 1;j++)
					{
						printf("\t");
					}
					printf("</elem>\n");
				}
			}
			switch(pNode -> jsonType)
			{
			case JSON_ARRAY:
                break;
			case JSON_STRING:
				std::cout << getStringDataFromSerialization(pNode -> getValue());
				break;
			case JSON_NUMERIC:
				std::cout << getDataFromSerialization<double>(pNode -> getValue());
				break;
			case JSON_BOOLEAN:
				if(getDataFromSerialization<bool>(pNode->getValue()))
				{
					std::printf("true");
				}
				else
				{
					std::printf("false");
				}
				break;
			case JSON_OBJECT:
			default:
				for(std::vector<JsonNode*>::size_type i = 0;i < pNode->children.size();i++)
				{
					displayRecursive(tabs + 1 , pNode -> children[i]);
				}
				break;
            }

			if(pNode -> hasChildren() || pNode->jsonType == JSON_ARRAY)
			{
				for(int i = 0;i < tabs;i++)
				{
					printf("\t");
				}
			}
			printf("</node>\n");
		}
    public:
        JsonNode()
        {
        	jsonType = JSON_UNKNOWN;
            parent = NIL;
        }
        ~JsonNode()
        {
			if(hasChildren())
			{
				for(std::vector<std::string>::size_type i = 0;i < children.size();i++)
				{
					delChild(i);
				}
			}
        }

    	void display()
    	{
			if(jsonType == JSON_VIRTUAL_ROOT)
			{
				for(decltype(children)::size_type i = 0;i < children.size();i++)
					displayRecursive(0,children[i]);
			}
			else
			{
				displayRecursive(0,this);
			}
    	}

        const std::string& getKey() const
        {
			return key;
        }
        void setKey(std::string key)
		{
			this -> key = key;
		}
		void setValue(const std::vector<unsigned char>& value)
		{
			this -> value = value;
		}
		std::vector<unsigned char> getValue() const
		{
			return value;
		}
        const bool delChild(int index)
        {
            if(index < 0 || index >= int(children.size()))
                return false;
            delete children[index];
            children.erase(children.begin() + index);
            return true;
        }

        const bool addChild(JsonNode* child)
        {
            if(child == NIL || child->parent != NIL || child == this)
                return false;
            children.push_back(child);
            child->parent = this;
            return true;
        }
        const bool addChild(const std::vector<JsonNode*>& child)
        {
			if(child.empty())
				return false;
			children = child;
			return true;
        }
        //根据字符串解析当前节点的json数据类型
		static const JSON_TYPE parseJsonType(const std::string& context)
        {
			JSON_TYPE result;
			//判断json数据类型
            std::string::size_type i;
			int counter = 0;
            for(i = 0;i < context.size();i++)
            {
                if(context[i] == '\"')
                    counter++;
                if(counter >= 2)
                {
                    i++;
                    break;
                }
            }
            while(context[i] == ' ' || context[i] == ':' ||
                  context[i] == '\t' || context[i] == '\n' ||
                  context[i] == '\r')
                i++;
            if(context[i] >= '0' && context[i] <= '9')
                result = JSON_NUMERIC;
            else if(context[i] == '[')
                result = JSON_ARRAY;
            else if(context[i] == '{')
                result = JSON_OBJECT;
            else if(context[i] == '\"')
                result = JSON_STRING;
            else if(context[i] == 't' || context[i] == 'f')
                result = JSON_BOOLEAN;
			//此时应该为错误数据类型
            else throw MyException("文件有问题你丫脑子有病吧！！！你知不知道姐姐写这个多蛋疼！！！");
            return result;
        }
        void setJsonType(JSON_TYPE type)
        {
			jsonType = type;
        }
        //返回当前节点的json数据类型
        const JSON_TYPE getJsonType()
        {
        	return jsonType;
        }
		const bool hasChildren() const
		{
			return !children.empty();
		}
        const bool hasParent() const
        {
			return parent != NIL;
        }
    public: //notice
        std::string key;
        std::vector<JsonNode*>children;
        std::vector<unsigned char> value;
        JSON_TYPE jsonType;
        JsonNode* parent;
    };
}
#endif // JSON_NODE_HPP

