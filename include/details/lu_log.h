#pragma once

#include <lu_config.h>

#include "lu_error.h"

#ifndef SPDLOG_COMPILED_LIB
#define SPDLOG_COMPILED_LIB 1
#endif
#include <spdlog/spdlog.h>

namespace lu
{
	namespace log
	{
		spdlog::logger& to_stdout() noexcept;
		spdlog::logger& to_stderr() noexcept;
	} // namespace log
} // namespace lu