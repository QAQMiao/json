#include"DiliverContext.hpp"
using namespace MEOJ;


std::vector<std::string> MEOJ::diliverContext(const std::string& context)
{
	std::vector<std::string> result;
	std::string nowString;
	std::string::size_type i;
	int cn1 = 0,cn2 = 0,cn3 = 0;			//分别记录引号花括号大括号的匹配情况
	for(i = 0;i < context.size();i++)
	{
		switch(context[i])
		{
		case '\"':
			cn1 = !cn1;break;
		case '[':
			cn2++;break;
		case ']':
			cn2--;break;
		case '{':
			cn3++;break;
		case '}':
			cn3--;break;
		default:
			break;
		}
		if(!cn1 && cn2 && cn3 && context[i] == ',')
		{
			result.push_back(nowString);
			nowString = "";
			continue;
		}
		nowString += context[i];
	}
	return result;
}


