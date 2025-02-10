#include "pch.h"
#include "StrUtil.h"
#include <codecvt>

namespace sf
{
	namespace StrUtil
	{
		std::string ToLower(std::string str)
		{
			int(*tl)(int) = std::tolower;
			std::transform(str.begin(), str.end(), str.begin(), tl);
			return str;
		}

		std::string ToUTF8(const std::wstring& wstr)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert("");
			return convert.to_bytes(wstr);
		}

		std::wstring ToWSTR(const std::string& u8str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert("", L"");
			return convert.from_bytes(u8str);
		}

		int64_t ToInt64(const std::string& str)
		{
			try
			{
				return std::stoll(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int64_t ToInt64(const std::wstring& str)
		{
			try
			{
				return std::stoll(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int32_t ToInt32(const std::string& str)
		{
			try
			{
				return std::stoi(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int32_t ToInt32(const std::wstring& str)
		{
			try
			{
				return std::stoi(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int16_t ToInt16(const std::string& str)
		{
			try
			{
				return std::stoi(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int16_t ToInt16(const std::wstring& str)
		{
			try
			{
				return std::stoi(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int8_t ToInt8(const std::string& str)
		{
			try
			{
				return std::stoi(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		int8_t ToInt8(const std::wstring& str)
		{
			try
			{
				return std::stoi(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		float ToFloat(const std::string& str)
		{
			try
			{
				return std::stof(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		float ToFloat(const std::wstring& str)
		{
			try
			{
				return std::stof(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		unsigned long ToUnsignedLong(const std::string& str)
		{
			try
			{
				return std::stoul(str);
			}
			catch (...)
			{
				return 0;
			}
		}

		bool IsUTF8(const std::string& str)
		{
			size_t idx = 0;
			size_t total = str.size();
			if (total <= 0)
			{
				return true;
			}

			bool isUTF8 = true;

			while (idx < total && isUTF8)
			{
				int supplemental_bytes = 0;

				if ((str[idx] & 0b11111000) == 0b11110000) {
					++idx;
					supplemental_bytes = 3;
				}
				else if ((str[idx] & 0b11110000) == 0b11100000) {
					++idx;
					supplemental_bytes = 2;
				}
				else if ((str[idx] & 0b11100000) == 0b11000000) {
					++idx;
					supplemental_bytes = 1;
				}
				else if ((str[idx] & 0b10000000) == 0b00000000) {
					++idx;
				}
				else {
					isUTF8 = false;
				}

				while (isUTF8 && supplemental_bytes--)
				{
					if (idx >= total)	isUTF8 = false;
					else if ((str[idx++] & 0xC0) != 0x80)	isUTF8 = false;
				}
			}

			return isUTF8;
		}

		//void Format(std::string& ret, const char* fmt, ...)
		//{
		//	if (fmt == nullptr) return;

		//	va_list arg;

		//	va_start(arg, fmt);

		//	int next = _vscprintf(fmt, arg);
		//	if (next > 0)
		//	{
		//		//_vsnprintf_s �� �������ڸ� �޾ƿö� �ǵڿ� �ι��ڰ� ���ԵǾ ���� ���ڿ� ���̺��� 1 ���
		//		//������ ����� 1 �÷��� ��´�
		//		++next;
		//		ret.resize(next);

		//		//����
		//		_vsnprintf_s((char*)ret.c_str(), next, _TRUNCATE, fmt, arg);

		//		//�ι��� ����
		//		ret.resize(ret.size() - 1);
		//	}

		//	va_end(arg);
		//}

		//std::string ToJson(const google::protobuf::Message& message)
		//{
		//	if (message.GetDescriptor() == nullptr)
		//	{
		//		return message.GetTypeName();
		//	}

		//	std::string str;
		//	google::protobuf::util::JsonPrintOptions op;
		//	//op.add_whitespace = true;
		//	op.always_print_primitive_fields = true;
		//	google::protobuf::util::MessageToJsonString(message, &str, op);
		//	return str;
		//}
	}
}
