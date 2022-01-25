#pragma once

#include <lu_config.h>

// TODO: leaf pulls in Windows.h via common.hpp, so we bypass that here to avoid the mess.
// if something did pull in windows.h, this is fine. custom_formatmessage, etc. are just a wrappers.
#ifndef _WINDOWS_

#ifndef LPVOID
#define LPVOID void*
#define LPVOID_redefined
#endif
#ifndef LPCSTR
#define LPCSTR char*
#define LPCSTR_redefined
#endif

namespace lu
{
	auto custom_formatmessage(
		unsigned long dwFlags,
		const void*	  lpSource,
		unsigned long dwMessageId,
		unsigned long dwLanguageId,
		char*		  lpBuffer,
		unsigned long nSize,
		va_list*	  Arguments) noexcept -> unsigned long;

	auto custom_getlasterror() noexcept -> unsigned long;

	auto custom_localfree(void* hMem) noexcept;
} // namespace lu

#define FormatMessageA(DWORD_dwFlags, LPCVOID_lpSource, DWORD_dwMessageId, DWORD_dwLanguageId, LPSTR_lpBuffer, DWORD_nSize, va_list_Arguments)                                     \
	::lu::custom_formatmessage(DWORD_dwFlags, LPCVOID_lpSource, DWORD_dwMessageId, DWORD_dwLanguageId, LPSTR_lpBuffer, DWORD_nSize, va_list_Arguments)
#define GetLastError		   ::lu::custom_getlasterror
#define LocalFree(HLOCAL_hMem) ::lu::custom_getlasterror(HLOCAL_hMem)
#define _WINDOWS_
#define _WINDOWS_redefined			   true
#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_FROM_SYSTEM	   0x00001000
#define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
#define MAKELANGID(p, s)			   ((((unsigned short)(s)) << 10) | (unsigned short)(p))
#define LANG_NEUTRAL				   0x00
#define SUBLANG_DEFAULT				   0x01
#define LPSTR						   char*
#else // #ifndef _WINDOWS_
#define _WINDOWS_redefined false
#endif // #else // #ifndef _WINDOWS_
#include <boost/leaf.hpp>
#if _WINDOWS_redefined
#ifdef LPVOID_redefined
#undef LPVOID
#undef LPVOID_redefined
#endif
#ifdef LPCSTR_redefined
#undef LPCSTR_redefined
#undef LPCSTR
#endif
#undef FormatMessageA
#undef GetLastError
#undef LocalFree
#undef _WINDOWS_
#undef _WINDOWS_redefined
#undef FORMAT_MESSAGE_ALLOCATE_BUFFER
#undef FORMAT_MESSAGE_FROM_SYSTEM
#undef FORMAT_MESSAGE_IGNORE_INSERTS
#undef MAKELANGID
#undef LANG_NEUTRAL
#undef SUBLANG_DEFAULT
#undef LPSTR
#endif // #if _WINDOWS_redefined

namespace lu
{
	namespace leaf = boost::leaf;

	struct common_error
	{
	};

	struct runtime_error
	{
		struct not_specified : common_error
		{
		};
	};
} // namespace lu

#define LU_LEAF_IF_REPORT(r)                                                                                                                                                       \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(BOOST_LEAF_TMP)>::type>::value, "LU_LEAF_CHECK requires a result object (see is_result_type)");       \
	if (!BOOST_LEAF_TMP)                                                                                                                                                           \
		/*TODO: REPORT*/;                                                                                                                                                          \
	else

#define LU_LEAF_RETHROW(r)                                                                                                                                                         \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(::boost::leaf::is_result_type<typename std::decay<decltype(BOOST_LEAF_TMP)>::type>::value, "LU_LEAF_CHECK requires a result object (see is_result_type)");       \
	if (BOOST_LEAF_TMP)                                                                                                                                                            \
		;                                                                                                                                                                          \
	else                                                                                                                                                                           \
	{                                                                                                                                                                              \
		throw BOOST_LEAF_TMP.error();                                                                                                                                              \
	}

