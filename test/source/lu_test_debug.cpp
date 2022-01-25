#include <doctest/doctest.h>
#include <lu_stdlib.h>

TEST_CASE("lu_test_debug")
{
	lu::debug::begin_new_process();
	lu::debug::capture_and_log_stack_trace(lu::log::to_stdout(), spdlog::level::info);
}
