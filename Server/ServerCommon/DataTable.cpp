#include "pch.h"
#include "DataTable.h"

namespace GameServer
{
	DataTable::DataTable(string name)
		: m_name(name)
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

	bool DataTable::Insert(Columns row)
	{
		//입력하려는 데이터체크
		if (m_header.size() < 0) return false;
		if (m_header.size() != row.size()) return false;

		//처음데이터(인덱스로 사용하는 데이터)가 없으면 리턴
		if (row[0].empty()) return false;

		m_rows.emplace_back(row);
		return true;
	}

	bool DataTable::Merge(DataTable& target)
	{
		if (target.m_header.size() != m_header.size()) return false;

		std::move(target.m_rows.begin(), target.m_rows.end(), std::back_inserter(m_rows));
		return true;
	}

	void DataTable::InitBind()
	{
		m_binds.clear();
	}

	void DataTable::Bind(std::wstring key, int64_t* ptr)
	{
		if (key.empty()) return;
		if (ptr == nullptr) return;

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		for (int n = 0; n < m_header.size(); ++n)
		{
			auto target = m_header[n];
			std::transform(target.begin(), target.end(), target.begin(), tolower);

			if (key.compare(target) != 0) continue;

			BindInfo info{};
			info.index = n;
			info.type = EColumn::Int64;
			info.ptr = ptr;
			m_binds.push_back(info);
			return;
		}

		*ptr = 0;
	}

	void DataTable::Bind(wstring key, int32_t* ptr)
	{
		if (key.empty()) return;
		if (ptr == nullptr) return;

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		for (int n = 0; n < m_header.size(); ++n)
		{
			auto target = m_header[n];
			std::transform(target.begin(), target.end(), target.begin(), ::tolower);

			if (key.compare(target) != 0) continue;

			BindInfo info {};
			info.index = n;
			info.type = EColumn::Int32;
			info.ptr = ptr;
			m_binds.push_back(info);
			return;
		}

		*ptr = 0;
	}

	void DataTable::Bind(wstring key, int16_t* ptr)
	{
		if (key.empty()) return;
		if (ptr == nullptr) return;

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		for (int n = 0; n < m_header.size(); ++n)
		{
			auto target = m_header[n];
			std::transform(target.begin(), target.end(), target.begin(), ::tolower);

			if (key.compare(target) != 0) continue;

			BindInfo info{};
			info.index = n;
			info.type = EColumn::Int16;
			info.ptr = ptr;
			m_binds.push_back(info);
			return;
		}

		*ptr = 0;
	}

	void DataTable::Bind(wstring key, int8_t* ptr)
	{
		if (key.empty()) return;
		if (ptr == nullptr) return;

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		for (int n = 0; n < m_header.size(); ++n)
		{
			auto target = m_header[n];
			std::transform(target.begin(), target.end(), target.begin(), ::tolower);

			if (key.compare(target) != 0) continue;

			BindInfo info{};
			info.index = n;
			info.type = EColumn::Int8;
			info.ptr = ptr;
			m_binds.push_back(info);
			return;
		}

		*ptr = 0;
	}

	void DataTable::Bind(wstring key, float* ptr)
	{
		if (key.empty()) return;
		if (ptr == nullptr) return;

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		for (int n = 0; n < m_header.size(); ++n)
		{
			auto target = m_header[n];
			std::transform(target.begin(), target.end(), target.begin(), ::tolower);

			if (key.compare(target) != 0) continue;

			BindInfo info{};
			info.index = n;
			info.type = EColumn::Float;
			info.ptr = ptr;
			m_binds.push_back(info);
			return;
		}

		*ptr = 0.f;
	}

	void DataTable::Bind(wstring key, string* ptr)
	{
		if (key.empty()) return;
		if (ptr == nullptr) return;

		std::transform(key.begin(), key.end(), key.begin(), ::tolower);

		for (int n = 0; n < m_header.size(); ++n)
		{
			auto target = m_header[n];
			std::transform(target.begin(), target.end(), target.begin(), ::tolower);

			if (key.compare(target) != 0) continue;

			BindInfo info{};
			info.index = n;
			info.type = EColumn::Int16;
			info.ptr = ptr;
			m_binds.push_back(info);
			return;
		}

		ptr->clear();
	}

	void DataTable::InitRead()
	{
		m_cur = m_rows.begin();
	}

	bool DataTable::Read()
	{
		if (m_cur == m_rows.end()) return false;

		auto& row = *m_cur;

		if (row.size() != m_header.size()) return false;

		std::wstring tid = row[0];
		for (auto& info : m_binds)
		{
			auto& temp = row[info.index];
			if (temp.compare(L"@") == 0)
			{
				temp.clear();
			}

			//switch (info.type)
			//{
			//case EColumn::Int64:
			//	(*(int64_t*)info.ptr) = StrUtil::ToInt64(temp);
			//	break;
			//case EColumn::Int32:
			//	(*(int32_t*)info.ptr) = StrUtil::ToInt32(temp);
			//	break;
			//case EColumn::Int16:
			//	(*(int16_t*)info.ptr) = StrUtil::ToInt16(temp);
			//	break;
			//case EColumn::Int8:
			//	(*(int8_t*)info.ptr) = StrUtil::ToInt8(temp);
			//	break;
			//case EColumn::Float:
			//	(*(float*)info.ptr) = StrUtil::ToFloat(temp);
			//	break;
			//case EColumn::String:
			//	(*(std::string*)info.ptr) = StrUtil::TOUTF8(temp);
			//	break;
			//}
		}

		++m_cur;
		return true;
	}
}