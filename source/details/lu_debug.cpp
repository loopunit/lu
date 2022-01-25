#include <lu_config.h>
#include <lu_windows.h>

#include <lu_stdlib.h>

#include "backward.hpp"

namespace lu
{
	namespace debug
	{
		namespace details
		{
				class backward_printer
				{
				public:
					bool snippet;
					bool address;
					bool object;
					int	 inliner_context_size;
					int	 trace_context_size;

					backward_printer() : snippet(true), address(false), object(false), inliner_context_size(5), trace_context_size(7) { }

					template<typename ST>
					void print(ST& st, spdlog::logger& l, spdlog::level::level_enum lvl)
					{
						print_stacktrace(st, l, lvl);
					}

					template<typename IT>
					void print(IT begin, IT end, spdlog::logger& l, spdlog::level::level_enum lvl, size_t thread_id = 0)
					{
						print_stacktrace(begin, end, l, lvl, thread_id);
					}

					backward::TraceResolver const& resolver() const
					{
						return _resolver;
					}

				private:
					backward::TraceResolver	 _resolver;
					backward::SnippetFactory _snippets;

					template<typename ST>
					void print_stacktrace(ST& st, spdlog::logger& l, spdlog::level::level_enum lvl)
					{
						print_header(l, lvl, st.thread_id());
						_resolver.load_stacktrace(st);
						for (size_t trace_idx = st.size(); trace_idx > 0; --trace_idx)
						{
							print_trace(l, lvl, _resolver.resolve(st[trace_idx - 1]));
						}
					}

					template<typename IT>
					void print_stacktrace(IT begin, IT end, spdlog::logger& l, spdlog::level::level_enum lvl, size_t thread_id)
					{
						print_header(l, lvl, thread_id);
						for (; begin != end; ++begin)
						{
							print_trace(l, lvl, *begin);
						}
					}

					void print_header(spdlog::logger& l, spdlog::level::level_enum lvl, size_t thread_id)
					{
						l.log(lvl, "{0}{1}{2}", "Stack trace (most recent call last)", (thread_id) ? " in thread " : "", ":");
					}

					void print_trace(spdlog::logger& l, spdlog::level::level_enum lvl, const backward::ResolvedTrace& trace)
					{
						bool		already_indented = true;
						std::string substr_2		 = [&]()
						{
							if (!trace.source.filename.size() || object)
							{
								already_indented = false;
								return spdlog::fmt_lib::format("   Object \"{0}\", at {1}, in {2}", trace.object_filename, trace.addr, trace.object_function);
							}
							else
							{
								return spdlog::fmt_lib::format("");
							}
						}();

						l.log(lvl, "#{0}{1}", trace.idx, substr_2);

						for (size_t inliner_idx = trace.inliners.size(); inliner_idx > 0; --inliner_idx)
						{
							const backward::ResolvedTrace::SourceLoc& inliner_loc = trace.inliners[inliner_idx - 1];
							if (!already_indented)
							{
								print_source_loc(l, lvl, "    | ", inliner_loc);
							}
							else
							{
								print_source_loc(l, lvl, " | ", inliner_loc);
							}

							if (snippet)
							{
								print_snippet(l, lvl, "    | ", inliner_loc, inliner_context_size);
							}
							already_indented = false;
						}

						if (trace.source.filename.size())
						{
							if (!already_indented)
							{
								print_source_loc(l, lvl, "      ", trace.source, trace.addr);
							}
							else
							{
								print_source_loc(l, lvl, "   ", trace.source, trace.addr);
							}

							if (snippet)
							{
								print_snippet(l, lvl, "      ", trace.source, trace_context_size);
							}
						}
					}

					void print_snippet(spdlog::logger& l, spdlog::level::level_enum lvl, const char* indent, const backward::ResolvedTrace::SourceLoc& source_loc, int context_size)
					{
						using namespace std;
						typedef backward::SnippetFactory::lines_t lines_t;

						lines_t lines = _snippets.get_snippet(source_loc.filename, source_loc.line, static_cast<unsigned>(context_size));

						for (lines_t::const_iterator it = lines.begin(); it != lines.end(); ++it)
						{
							l.log(lvl, "{0}{1}{2}: {3}", indent, (it->first == source_loc.line) ? ">" : " ", it->first, it->second);
						}
					}

					void print_source_loc(
						spdlog::logger&							  l,
						spdlog::level::level_enum				  lvl,
						const char*								  indent,
						const backward::ResolvedTrace::SourceLoc& source_loc,
						void*									  addr = nullptr)
					{
						l.log(
							lvl, "{0} Source \"{1}\", line {2}, in {3}{4}", indent, source_loc.filename, source_loc.function, source_loc.line,
							(address && addr != nullptr) ? spdlog::fmt_lib::format(" [{0}]", addr) : "");
					}
				};

				// TODO: terminate handler. these should all be some sort of common root types that we can squeeze reasonable info out of
			static inline auto error_handlers = std::make_tuple(
				[](runtime_error::not_specified x, leaf::e_source_location sl)
				{
					log::to_stderr().log(spdlog::level::err, "{0} :: {1} -> {2} : runtime_error :: not_specified", sl.line, sl.file, sl.function);
				},
				[](common_error x, leaf::e_source_location sl)
				{
					log::to_stderr().log(spdlog::level::err, "{0} :: {1} -> {2} : common_error", sl.line, sl.file, sl.function);
				},
				[]
				{
					log::to_stderr().log(spdlog::level::err, "???");
				});

			struct debug_impl
			{
				static inline std::atomic<bool> s_destroyed;
				static inline backward_printer m_stacktrace_printer;

				debug_impl()
				{
					// TODO: terminate handler.
					std::set_terminate(
						[]() noexcept
						{
							if (!s_destroyed.load())
							{
								log::to_stderr().log(spdlog::level::critical, "Terminate handler activated");

								capture_and_log_stack_trace(log::to_stderr(), spdlog::level::critical);

								// Rethrow and try to get some info out of it
								if (auto x = std::current_exception())
								{
									// TODO: concatenate with additional types
									auto terminate_error_handlers = error_handlers;

									leaf::try_handle_all(
										[&]() -> leaf::result<void>
										{
											std::rethrow_exception(x);
										},
										terminate_error_handlers);
								}

								std::_Exit(EXIT_FAILURE);
							}
						});
				}

				~debug_impl()
				{
					try
					{
						s_destroyed.store(true);
					}
					catch (...)
					{
						// TODO: report error
						return;
					}
				}

				void begin_new_process() noexcept 
				{ 
					// TODO: open a new log file, etc
				}
				
				static inline void capture_and_log_stack_trace(spdlog::logger& l, spdlog::level::level_enum lvl) noexcept
				{
					backward::StackTrace st;
					st.load_here(32);
					m_stacktrace_printer.print(st, l, lvl);
				}
			};
		} // namespace details

		void begin_new_process() noexcept
		{
			singleton_static<details::debug_impl>()->begin_new_process();
		}

		void capture_and_log_stack_trace(spdlog::logger& l, spdlog::level::level_enum lvl) noexcept
		{
			singleton_static<details::debug_impl>()->capture_and_log_stack_trace(l, lvl);
		}
	} // namespace debug
} // namespace lu
