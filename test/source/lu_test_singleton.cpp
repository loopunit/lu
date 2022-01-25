#include <doctest/doctest.h>
#include <lu_stdlib.h>

namespace details
{
	struct basic_static_singleton_interface
	{
		basic_static_singleton_interface()			= default;
		virtual ~basic_static_singleton_interface() = default;

		virtual void ping() = 0;
	};

	struct basic_dynamic_singleton_interface
	{
		basic_dynamic_singleton_interface()			 = default;
		virtual ~basic_dynamic_singleton_interface() = default;

		virtual void ping() = 0;
	};

	struct basic_static_singleton
	{
		basic_static_singleton()
		{
			printf("basic_static_singleton()\n");
		}

		virtual ~basic_static_singleton()
		{
			printf("~basic_static_singleton()\n");
		}

		virtual void ping()
		{
			printf("ping!\n");
		}
	};

	struct basic_dynamic_singleton
	{
		basic_dynamic_singleton()
		{
			printf("basic_dynamic_singleton()\n");
		}

		virtual ~basic_dynamic_singleton()
		{
			printf("~basic_dynamic_singleton()\n");
		}

		virtual void ping()
		{
			printf("ping!\n");
		}
	};

	struct basic_virtual_static_singleton : public basic_static_singleton_interface
	{
		basic_virtual_static_singleton()
		{
			printf("basic_virtual_static_singleton()\n");
		}

		virtual ~basic_virtual_static_singleton()
		{
			printf("~basic_virtual_static_singleton()\n");
		}

		virtual void ping()
		{
			printf("ping!\n");
		}
	};

	struct basic_virtual_dynamic_singleton : public basic_dynamic_singleton_interface
	{
		basic_virtual_dynamic_singleton()
		{
			printf("basic_virtual_dynamic_singleton()\n");
		}

		virtual ~basic_virtual_dynamic_singleton()
		{
			printf("~basic_virtual_dynamic_singleton()\n");
		}

		virtual void ping()
		{
			printf("ping!\n");
		}
	};
} // namespace details

using basic_static_singleton  = lu::singleton_static<details::basic_static_singleton>;
using basic_dynamic_singleton = lu::singleton_dynamic<details::basic_dynamic_singleton>;

using virtual_static_singleton				   = lu::singleton_virtual<details::basic_static_singleton_interface>;
using details_basic_virtual_static_singleton   = details::basic_virtual_static_singleton;
using details_basic_static_singleton_interface = details::basic_static_singleton_interface;
LU_IMPL_STATIC_SINGLETON_VIRTUAL_FACTORY(details_basic_static_singleton_interface, details_basic_virtual_static_singleton);

using virtual_dynamic_singleton					= lu::singleton_virtual<details::basic_dynamic_singleton_interface>;
using details_basic_virtual_dynamic_singleton	= details::basic_virtual_dynamic_singleton;
using details_basic_dynamic_singleton_interface = details::basic_dynamic_singleton_interface;
LU_IMPL_DYNAMIC_SINGLETON_VIRTUAL_FACTORY(details_basic_dynamic_singleton_interface, details_basic_virtual_dynamic_singleton);

TEST_CASE("lu_singleton")
{
	basic_static_singleton()->ping();
	basic_dynamic_singleton()->ping();
	virtual_static_singleton()->ping();
	virtual_dynamic_singleton()->ping();

	// force destroy for purposes of the test.
	printf("Force destroying all referenced singletons, they can't be referenced again.\n");
	basic_static_singleton::destroy();
	basic_dynamic_singleton::destroy();
	virtual_static_singleton::destroy();
	virtual_dynamic_singleton::destroy();
	printf("Force destroying done\n");
}
