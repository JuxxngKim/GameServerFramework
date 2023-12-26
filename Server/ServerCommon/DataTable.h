#pragma once

namespace GameServer
{
	class DataTable
	{
	public:
		using Columns = std::vector<std::wstring>;
		using Rows = std::vector<Columns>;

		enum class EColumn
		{
			None,
			Int64,
			Int32,
			Int16,
			Int8,
			Float,
			String,
		};

		struct BindInfo
		{
			int index;
			EColumn type;
			void* ptr;
		};

		using Binds = list<BindInfo>;

	protected:
		string m_name;
		Columns m_header;
		Rows m_rows;
		Rows::iterator m_cur;

		Binds m_binds;

	public:
		DataTable() = delete;
		DataTable(string name);
		virtual ~DataTable();

	public:
		string GetName();

	public:
		bool Check(Columns& header);
		bool Insert(Columns header);
		bool Merge(DataTable& header);

	public:
		void InitBind();
		void Bind(wstring key, int64_t* ptr);
		void Bind(wstring key, int32_t* ptr);
		void Bind(wstring key, int16_t* ptr);
		void Bind(wstring key, int8_t* ptr);
		void Bind(wstring key, float* ptr);
		void Bind(wstring key, string* ptr);

	public:
		void InitRead();
		bool Read();
	};
}