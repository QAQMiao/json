#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include<vector>
#include"util.hpp"

namespace MEOJ
{
	/*
	*@brief 将一个类型的数据进行串行化
	*@param T& data 需要被串行化的数据格式
	*@return const std::vector<unsigned char>
	*/
	template<typename T>
	const std::vector<unsigned char> getDataSerialization(T& data)
	{
		auto pData = reinterpret_cast<unsigned char*>(getAddressOf(data));
		std::vector<unsigned char> result;
		result.resize(sizeof(T));
		for(std::vector<unsigned char>::size_type i = 0;i < result.size();i++)
		{
			result[i] = pData[i];
		}
		return result;
	}
	/*
	*@brief 将一个串行化过的数据进行解串行化
	*@param const std::vector<unsigned char>& data 需要被解串行化的数据格式
	*@return const T　指定类型后解串行化得到的数据
	*/
	template<typename T>
	const T getDataFromSerialization(const std::vector<unsigned char>& data)
	{
		auto pData = reinterpret_cast<const T*>(&data[0]);
		return *pData;
	}
}


#endif // SERIALIZATION_HPP
