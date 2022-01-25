#pragma once

#include <lu_config.h>

#include "lu_error.h"

#include <mutex>
#include <atomic>

namespace lu
{
	namespace details
	{
		constexpr size_t round_up(size_t val, size_t multiple) noexcept
		{
			return (multiple == 0) ? val : (((val % multiple) == 0) ? val : (val + multiple - (val % multiple)));
		}
	} // namespace details

	// NOTE: only works on T_VAL that has a single init.
	template<typename T_VAL>
	struct double_checked_lock_wrapper
	{
		std::mutex			m_mutex;
		std::atomic<T_VAL*> m_value_ptr;
		T_VAL				m_value;

		double_checked_lock_wrapper() = default;

		template<typename... T_ARGS>
		double_checked_lock_wrapper(T_ARGS... args) : m_value(args...)
		{ }

		T_VAL& get()
		{
			return m_value;
		}

		template<typename T_INIT>
		T_VAL& get(T_INIT init_func)
		{
			// Using sequentially consistent atomics, no memory order necessary
			if (T_VAL* local = m_value_ptr.load(); !local) [[unlikely]]
			{
				std::lock_guard<std::mutex> guard(m_mutex);

				// check the flag again so only the first thread does the init, while all others block w/the mutex.
				if (local = m_value_ptr.load(); !local) [[unlikely]]
				{
					// init_func should throw on error, each thread locked w/guard will retry.
					local = &m_value;
					init_func(*local);

					// if init_func fails, return m_value in an undefined state
					m_value_ptr.store(local);
				}

				return *local;
			}
			else [[likely]]
			{
				// else the var is set, so we can just return it.
				return m_value;
			}
		}
	};
} // namespace lu
