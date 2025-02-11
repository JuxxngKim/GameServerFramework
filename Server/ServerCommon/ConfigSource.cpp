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
			// �������� �̸����� ���ξ�, ���̾ �����Ѵ�.
			//  ���ξ�: Sk2
			//  ���̾�: Server, d
			// NOTE: ����� ������ d�� �ƴ϶�, �����̸��� ������ d�� Ż���ȴ�.

			auto str = FileSystem::GetExecutableFileName();
			auto pattern = "(Sk2)?(.*?)(Server)?(d)?";

			// non-greedy �������� ���� ECMAScript �ɼ� ���
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
