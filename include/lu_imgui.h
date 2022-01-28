#pragma once

#include <lu_stdlib.h>
#include <details/imgui/imgui.h>

#include <optional>
#include <array>

namespace lu
{
	namespace imgui
	{
		struct window_init_res
		{
			std::array<int, 2> position;
			std::array<int, 2> size;
			std::string		   title;
		};

		struct imgui_init_res
		{
		};

		struct font_init_res
		{
		};

		struct imgui_frame_res
		{
		};

		int app_main(
			std::optional<window_init_res> (*user_window_init_func)(), std::optional<imgui_init_res> (*user_imgui_init_func)(),
			std::optional<font_init_res> (*user_imgui_init_fonts)(), std::optional<imgui_frame_res> (*user_imgui_frame)());
	} // namespace imgui
} // namespace lu