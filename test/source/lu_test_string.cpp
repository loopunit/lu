#include <doctest/doctest.h>
#include <lu_stdlib.h>

TEST_CASE("lu_string")
{
	const lu::utf8::string str = "Hello World";

	assert(str.sso_active());

	lu::utf8::string str_fwd;
	lu::utf8::string str_rev;

	std::copy(str.begin(), str.end(), str_fwd.begin());	  // Copy using forward iterators
	std::copy(str.rbegin(), str.rend(), str_rev.begin()); // Copy using reverse iterators

	assert(std::equal(
		str.begin(), str.end(), str_fwd.begin(),
		[](const lu::utf8::string::value_type& a, const lu::utf8::string::value_type& b) -> bool
		{
			return ((static_cast<uint64_t>(a)) == (static_cast<uint64_t>(b)));
		}));

	lu::utf8::string::const_iterator it_src = str.end();
	lu::utf8::string::const_iterator it_rev = str_rev.begin();
	for (/* NOTHING HERE */; it_src != str.begin(); /* NOTHING HERE */)
	{
		--it_src;

		assert((static_cast<uint64_t>(*it_src)) == (static_cast<uint64_t>(*it_rev)));

		++it_rev;
	}

	lu::utf8::string::const_iterator it_fwd = str.begin();
	for (size_t chcount = 0; chcount < str.length(); ++chcount)
	{
		assert((static_cast<uint64_t>(str[chcount])) == (static_cast<uint64_t>(*it_fwd)));
		++it_fwd;
	}
}
