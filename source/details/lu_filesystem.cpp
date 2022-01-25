#include <lu_config.h>
#include <lu_stdlib.h>
#include <lu_windows.h>

#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <mutex>

#include <boost/scope_exit.hpp>

#if LU_OS_IS_WINDOWS
#include <userenv.h>
#endif

namespace lu
{
	namespace filesystem
	{
		namespace details
		{
			leaf::result<std::string> convert_wide_str(const std::wstring_view& wstr) noexcept
			{
				try
				{
					if (wstr.size() > 0)
					{
						if constexpr (config::operating_system == config::windows_)
						{
							if (auto size_needed = ::WideCharToMultiByte(CP_UTF8, 0, &wstr[0], -1, NULL, 0, NULL, NULL); size_needed > 0)
							{
								std::vector<char> buffer(size_needed);
								if (::WideCharToMultiByte(CP_UTF8, 0, &wstr[0], -1, buffer.data(), size_needed, NULL, NULL) > 0)
								{
									return std::string(buffer.data());
								}
							}
						}
					}
					return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
				}
				catch (...)
				{
					return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
				}
			}

			class special_path_helper
			{
				std::string m_home_dir;

				// SPECIAL_CHARS
				// closing ')', '}' and ']'
				// '-' (a range in character set)
				// '&', '~', (extended character set operations)
				// '#' (comment) and WHITESPACE (ignored) in verbose mode
				std::string				   special_characters = "()[]{}?*+-|^$\\.&~# \t\n\r\v\f";
				std::map<int, std::string> special_characters_map;
				std::regex				   magic_check;

			public:
				special_path_helper()
				{
					magic_check = std::regex("([*?[])");

					if constexpr (config::operating_system == config::windows_)
					{
						HANDLE hToken;
						if (::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
						{
							BOOST_SCOPE_EXIT(&hToken)
							{
								::CloseHandle(hToken);
							}
							BOOST_SCOPE_EXIT_END

							DWORD size_needed = 0;
							if (::GetUserProfileDirectoryW(hToken, nullptr, &size_needed); size_needed > 0)
							{
								std::vector<wchar_t> buffer;
								buffer.resize(size_needed);

								if (::GetUserProfileDirectoryW(hToken, buffer.data(), &size_needed))
								{
									if (auto home = details::convert_wide_str(std::wstring_view(buffer.data(), size_needed - 1)))
									{
										m_home_dir = std::move(*home);
									}
									else
									{
										throw std::invalid_argument("error: details::convert_wide_str(str_from)");
									}
								}
								else
								{
									throw std::invalid_argument("error: ::GetUserProfileDirectoryW(hToken, &str_from[0], &size_needed)");
								}
							}
							else
							{
								throw std::invalid_argument("error: ::GetUserProfileDirectoryW(hToken, nullptr, &size_needed)");
							}
						}
						else
						{
							throw std::invalid_argument("error: ::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)");
						}
					}
					else
					{
						// TODO: implement real support
						const char* home = std::getenv("HOME");
						if (home == nullptr)
						{
							throw std::invalid_argument("error: Unable to expand `~` - HOME environment variable not set.");
						}
						m_home_dir = home;
					}

					for (auto& c : special_characters)
					{
						special_characters_map.insert(std::make_pair(static_cast<int>(c), std::string{"\\"} + std::string(1, c)));
					}
				}

				~special_path_helper() = default;

				const std::string& home_dir() const
				{
					return m_home_dir;
				}

				auto& get_special_characters()
				{
					return special_characters;
				}

				auto& get_special_characters_map()
				{
					return special_characters_map;
				}

				auto& get_magic_check()
				{
					return magic_check;
				}
			};
		} // namespace details

		leaf::result<std::string> path_to_string(const path& p) noexcept
		{
			return details::convert_wide_str(p.native());
		}

		namespace
		{
			using special_path_helper = lu::singleton_static<details::special_path_helper>;

			bool string_replace(std::string& str, const std::string& from, const std::string& to)
			{
				std::size_t start_pos = str.find(from);
				if (start_pos == std::string::npos)
				{
					return false;
				}

				str.replace(start_pos, from.length(), to);
				return true;
			}

