#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include<vector>
#include"util.hpp"

namespace MEOJ
{
	/*
	*@brief ��һ�����͵����ݽ��д��л�
	*@param T& data ��Ҫ�����л������ݸ�ʽ
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
	*@brief ��һ�����л��������ݽ��н⴮�л�
	*@param const std::vector<unsigned char>& data ��Ҫ���⴮�л������ݸ�ʽ
	*@return const T��ָ�����ͺ�⴮�л��õ�������
	*/
	template<typename T>
	const T getDataFromSerialization(const std::vector<unsigned char>& data)
	{
		auto pData = reinterpret_cast<const T*>(&data[0]);
		return *pData;
	}
}


#endif // SERIALIZATION_HPP
