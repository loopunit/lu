#pragma once

#include <lu_config.h>
#include "lu_util.h"

#include <functional>

namespace lu
{
	// Threadsafe in the sense that the C++11 standard guarantees that static variables are initialized in a threadsafe manner
	namespace details
	{
		enum class singleton_tag_default
		{
		};

		template<typename T, typename T_TAG>
		class singleton_instance
		{
			using tag_type = T_TAG;

		public:
			singleton_instance() noexcept = default;
			~singleton_instance()		  = default;

		protected:
			static inline T* s_instance = nullptr;
		};

		template<typename T, typename T_TAG, typename T_ALIGNMENT_VAR = uint64_t>
		class singleton_storage_static : singleton_instance<T, T_TAG>
		{
		protected:
			using value_type	 = T;
			using alignment_type = T_ALIGNMENT_VAR;
			using singleton_instance<T, T_TAG>::s_instance;

		public:
			singleton_storage_static() noexcept
			{
				static bool static_init = []() noexcept -> bool
				{
					try
					{
						s_instance = new (&s_instance_memory[0]) T();
						std::atexit(destroy); // atexit will be called in reverse order
					}
					catch (...)
					{
						// TODO: trap any exceptions here. this will not be recoverable.
						// also post the error to leaf so that it can be retrieved via leaf::error_monitor
						(void)::boost::leaf::new_error(runtime_error::not_specified{});
						std::abort();
						return false;
					}
					return true;
				}();
				BOOST_ATTRIBUTE_UNUSED(static_init);
			}

			~singleton_storage_static() = default;

			static void destroy() noexcept
			{
				try
				{
					if (s_instance)
					{
						s_instance->~T();
						s_instance = nullptr;
					}
				}
				catch (...)
				{
					// TODO: trap any exceptions here. this will not be recoverable.
					// also post the error to leaf so that it can be retrieved via leaf::error_monitor
					(void)::boost::leaf::new_error(runtime_error::not_specified{});
					std::abort();
				}
			}

		private:
			static inline alignment_type s_instance_memory[details::round_up(sizeof(T), sizeof(alignment_type))];
		};

		template<typename T, typename T_TAG>
		class singleton_storage_dynamic : singleton_instance<T, T_TAG>
		{
		protected:
			using value_type = T;
			using singleton_instance<T, T_TAG>::s_instance;

		public:
			singleton_storage_dynamic() noexcept
			{
				static bool static_init = []() -> bool
				{
					try
					{
						s_instance = new T();
						std::atexit(destroy); // atexit will be called in reverse order
					}
					catch (...)
					{
						// TODO: trap any exceptions here. this will not be recoverable.
						// also post the error to leaf so that it can be retrieved via leaf::error_monitor
						(void)::boost::leaf::new_error(runtime_error::not_specified{});
						std::abort();
						return false;
					}
					return true;
				}();
				BOOST_ATTRIBUTE_UNUSED(static_init);
			}

			~singleton_storage_dynamic() = default;

			static void destroy() noexcept
			{
				try
				{
					if (s_instance)
					{
						delete s_instance;
						s_instance = nullptr;
					}
				}
				catch (...)
				{
					// TODO: trap any exceptions here. this will not be recoverable.
					// also post the error to leaf so that it can be retrieved via leaf::error_monitor
					(void)::boost::leaf::new_error(runtime_error::not_specified{});
					std::abort();
				}
			}
		};

		template<typename T, typename T_TAG, typename T_FACTORY>
		class singleton_storage_factory : singleton_instance<T, T_TAG>
		{
		protected:
			using value_type = T;
			using factory	 = T_FACTORY;
			using singleton_instance<T, T_TAG>::s_instance;

		public:
			singleton_storage_factory() noexcept
			{
				static bool static_init = []() -> bool
				{
					try
					{
						s_instance = factory::create();
						std::atexit(destroy); // atexit will be called in reverse order
					}
					catch (...)
					{
						// TODO: trap any exceptions here. this will not be recoverable, so might as well std::abort.
						// also post the error to leaf so that it can be retrieved via leaf::error_monitor
						(void)::boost::leaf::new_error(runtime_error::not_specified{});
						std::abort();
						return false;
					}
					return true;
				}();
				BOOST_ATTRIBUTE_UNUSED(static_init);
			}

			~singleton_storage_factory() = default;

