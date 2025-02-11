#pragma once
#include <map>
#include <string>
#include <vector>

namespace sf
{
	class IniSection;

	class IniFile
	{
	private:
		std::map<std::string, IniSection> m_sections;

	public:
		bool Load(const std::string& filePath);
		const IniSection& Get(const std::string& section) const;
		IniSection& Mutable(const std::string& section);

	private:
		bool LoadSections(const std::vector<std::string>& sectionNames, const std::string& filePath);
	};
}
