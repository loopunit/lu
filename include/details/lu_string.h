#pragma once

#include <lu_config.h>

#include "lu_error.h"

#include <spdlog/fmt/fmt.h>
#include <string>
#include <details/tinyutf8.h>

namespace lu
{
	namespace utf8
	{
		using namespace tiny_utf8;

		leaf::result<std::string>  from_wide_char(std::wstring_view wstr) noexcept;
		leaf::result<std::wstring> to_wide_char(std::string_view str) noexcept;
	} // namespace utf8
} // namespace lu