#define LU_LEAF_ASSIGN(v, r)                                                                                                                                                       \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(                                                                                                                                                                 \
		::boost::leaf::is_result_type<std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,                                                                                          \
		"LU_LEAF_ASSIGN and LU_LEAF_AUTO require a result object as the second argument (see is_result_type)");                                                                    \
	if (!BOOST_LEAF_TMP)                                                                                                                                                           \
	{                                                                                                                                                                              \
		return BOOST_LEAF_TMP.error();                                                                                                                                             \
	}                                                                                                                                                                              \
	v = std::forward<decltype(BOOST_LEAF_TMP)>(BOOST_LEAF_TMP).value()

#define LU_LEAF_PUSH_BACK(v, r)                                                                                                                                                    \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(                                                                                                                                                                 \
		::boost::leaf::is_result_type<std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,                                                                                          \
		"LU_LEAF_ASSIGN and LU_LEAF_AUTO require a result object as the second argument (see is_result_type)");                                                                    \
	if (!BOOST_LEAF_TMP)                                                                                                                                                           \
	{                                                                                                                                                                              \
		return BOOST_LEAF_TMP.error();                                                                                                                                             \
	}                                                                                                                                                                              \
	v.push_back(std::forward<decltype(BOOST_LEAF_TMP)>(BOOST_LEAF_TMP).value())

#define LU_LEAF_EMPLACE_BACK(v, r)                                                                                                                                                 \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(                                                                                                                                                                 \
		::boost::leaf::is_result_type<std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,                                                                                          \
		"LU_LEAF_ASSIGN and LU_LEAF_AUTO require a result object as the second argument (see is_result_type)");                                                                    \
	if (!BOOST_LEAF_TMP)                                                                                                                                                           \
	{                                                                                                                                                                              \
		return BOOST_LEAF_TMP.error();                                                                                                                                             \
	}                                                                                                                                                                              \
	v.emplace_back(std::forward<decltype(BOOST_LEAF_TMP)>(BOOST_LEAF_TMP).value())

#define LU_LEAF_AUTO(v, r) LU_LEAF_ASSIGN(auto v, r)

#define LU_LEAF_ASSIGN_THROW(v, r)                                                                                                                                                 \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(                                                                                                                                                                 \
		::boost::leaf::is_result_type<std::decay<decltype(BOOST_LEAF_TMP)>::type>::value,                                                                                          \
		"LU_LEAF_ASSIGN and LU_LEAF_AUTO require a result object as the second argument (see is_result_type)");                                                                    \
	if (!BOOST_LEAF_TMP)                                                                                                                                                           \
	{                                                                                                                                                                              \
		throw BOOST_LEAF_TMP.error();                                                                                                                                              \
	}                                                                                                                                                                              \
	v = std::forward<decltype(BOOST_LEAF_TMP)>(BOOST_LEAF_TMP).value()

#define LU_LEAF_AUTO_THROW(v, r) LU_LEAF_ASSIGN_THROW(auto v, r)

#define LU_LEAF_CHECK(r)                                                                                                                                                           \
	auto&& BOOST_LEAF_TMP = r;                                                                                                                                                     \
	static_assert(::boost::leaf::is_result_type<std::decay<decltype(BOOST_LEAF_TMP)>::type>::value, "LU_LEAF_CHECK requires a result object (see is_result_type)");                \
	if (BOOST_LEAF_TMP)                                                                                                                                                            \
		;                                                                                                                                                                          \
	else                                                                                                                                                                           \
	{                                                                                                                                                                              \
		return BOOST_LEAF_TMP.error();                                                                                                                                             \
	}

#define LU_LEAF_NEW_ERROR		::boost::leaf::leaf_detail::inject_loc{__FILE__, __LINE__, __FUNCTION__} + ::boost::leaf::new_error
#define LU_LEAF_EXCEPTION		::boost::leaf::leaf_detail::inject_loc{__FILE__, __LINE__, __FUNCTION__} + ::boost::leaf::exception
#define LU_LEAF_THROW_EXCEPTION ::boost::leaf::leaf_detail::throw_with_loc{__FILE__, __LINE__, __FUNCTION__} + ::boost::leaf::exception
#define LU_LEAF_LOG_ERROR(...)	((void)0)
