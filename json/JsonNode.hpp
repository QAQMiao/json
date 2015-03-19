#ifndef JSONNODE_HPP
#define JSONNODE_HPP

#include "config.hpp"
#include "JSON_TYPE.hpp"
#include "MyException.hpp"
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
			switch(pNode->jsonType)
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
						pNode->key.c_str(),
						typeString.c_str());
			if(pNode->hasChildren())
				printf("\n");
			for(std::vector<JsonNode*>::size_type i = 0;i < pNode->children.size();i++)
			{
				displayRecursive(tabs + 1 , pNode->children[i]);
			}
			if(pNode->hasChildren())
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
			displayRecursive(0,this);
    	}

        const std::string& getKey() const
        {
			return key;
        }
        void setKey(std::string key)
		{
			this->key = key;
		}
		void setValue(std::vector<unsigned char> value)
		{
			this->value = value;
		}
		const std::vector<unsigned char> getValue() const
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
        //根据字符串解析当前节点的json数据类型
        const JSON_TYPE parseJsonType(const std::string& context)
        {
			//如果已经处理过了，直接返回值
        	if(jsonType != JSON_UNKNOWN)
			{
				return jsonType;
			}
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
                jsonType = JSON_NUMERIC;
            else if(context[i] == '[')
                jsonType = JSON_ARRAY;
            else if(context[i] == '{')
                jsonType = JSON_OBJECT;
            else if(context[i] == '\"')
                jsonType = JSON_STRING;
            else if(context[i] == 't' || context[i] == 'f')
                jsonType = JSON_BOOLEAN;
			//此时应该为错误数据类型
            else throw MyException("文件有问题你丫脑子有病吧！！！你知不知道姐姐写这个多蛋疼！！！");
            return jsonType;
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
    private:
        std::string key;
        std::vector<JsonNode*>children;
        std::vector<unsigned char> value;
        JSON_TYPE jsonType;
        JsonNode* parent;
    };
}
#endif // JSON_NODE_HPP

