#pragma once

#include <lu_config.h>

#include "lu_error.h"
#include "lu_string.h"

#include <vector>
#include <string>

#include <ghc/filesystem.hpp>

namespace lu
{
	// NOTE: std::string is treated as utf8
	namespace filesystem
	{
		using namespace ghc::filesystem;
		
		leaf::result<std::string> path_to_string(const path& p) noexcept;

		/// \param pathname string containing a path specification
		/// \return vector of paths that match the pathname
		///
		/// Pathnames can be absolute (/usr/src/Foo/Makefile) or relative (../../Tools/*/*.gif)
		/// Pathnames can contain shell-style wildcards
		/// Broken symlinks are included in the results (as in the shell)
		leaf::result<std::vector<path>> glob(const std::string& pathname) noexcept;

		/// \param pathnames string containing a path specification
		/// \return vector of paths that match the pathname
		///
		/// Globs recursively.
		/// The pattern “**” will match any files and zero or more directories, subdirectories and
		/// symbolic links to directories.
		leaf::result<std::vector<path>> rglob(const std::string& pathname) noexcept;

		/// Runs `glob` against each pathname in `pathnames` and accumulates the results
		leaf::result<std::vector<path>> glob(const std::vector<std::string>& pathnames) noexcept;

		/// Runs `rglob` against each pathname in `pathnames` and accumulates the results
		leaf::result<std::vector<path>> rglob(const std::vector<std::string>& pathnames) noexcept;

		/// Initializer list overload for convenience
		leaf::result<std::vector<path>> glob(const std::initializer_list<std::string>& pathnames) noexcept;

		/// Initializer list overload for convenience
		leaf::result<std::vector<path>> rglob(const std::initializer_list<std::string>& pathnames) noexcept;
	} // namespace filesystem
} // namespace lu
