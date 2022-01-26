#pragma once

#include <boost/predef.h>
#include <boost/config.hpp>

#include "details/spy.hpp"

#ifdef SPY_OS_IS_WINDOWS
#define LU_OS_IS_WINDOWS (1)
#else
#define LU_OS_IS_WINDOWS (0)
#endif

#ifdef SPY_OS_IS_ANDROID
#define LU_OS_IS_ANDROID (1)
#else
#define LU_OS_IS_ANDROID (0)
#endif

#ifdef SPY_OS_IS_BSD
#define LU_OS_IS_BSD (1)
#else
#define LU_OS_IS_BSD (0)
#endif

#ifdef SPY_OS_IS_CYGWIN
#define LU_OS_IS_CYGWIN (1)
#else
#define LU_OS_IS_CYGWIN (0)
#endif

#ifdef SPY_OS_IS_IOS
#define LU_OS_IS_IOS (1)
#else
#define LU_OS_IS_IOS (0)
#endif

#ifdef SPY_OS_IS_LINUX
#define LU_OS_IS_LINUX (1)
#else
#define LU_OS_IS_LINUX (0)
#endif

#ifdef SPY_OS_IS_MACOS
#define LU_OS_IS_MACOS (1)
#else
#define LU_OS_IS_MACOS (0)
#endif

#ifdef SPY_OS_IS_UNIX
#define LU_OS_IS_UNIX (1)
#else
#define LU_OS_IS_UNIX (0)
#endif

#ifdef SPY_OS_IS_WINDOWS
#define LU_OS_IS_WINDOWS (1)
#else
#define LU_OS_IS_WINDOWS (0)
#endif

#ifdef SPY_OS_IS_UNKNOWN
#define LU_OS_IS_UNKNOWN (1)
#else
#define LU_OS_IS_UNKNOWN (0)
#endif

#define LU_OS_IS_VALID (LU_OS_IS_WINDOWS || LU_OS_IS_IOS || LU_OS_IS_MACOS || LU_OS_IS_LINUX)
#define LU_OS_IS_DX12 (LU_OS_IS_WINDOWS)
#define LU_OS_IS_VULKAN (LU_OS_IS_LINUX)
#define LU_OS_IS_METAL (LU_OS_IS_IOS || LU_OS_IS_MACOS)
#define LU_OS_IS_WIN32 (LU_OS_IS_WINDOWS)
#define LU_OS_IS_GLFW (!LU_OS_IS_WIN32)

namespace lu
{
	namespace config = ::spy;
	using namespace config::literal;
} // namespace lu
