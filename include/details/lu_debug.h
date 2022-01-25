#pragma once

#include <lu_config.h>

#include "lu_error.h"
#include "lu_string.h"
#include "lu_filesystem.h"

namespace lu
{
	namespace debug
	{
		void begin_new_process() noexcept;

		void capture_and_log_stack_trace(spdlog::logger& l, spdlog::level::level_enum lvl) noexcept;
	} // namespace debug
} // namespace lu
