#include "pch.h"
#include "FileSystem.h"
#include <fstream>
#include "StrUtil.h"

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

			errno_t err = _splitpath_s(fullPath.c_str(),
				nullptr, 0,       // drive 정보 없음
				nullptr, 0,       // dir 정보 없음
				filename, MAX_PATH, // 파일명
				nullptr, 0);      // 확장자 정보 없음
			if (err != 0) {
				// 에러 처리 (필요시)
			}

			return std::string(filename);
		}

		std::string GetExecutableDirName()
		{
			auto fullPath = GetExecutableFullPath();

			char drive[MAX_PATH];
			char dir[MAX_PATH];
			errno_t err = _splitpath_s(fullPath.c_str(),
				drive, MAX_PATH,  // 드라이브 정보
				dir, MAX_PATH,    // 디렉토리 정보
				nullptr, 0,       // 파일명 정보 없음
				nullptr, 0);      // 확장자 정보 없음

			if (err != 0) {
				// 에러 처리 (필요시)
			}

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
				result.push_back(StrUtil::ToUTF8(args[i]));
			}

			return result;
		}
	}
}