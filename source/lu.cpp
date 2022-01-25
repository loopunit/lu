#if defined(_WIN32) || defined(WIN32)
#include <stdexcept>

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // #ifndef WIN32_LEAN_AND_MEAN

#include <objbase.h>
#include <timeapi.h>
#include <windows.h>

namespace lu
{
	// overriding the windows formatmessage handler
	auto custom_formatmessage(
		unsigned long dwFlags,
		const void*	  lpSource,
		unsigned long dwMessageId,
		unsigned long dwLanguageId,
		char*		  lpBuffer,
		unsigned long nSize,
		va_list*	  Arguments) noexcept -> unsigned long
	{
		return ::FormatMessageA(dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments);
	}

	auto custom_getlasterror() noexcept -> unsigned long
	{
		return ::GetLastError();
	}

	auto custom_localfree(void* hMem) noexcept -> void
	{
		::LocalFree(hMem);
	}

} // namespace lu
#endif // #if defined(_WIN32) || defined(WIN32)

#include <lu_config.h>
#include <boost/config.hpp>
