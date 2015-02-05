#ifndef JSONNODE_HPP
#define JSONNODE_HPP

#include"config.hpp"
#include"JSON_TYPE.hpp"
#include<vector>
#include<string>

namespace MEOJ
{
    class JsonNode
    {
    public:
        JsonNode()
        {
            parent = NIL;
            counter = 0;
        }
        ~JsonNode(){}
        std::string key;
        std::vector<JsonNode*>children;
        std::vector<unsigned char>value;
        JSON_TYPE jsonType;
        bool delChild(int index)
        {
            if(index < 0 || index >= children.size())
                return false;
            delete children[index];
            children.erase(children.begin() + index);
            return true;
        }
        bool addChild(JsonNode* child)
        {
            if(child == NIL || child->parent != NIL || child->key.empty())
                return false;
            children.push_back(child);
            child->parent = this;
        }
        JSON_TYPE getJsonType(const std::string& context)
        {
            int i;
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
                return JSON_NUMERIC;
            if(context[i] == '[')
                return JSON_ARRAY;
            if(context[i] == '{')
                return JSON_OBJECT;
            if(context[i] == '\"')
                return JSON_STRING;
            if(context[i] == 't' || context[i] == 'f')
                return JSON_BOOLEAN;
            return JSON_UNKNOWN;
        }
    private:
        JsonNode* parent;
        int counter;
    };
}
#endif // JSON_NODE_HPP

