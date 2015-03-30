#include "Serialization.hpp"
using namespace MEOJ;


const std::vector<unsigned char> MEOJ::getStringDataSerialization(std::string& data)
{
	vectorWrap result;
	result.chunks = data.size();
	result.dataBytes = new unsigned char[result.chunks];
	for(int i=0;i<data.size();i++)
	{
		result.dataBytes[i] = data[i];
	}
	return getDataSerialization(result);
}
const std::string MEOJ::getStringDataFromSerialization(const std::vector<unsigned char>& data)
{
	vectorWrap result = getDataFromSerialization<vectorWrap>(data);
	std::string realResult;
	for(int i=0;i<result.chunks;i++)
	{
		realResult += result.dataBytes[i];
	}
	delete [] result.dataBytes;
	return realResult;
}
