#include <lu_config.h>
#include <lu_stdlib.h>

#include <lu_windows.h>

#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace lu
{
	namespace log
	{
		namespace details
		{
			struct logger_impl
			{
				//backward::TraceResolver			m_resolver_ref; // Keep one of these around so the symbols load properly.
				std::shared_ptr<spdlog::logger> m_stderr_logger;
				std::shared_ptr<spdlog::logger> m_stdout_logger;

				logger_impl()
				{
					auto stderr_logger = std::make_shared<spdlog::logger>("stderr", std::make_shared<spdlog::sinks::stderr_sink_mt>());
					auto stdout_logger = std::make_shared<spdlog::logger>("stdout", std::make_shared<spdlog::sinks::stdout_sink_mt>());

					m_stderr_logger = stderr_logger;
					m_stdout_logger = stdout_logger;
				}

				virtual ~logger_impl()
				{
					try
					{
						m_stderr_logger.reset();
						m_stdout_logger.reset();
					}
					catch (...)
					{
						// TODO: report error
						return;
					}
				}
			};
		}		
		
		spdlog::logger& to_stdout() noexcept 
		{ 
			return *singleton_static<details::logger_impl>()->m_stdout_logger;
		}

		spdlog::logger& to_stderr() noexcept 
		{ 
			return *singleton_static<details::logger_impl>()->m_stderr_logger;
		}
	} // namespace log
} // namespace lu