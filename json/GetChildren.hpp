#ifndef GETCHILDREN_HPP
#define GETCHILDREN_HPP

#include<cstdio>
#include<string>
#include<vector>

namespace MEOJ
{
	JsonNode* getChildren(std::string context);
	void dealString(const string& str);
	void dealBoolean(const string& str);
	void dealNumberic(const string& str);
	void dealObject(const string& str);
	void dealArray(const string& str);
}
#endif // GETCHILDREN_HPP
