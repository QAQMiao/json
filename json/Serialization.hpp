#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include<vector>
#include<string>
#include"util.hpp"

namespace MEOJ
{
	struct vectorWrap
	{
		unsigned int chunks;
		unsigned char* dataBytes;
	};
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

	template<typename T>
	const std::vector<unsigned char> getVectorDataSerialization(std::vector<T>& data)
	{
		vectorWrap result;
		result.chunks = data.size() * sizeof(T);
		result.dataBytes = new unsigned char[result.chunks];
		for(typename std::vector<T>::size_type i = 0;i < data.size();i++)
		{
			*reinterpret_cast<T*>(result.dataBytes + (i * sizeof(T))) = data[i];
		}
		return getDataSerialization(result);
	}

	template<typename T>
	const std::vector<T> getVectorDataFromSerialization(const std::vector<unsigned char>& data)
	{
		vectorWrap result = getDataFromSerialization<vectorWrap>(data);
		std::vector<T> realResult;
		realResult.resize(result.chunks / sizeof(T));
		for(int i = 0;i < realResult.size() ;i++)
		{
			realResult[i] = *reinterpret_cast<T*>(result.dataBytes + (i * sizeof(T)));
		}
		delete [] result.dataBytes;
		return realResult;
	}
	const std::vector<unsigned char> getStringDataSerialization(std::string& data);
	const std::string getStringDataFromSerialization(const std::vector<unsigned char>& data);
}


#endif // SERIALIZATION_HPP