			std::string translate(const std::string& pattern)
			{
				std::size_t i = 0, n = pattern.size();
				std::string result_string;

				while (i < n)
				{
					auto c = pattern[i];
					i += 1;
					if (c == '*')
					{
						result_string += ".*";
					}
					else if (c == '?')
					{
						result_string += ".";
					}
					else if (c == '[')
					{
						auto j = i;
						if (j < n && pattern[j] == '!')
						{
							j += 1;
						}
						if (j < n && pattern[j] == ']')
						{
							j += 1;
						}
						while (j < n && pattern[j] != ']')
						{
							j += 1;
						}
						if (j >= n)
						{
							result_string += "\\[";
						}
						else
						{
							auto stuff = std::string(pattern.begin() + i, pattern.begin() + j);
							if (stuff.find("--") == std::string::npos)
							{
								string_replace(stuff, std::string{"\\"}, std::string{R"(\\)"});
							}
							else
							{
								std::vector<std::string> chunks;
								std::size_t				 k = 0;
								if (pattern[i] == '!')
								{
									k = i + 2;
								}
								else
								{
									k = i + 1;
								}

								while (true)
								{
									k = pattern.find("-", k, j);
									if (k == std::string::npos)
									{
										break;
									}
									chunks.push_back(std::string(pattern.begin() + i, pattern.begin() + k));
									i = k + 1;
									k = k + 3;
								}

								chunks.push_back(std::string(pattern.begin() + i, pattern.begin() + j));
								// Escape backslashes and hyphens for set difference (--).
								// Hyphens that create ranges shouldn't be escaped.
								bool first = false;
								for (auto& s : chunks)
								{
									string_replace(s, std::string{"\\"}, std::string{R"(\\)"});
									string_replace(s, std::string{"-"}, std::string{R"(\-)"});
									if (first)
									{
										stuff += s;
										first = false;
									}
									else
									{
										stuff += "-" + s;
									}
								}
							}

							// Escape set operations (&&, ~~ and ||).
							std::string result;
							std::regex_replace(
								std::back_inserter(result),			 // ressult
								stuff.begin(), stuff.end(),			 // string
								std::regex(std::string{R"([&~|])"}), // pattern
								std::string{R"(\\\1)"});			 // repl
							stuff = result;
							i	  = j + 1;
							if (stuff[0] == '!')
							{
								stuff = "^" + std::string(stuff.begin() + 1, stuff.end());
							}
							else if (stuff[0] == '^' || stuff[0] == '[')
							{
								stuff = "\\\\" + stuff;
							}
							result_string = result_string + "[" + stuff + "]";
						}
					}
					else
					{
						if (special_path_helper()->get_special_characters().find(c) != std::string::npos)
						{
							result_string += special_path_helper()->get_special_characters_map()[static_cast<int>(c)];
						}
						else
						{
							result_string += c;
						}
					}
				}
				return std::string{"(("} + result_string + std::string{R"()|[\r\n])$)"};
			}

			std::regex compile_pattern(const std::string& pattern)
			{
				return std::regex(translate(pattern), std::regex::ECMAScript);
			}

			bool fnmatch_case(const path& name, const std::string& pattern)
			{
				return std::regex_match(name.string(), compile_pattern(pattern));
			}

			std::vector<path> filter(const std::vector<path>& names, const std::string& pattern)
			{
				// std::cout << "Pattern: " << pattern << "\n";
				std::vector<path> result;
				for (auto& name : names)
				{
					// std::cout << "Checking for " << name.string() << "\n";
					if (fnmatch_case(name, pattern))
					{
						result.push_back(name);
					}
				}
				return result;
			}

			path expand_tilde(path p)
			{
				if (p.empty())
					return p;

				std::string s = p.string();
				if (s[0] == '~')
				{
					return path(special_path_helper()->home_dir() + s.substr(1, s.size() - 1));
				}
				else
				{
					return p;
				}
			}

			bool has_magic(const std::string& pathname)
			{
				return std::regex_search(pathname, special_path_helper()->get_magic_check());
			}

			bool is_hidden(const std::string& pathname)
			{
				return pathname[0] == '.';
			}

			bool is_recursive(const std::string& pattern)
			{
				return pattern == "**";
			}

			std::vector<path> iter_directory(const path& dirname, bool dironly)
			{
				std::vector<path> result;

				auto current_directory = dirname;
				if (current_directory.empty())
				{
					current_directory = current_path();
				}

				if (exists(current_directory))
				{
					try
					{
						for (auto& entry : directory_iterator(current_directory, directory_options::follow_directory_symlink | directory_options::skip_permission_denied))
						{
							if (!dironly || entry.is_directory())
							{
								if (dirname.is_absolute())
								{
									result.push_back(entry.path());
								}
								else
								{
									result.push_back(relative(entry.path()));
								}
							}
						}
					}
					catch (std::exception&)
					{
						// not a directory
						// do nothing
					}
				}

				return result;
			}

			// Recursively yields relative pathnames inside a literal directory.
			std::vector<path> rlistdir(const path& dirname, bool dironly)
			{
				std::vector<path> result;
				auto			  names = iter_directory(dirname, dironly);
				for (auto& x : names)
				{
					if (!is_hidden(x.string()))
					{
						result.push_back(x);
						for (auto& y : rlistdir(x, dironly))
						{
							result.push_back(y);
						}
					}
				}
				return result;
			}