			static void destroy() noexcept
			{
				try
				{
					if (s_instance)
					{
						factory::destroy(s_instance);
						s_instance = nullptr;
					}
				}
				catch (...)
				{
					// TODO: trap any exceptions here. this will not be recoverable.
					// also post the error to leaf so that it can be retrieved via leaf::error_monitor
					(void)::boost::leaf::new_error(runtime_error::not_specified{});
					std::abort();
				}
			}
		};

		///

		template<typename T_FLAVOR>
		class singleton_iface : T_FLAVOR
		{
		protected:
			using T_FLAVOR::s_instance;

		public:
			using value_type = T_FLAVOR::value_type;

			static void destroy() noexcept
			{
				T_FLAVOR::destroy();
			}

			auto operator->() noexcept -> value_type*
			{
				return s_instance;
			}

			auto operator->() const noexcept -> const value_type*
			{
				return s_instance;
			}

			auto operator*() noexcept -> value_type&
			{
				return *s_instance;
			}

			auto operator*() const noexcept -> const value_type&
			{
				return *s_instance;
			}

			auto get() noexcept -> value_type*
			{
				return s_instance;
			}

			auto get() const noexcept -> const value_type*
			{
				return s_instance;
			}

			singleton_iface() noexcept = default;
			~singleton_iface()		   = default;
		};

		///

		template<typename T, typename T_TAG>
		using singleton_static_impl = singleton_iface<singleton_storage_static<T, T_TAG>>;

		template<typename T, typename T_TAG>
		using singleton_dynamic_impl = singleton_iface<singleton_storage_dynamic<T, T_TAG>>;

		template<typename T, typename T_TAG, typename T_FACTORY>
		using singleton_factory_impl = singleton_iface<singleton_storage_factory<T, T_TAG, T_FACTORY>>;

		template<typename T, typename T_TAG>
		struct singleton_virtual_factory
		{
			// should throw on error
			static T* create();

			// should throw on error
			static void destroy(T*);
		};

		template<typename T, typename T_TAG>
		using singleton_virtual_impl = singleton_iface<singleton_storage_factory<T, T_TAG, singleton_virtual_factory<T, T_TAG>>>;
	} // namespace details

	template<typename T>
	using singleton_static = details::singleton_static_impl<T, details::singleton_tag_default>;

	template<typename T>
	using singleton_dynamic = details::singleton_dynamic_impl<T, details::singleton_tag_default>;

	template<typename T, typename T_FACTORY>
	using singleton_factory = details::singleton_factory_impl<T, details::singleton_tag_default, T_FACTORY>;

	template<typename T>
	using singleton_virtual = details::singleton_virtual_impl<T, details::singleton_tag_default>;

	///

#define LU_IMPL_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL, T_SING)                                                                                                                 \
	T_IFACE* ::lu::details::singleton_virtual_factory<T_IFACE, ::lu::details::singleton_tag_default>::create()                                                                     \
	{                                                                                                                                                                              \
		/* simply forward to the implementation singleton - implementation should be unique */                                                                                     \
		return T_SING().get();                                                                                                                                                     \
	}                                                                                                                                                                              \
	void ::lu::details::singleton_virtual_factory<T_IFACE, ::lu::details::singleton_tag_default>::destroy(T_IFACE* val)                                                            \
	{                                                                                                                                                                              \
		/* simply forward to the implementation singleton - implementation should be unique */                                                                                     \
		return T_SING::destroy();                                                                                                                                                  \
	}                                                                                                                                                                              \
	/**/

#define LU_IMPL_STATIC_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL)                                                                                                                  \
	using singleton_static_impl_##T_IMPL = ::lu::singleton_static<T_IMPL>;                                                                                                         \
	LU_IMPL_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL, singleton_static_impl_##T_IMPL)                                                                                             \
	/**/

#define LU_IMPL_DYNAMIC_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL)                                                                                                                 \
	using singleton_dynamic_impl_##T_IMPL = ::lu::singleton_dynamic<T_IMPL>;                                                                                                       \
	LU_IMPL_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL, singleton_dynamic_impl_##T_IMPL)                                                                                            \
	/**/

#define LU_IMPL_FACTORY_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL, T_FACTORY)                                                                                                      \
	using singleton_factory_impl_##T_IMPL = ::lu::singleton_factoryl<T_IMPL, T_FACTORY>;                                                                                           \
	LU_IMPL_SINGLETON_VIRTUAL_FACTORY(T_IFACE, T_IMPL, singleton_factory_impl_##T_IMPL)                                                                                            \
	/**/
} // namespace lu