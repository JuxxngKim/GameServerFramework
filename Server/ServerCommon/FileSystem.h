#pragma once

namespace sf
{
	namespace FileSystem
	{
		std::string GetExecutableFullPath();
		std::string GetExecutableFileName();
		std::string GetExecutableDirName();
		bool Exist(const std::string& path);

		std::vector<std::string> CommandLineToArgv();
	};
}