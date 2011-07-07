#include <elemel/string_range.hpp>

#include <cassert>
#include <string>

void test_compare()
{
    assert(!(elemel::string_range("bar") == elemel::string_range("foo")));
    assert(elemel::string_range("bar") != elemel::string_range("foo"));
    assert(elemel::string_range("bar") < elemel::string_range("foo"));
    assert(elemel::string_range("bar") <= elemel::string_range("foo"));
    assert(!(elemel::string_range("bar") >= elemel::string_range("foo")));
    assert(!(elemel::string_range("bar") > elemel::string_range("foo")));

    assert(!(elemel::string_range("bar") == "foo"));
    assert(elemel::string_range("bar") != "foo");
    assert(elemel::string_range("bar") < "foo");
    assert(elemel::string_range("bar") <= "foo");
    assert(!(elemel::string_range("bar") >= "foo"));
    assert(!(elemel::string_range("bar") > "foo"));

    assert(!("bar" == elemel::string_range("foo")));
    assert("bar" != elemel::string_range("foo"));
    assert("bar" < elemel::string_range("foo"));
    assert("bar" <= elemel::string_range("foo"));
    assert(!("bar" >= elemel::string_range("foo")));
    assert(!("bar" > elemel::string_range("foo")));

    assert(elemel::string_range("foo") == elemel::string_range("foo"));
    assert(!(elemel::string_range("foo") != elemel::string_range("foo")));
    assert(!(elemel::string_range("foo") < elemel::string_range("foo")));
    assert(elemel::string_range("foo") <= elemel::string_range("foo"));
    assert(elemel::string_range("foo") >= elemel::string_range("foo"));
    assert(!(elemel::string_range("foo") > elemel::string_range("foo")));

    assert(elemel::string_range("foo") == "foo");
    assert(!(elemel::string_range("foo") != "foo"));
    assert(!(elemel::string_range("foo") < "foo"));
    assert(elemel::string_range("foo") <= "foo");
    assert(elemel::string_range("foo") >= "foo");
    assert(!(elemel::string_range("foo") > "foo"));

    assert("foo" == elemel::string_range("foo"));
    assert(!("foo" != elemel::string_range("foo")));
    assert(!("foo" < elemel::string_range("foo")));
    assert("foo" <= elemel::string_range("foo"));
    assert("foo" >= elemel::string_range("foo"));
    assert(!("foo" > elemel::string_range("foo")));

    assert(!(elemel::string_range("foo") == elemel::string_range("bar")));
    assert(elemel::string_range("foo") != elemel::string_range("bar"));
    assert(!(elemel::string_range("foo") < elemel::string_range("bar")));
    assert(!(elemel::string_range("foo") <= elemel::string_range("bar")));
    assert(elemel::string_range("foo") >= elemel::string_range("bar"));
    assert(elemel::string_range("foo") > elemel::string_range("bar"));

    assert(!(elemel::string_range("foo") == "bar"));
    assert(elemel::string_range("foo") != "bar");
    assert(!(elemel::string_range("foo") < "bar"));
    assert(!(elemel::string_range("foo") <= "bar"));
    assert(elemel::string_range("foo") >= "bar");
    assert(elemel::string_range("foo") > "bar");

    assert(!("foo" == elemel::string_range("bar")));
    assert("foo" != elemel::string_range("bar"));
    assert(!("foo" < elemel::string_range("bar")));
    assert(!("foo" <= elemel::string_range("bar")));
    assert("foo" >= elemel::string_range("bar"));
    assert("foo" > elemel::string_range("bar"));
}

int main(int argc, char *argv[])
{
    test_compare();
    return 0;
}
