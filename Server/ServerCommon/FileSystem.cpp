#include "pch.h"
#include "FileSystem.h"
#include <fstream>
//#include <shellapi.h>

namespace sf
{
	namespace FileSystem
	{
		std::string GetExecutableFullPath()
		{
			char buffer[MAX_PATH];
			::GetModuleFileNameA(nullptr, buffer, MAX_PATH);

			return buffer;
		}

		std::string GetExecutableFileName()
		{
			auto fullPath = GetExecutableFullPath();

			char filename[MAX_PATH];
			_splitpath(fullPath.c_str(), nullptr, nullptr, filename, nullptr);

			return filename;
		}

		std::string GetExecutableDirName()
		{
			auto fullPath = GetExecutableFullPath();

			char drive[MAX_PATH];
			char dir[MAX_PATH];
			_splitpath(fullPath.c_str(), drive, dir, nullptr, nullptr);

			return std::string(drive) + std::string(dir);
		}

		bool Exist(const std::string& path)
		{
			std::ifstream f(path);
			return f.good();
		}

		std::vector<std::string> CommandLineToArgv()
		{
			std::vector<std::string> result;

			int argc{};
			auto args = ::CommandLineToArgvW(::GetCommandLineW(), &argc);

			for (int i = 0; i < argc; i++)
			{
				//result.push_back(StrUtil::ToUTF8(args[i]));
			}

			return result;
		}
	}
}