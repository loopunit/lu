#include <lu_config.h>
#include <lu_stdlib.h>

#include <lu_windows.h>

namespace lu
{
	namespace utf8
	{
		leaf::result<std::string> from_wide_char(std::wstring_view wstr) noexcept
		{
			try
			{
				if (wstr.size() > 0)
				{
					if constexpr (config::operating_system == config::windows_)
					{
						if (auto size_needed = ::WideCharToMultiByte(CP_UTF8, 0, &wstr[0], -1, NULL, 0, NULL, NULL); size_needed > 0)
						{
							std::vector<char> buffer(size_needed);
							if (::WideCharToMultiByte(CP_UTF8, 0, &wstr[0], -1, buffer.data(), size_needed, NULL, NULL) > 0)
							{
								return std::string(buffer.data());
							}
						}
					}
				}
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
			catch (...)
			{
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
		}

		leaf::result<std::wstring> to_wide_char(std::string_view str) noexcept
		{
			try
			{
				if (str.size() > 0)
				{
					if (int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], -1, NULL, 0); size_needed > 0)
					{
						std::vector<wchar_t> buffer(size_needed);
						if (::MultiByteToWideChar(CP_UTF8, 0, &str[0], -1, buffer.data(), size_needed) > 0)
						{
							return std::wstring(buffer.data());
						}
					}
				}
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
			catch (...)
			{
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
		}
	} // namespace utf8
} // namespace lu
