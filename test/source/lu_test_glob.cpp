#include <doctest/doctest.h>
#include <lu_stdlib.h>

TEST_CASE("lu_glob")
{
	auto get_test_glob = []() noexcept -> lu::leaf::result<std::vector<lu::filesystem::path>>
	{
		if constexpr (::lu::config::operating_system == ::lu::config::windows_)
		{
			return lu::filesystem::rglob("~\\Desktop\\**");
		}
		else
		{
			return lu::filesystem::rglob("~/**");
		}
	};
	
	if (auto matches = get_test_glob())
	{
		for (auto& match : *matches)
		{
			if (auto u8_str = ::lu::filesystem::path_to_string(match))
			{
				::printf("%s\n", u8_str->c_str());
			}
		}
	}
	else
	{
		throw lu::leaf::exception(matches.error());
	}
}
