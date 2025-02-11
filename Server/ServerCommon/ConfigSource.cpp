#include "pch.h"
#include "ConfigSource.h"
#include "FileSystem.h"

namespace sf
{
	namespace ConfigSource
	{
		std::vector<std::string> MakeInitialConfigFullPaths()
		{
			auto filename = "profile.ini";
			return MakeFullPaths("profile.ini");
		}

		std::vector<std::string> MakeConfigFullPaths(const std::string& env)
		{
			auto filename = "config." + env + ".ini";
			return MakeFullPaths(filename);
		}

		std::vector<std::string> MakeFullPaths(const std::string& filename)
		{
			auto dirname = GetConfigDirName();
			auto local = dirname + "_" + filename;
			auto config = dirname + filename;

			std::vector<std::string> result;
			if (FileSystem::Exist(local)) result.push_back(local);
			result.push_back(config);

			return result;
		}

		std::string MakeServiceName()
		{
			// 실행파일 이름에서 접두어, 접미어를 제거한다.
			//  접두어: Sk2
			//  접미어: Server, d
			// NOTE: 디버그 빌드의 d가 아니라도, 파일이름의 마지막 d는 탈락된다.

			auto str = FileSystem::GetExecutableFileName();
			auto pattern = "(Sk2)?(.*?)(Server)?(d)?";

			// non-greedy 연산사용을 위해 ECMAScript 옵션 사용
			std::regex r(pattern, std::regex::ECMAScript | std::regex::icase);
			std::smatch m;

			if (std::regex_match(str, m, r))
			{
				return m[2].str();	// (.*?) non-greedy
			}

			return "";
		}

		std::string GetConfigDirName()
		{
			auto dirname = FileSystem::GetExecutableDirName();
			auto relativeDir = "config\\";

			return dirname + relativeDir;
		}
	}
}
