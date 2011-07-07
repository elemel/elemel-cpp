#include <elemel/string_ptr.hpp>

#include <cassert>
#include <string>

void test_compare()
{
    assert(!(elemel::string_ptr("bar") == elemel::string_ptr("foo")));
    assert(elemel::string_ptr("bar") != elemel::string_ptr("foo"));
    assert(elemel::string_ptr("bar") < elemel::string_ptr("foo"));
    assert(elemel::string_ptr("bar") <= elemel::string_ptr("foo"));
    assert(!(elemel::string_ptr("bar") >= elemel::string_ptr("foo")));
    assert(!(elemel::string_ptr("bar") > elemel::string_ptr("foo")));

    assert(!(elemel::string_ptr("bar") == "foo"));
    assert(elemel::string_ptr("bar") != "foo");
    assert(elemel::string_ptr("bar") < "foo");
    assert(elemel::string_ptr("bar") <= "foo");
    assert(!(elemel::string_ptr("bar") >= "foo"));
    assert(!(elemel::string_ptr("bar") > "foo"));

    assert(!("bar" == elemel::string_ptr("foo")));
    assert("bar" != elemel::string_ptr("foo"));
    assert("bar" < elemel::string_ptr("foo"));
    assert("bar" <= elemel::string_ptr("foo"));
    assert(!("bar" >= elemel::string_ptr("foo")));
    assert(!("bar" > elemel::string_ptr("foo")));

    assert(elemel::string_ptr("foo") == elemel::string_ptr("foo"));
    assert(!(elemel::string_ptr("foo") != elemel::string_ptr("foo")));
    assert(!(elemel::string_ptr("foo") < elemel::string_ptr("foo")));
    assert(elemel::string_ptr("foo") <= elemel::string_ptr("foo"));
    assert(elemel::string_ptr("foo") >= elemel::string_ptr("foo"));
    assert(!(elemel::string_ptr("foo") > elemel::string_ptr("foo")));

    assert(elemel::string_ptr("foo") == "foo");
    assert(!(elemel::string_ptr("foo") != "foo"));
    assert(!(elemel::string_ptr("foo") < "foo"));
    assert(elemel::string_ptr("foo") <= "foo");
    assert(elemel::string_ptr("foo") >= "foo");
    assert(!(elemel::string_ptr("foo") > "foo"));

    assert("foo" == elemel::string_ptr("foo"));
    assert(!("foo" != elemel::string_ptr("foo")));
    assert(!("foo" < elemel::string_ptr("foo")));
    assert("foo" <= elemel::string_ptr("foo"));
    assert("foo" >= elemel::string_ptr("foo"));
    assert(!("foo" > elemel::string_ptr("foo")));

    assert(!(elemel::string_ptr("foo") == elemel::string_ptr("bar")));
    assert(elemel::string_ptr("foo") != elemel::string_ptr("bar"));
    assert(!(elemel::string_ptr("foo") < elemel::string_ptr("bar")));
    assert(!(elemel::string_ptr("foo") <= elemel::string_ptr("bar")));
    assert(elemel::string_ptr("foo") >= elemel::string_ptr("bar"));
    assert(elemel::string_ptr("foo") > elemel::string_ptr("bar"));

    assert(!(elemel::string_ptr("foo") == "bar"));
    assert(elemel::string_ptr("foo") != "bar");
    assert(!(elemel::string_ptr("foo") < "bar"));
    assert(!(elemel::string_ptr("foo") <= "bar"));
    assert(elemel::string_ptr("foo") >= "bar");
    assert(elemel::string_ptr("foo") > "bar");

    assert(!("foo" == elemel::string_ptr("bar")));
    assert("foo" != elemel::string_ptr("bar"));
    assert(!("foo" < elemel::string_ptr("bar")));
    assert(!("foo" <= elemel::string_ptr("bar")));
    assert("foo" >= elemel::string_ptr("bar"));
    assert("foo" > elemel::string_ptr("bar"));
}

int main(int argc, char *argv[])
{
    test_compare();
    return 0;
}
