#include <doctest/doctest.h>
#include <lu_stdlib.h>

TEST_CASE("[stdout]")
{
	auto l = &lu::log::to_stdout();
	l->set_pattern("%+");
	l->set_level(spdlog::level::trace);
	l->trace("Test stdout_st");
	spdlog::drop_all();

	l->set_pattern("%+");
	l->set_level(spdlog::level::debug);
	l->debug("Test stdout_mt");
	spdlog::drop_all();

	l->set_pattern("%+");
	l->info("Test stdout_color_st");
	spdlog::drop_all();

	l->set_pattern("%+");
	l->set_level(spdlog::level::trace);
	l->trace("Test stdout_color_mt");
	spdlog::drop_all();
}

TEST_CASE("[stderr]")
{
	auto l = &lu::log::to_stderr();
	l->set_pattern("%+");
	l->info("Test stderr_st");
	spdlog::drop_all();

	l->set_pattern("%+");
	l->info("Test stderr_mt");
	l->warn("Test stderr_mt");
	l->error("Test stderr_mt");
	l->critical("Test stderr_mt");
	spdlog::drop_all();

	l->set_pattern("%+");
	l->set_level(spdlog::level::debug);
	l->debug("Test stderr_color_st");
	spdlog::drop_all();

	l->set_pattern("%+");
	l->info("Test stderr_color_mt");
	l->warn("Test stderr_color_mt");
	l->error("Test stderr_color_mt");
	l->critical("Test stderr_color_mt");
	spdlog::drop_all();
}

TEST_CASE("lu_test_01")
{
}
