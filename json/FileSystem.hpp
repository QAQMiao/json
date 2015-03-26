#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include<cstdio>
#include<string>
#include"config.hpp"

namespace MEOJ
{
	class FileSystem
	{
	public:
		//根据文件路径读取文件内容
		static const std::string readFileContext(const char* fileName)
		{
			std::FILE* fp = NIL;
			std::string fileContext;
			fp = std::fopen(fileName,"r");
			//此时fp仍然为null值则读取文件失败，返回false
			if(!fp)
			{
				return "";
			}
			fileContext = "";
			while(!std::feof(fp))
			{
				fileContext += std::fgetc(fp);
			}
			if(!!fp)
			{
				std::fclose(fp);
			}
			return fileContext;
		}
		static bool writeFileContext(const char* fileName,const std::string& fileContext)
		{
			std::FILE* fp = NIL;
			fp = std::fopen(fileName,"w");
			if(!fp)
			{
				return false;
			}
			for(std::string::size_type i = 0;i < fileContext.length(); i++)
			{
				std::fputc(fileContext[i],fp);
			}
			if(!!fp)
			{
				std::fclose(fp);
			}
			return true;
		}
	};
}


#endif // FILESYSTEM_HPP