			// This helper function recursively yields relative pathnames inside a literal
			// directory.
			std::vector<path> glob2(const path& dirname, const path& pattern, bool dironly)
			{
				// std::cout << "In glob2\n";
				std::vector<path> result;
				assert(is_recursive(pattern.string()));
				for (auto& dir : rlistdir(dirname, dironly))
				{
					result.push_back(dir);
				}
				return result;
			}

			// These 2 helper functions non-recursively glob inside a literal directory.
			// They return a list of basenames.  _glob1 accepts a pattern while _glob0
			// takes a literal basename (so it only has to check for its existence).

			std::vector<path> glob1(const path& dirname, const path& pattern, bool dironly)
			{
				// std::cout << "In glob1\n";
				auto			  names = iter_directory(dirname, dironly);
				std::vector<path> filtered_names;
				for (auto& n : names)
				{
					if (!is_hidden(n.string()))
					{
						filtered_names.push_back(n.filename());
						// if (n.is_relative()) {
						//   // std::cout << "Filtered (Relative): " << n << "\n";
						//   filtered_names.push_back(relative(n));
						// } else {
						//   // std::cout << "Filtered (Absolute): " << n << "\n";
						//   filtered_names.push_back(n.filename());
						// }
					}
				}
				return filter(filtered_names, pattern.string());
			}

			std::vector<path> glob0(const path& dirname, const path& basename, bool /*dironly*/)
			{
				// std::cout << "In glob0\n";
				std::vector<path> result;
				if (basename.empty())
				{
					// 'q*x/' should match only directories.
					if (is_directory(dirname))
					{
						result = {basename};
					}
				}
				else
				{
					if (exists(dirname / basename))
					{
						result = {basename};
					}
				}
				return result;
			}

			std::vector<path> glob(const path& inpath, bool recursive = false, bool dironly = false)
			{
				std::vector<path> result;

				const auto pathname = inpath.string();
				auto	   p		= path(pathname);

				if (pathname[0] == '~')
				{
					// expand tilde
					p = expand_tilde(p);
				}

				auto	   dirname	= p.parent_path();
				const auto basename = p.filename();

				if (!has_magic(pathname))
				{
					assert(!dironly);
					if (!basename.empty())
					{
						if (exists(p))
						{
							result.push_back(p);
						}
					}
					else
					{
						// Patterns ending with a slash should match only directories
						if (is_directory(dirname))
						{
							result.push_back(p);
						}
					}
					return result;
				}

				if (dirname.empty())
				{
					if (recursive && is_recursive(basename.string()))
					{
						return glob2(dirname, basename, dironly);
					}
					else
					{
						return glob1(dirname, basename, dironly);
					}
				}

				std::vector<path> dirs;
				if (dirname != path(pathname) && has_magic(dirname.string()))
				{
					dirs = glob(dirname, recursive, true);
				}
				else
				{
					dirs = {dirname};
				}

				auto glob_in_dir = (has_magic(basename.string())) ? ((recursive && is_recursive(basename.string())) ? glob2 : glob1) : glob0;

				for (auto& d : dirs)
				{
					for (auto& name : glob_in_dir(d, basename, dironly))
					{
						path subresult = name;
						if (name.parent_path().empty())
						{
							subresult = d / name;
						}
						result.push_back(subresult);
					}
				}

				return result;
			}

		} // namespace

		leaf::result<std::vector<path>> glob(const std::string& pathname) noexcept
		{
			try
			{
				return glob(pathname, false);
			}
			catch (...)
			{
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
		}

		leaf::result<std::vector<path>> rglob(const std::string& pathname) noexcept
		{
			try
			{
				return glob(pathname, true);
			}
			catch (...)
			{
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
		}

		leaf::result<std::vector<path>> glob(const std::vector<std::string>& pathnames) noexcept
		{
			try
			{
				std::vector<path> result;
				for (auto& pathname : pathnames)
				{
					for (auto& match : glob(pathname, false))
					{
						result.push_back(std::move(match));
					}
				}
				return result;
			}
			catch (...)
			{
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
		}

		leaf::result<std::vector<path>> rglob(const std::vector<std::string>& pathnames) noexcept
		{
			try
			{
				std::vector<path> result;
				for (auto& pathname : pathnames)
				{
					for (auto& match : glob(pathname, true))
					{
						result.push_back(std::move(match));
					}
				}
				return result;
			}
			catch (...)
			{
				return LU_LEAF_NEW_ERROR(runtime_error::not_specified{});
			}
		}

		leaf::result<std::vector<path>> glob(const std::initializer_list<std::string>& pathnames) noexcept
		{
			return glob(std::vector<std::string>(pathnames));
		}

		leaf::result<std::vector<path>> rglob(const std::initializer_list<std::string>& pathnames) noexcept
		{
			return rglob(std::vector<std::string>(pathnames));
		}

	} // namespace filesystem
} // namespace lu