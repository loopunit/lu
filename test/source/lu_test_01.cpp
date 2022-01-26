#include <doctest/doctest.h>
#include <lu_stdlib.h>

int imgui_main(int, char**);

TEST_CASE("lu_test_01")
{
	imgui_main(0, nullptr);
}
