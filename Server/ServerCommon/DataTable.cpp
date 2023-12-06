#include "pch.h"
#include "DataTable.h"

namespace GameServer
{
	DataTable::DataTable(string name)
	{
	}

	DataTable::~DataTable()
	{
	}

	string DataTable::GetName()
	{
		return m_name;
	}

	bool DataTable::Check(Columns& header)
	{
		Columns target;

		//빈값은 무시
		if (header.size() > 0)
		{
			target.reserve(header.size());
			for (auto& str : header)
			{
				if (str.empty()) continue;
				target.push_back(str);
			}
		}

		if (target.size() <= 0) return false;

		//헤더가 같은지 체크
		if (m_header.size() > 0)
		{
			if (m_header.size() != target.size()) return false;
			for (size_t n = 0; n < target.size(); ++n)
			{
				if (m_header[n].compare(target[n]) != 0) return false;
			}

			return true;
		}

		//새로운 헤더 셋팅
		m_header.swap(target);

		return true;
	}

	bool DataTable::Insert(Columns& header)
	{
		return false;
	}

	bool DataTable::Merge(Columns& header)
	{
		return false;
	}

	void DataTable::InitBind()
	{
	}

	void DataTable::Bind(wstring key, int64_t* ptr)
	{
	}

	void DataTable::Bind(wstring key, int32_t* ptr)
	{
	}

	void DataTable::Bind(wstring key, int16_t* ptr)
	{
	}

	void DataTable::Bind(wstring key, int8_t* ptr)
	{
	}

	void DataTable::Bind(wstring key, float* ptr)
	{
	}

	void DataTable::Bind(wstring key, string* ptr)
	{
	}

	void DataTable::Bind(wstring key, bool* ptr)
	{
	}

	void DataTable::InitRead()
	{
	}

	bool DataTable::Read()
	{
		return false;
	}
}