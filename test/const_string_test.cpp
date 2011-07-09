#include <elemel/const_string.hpp>

#include <cassert>
#include <string>

void test_compare()
{
    assert(!(elemel::const_string("bar") == elemel::const_string("foo")));
    assert(elemel::const_string("bar") != elemel::const_string("foo"));
    assert(elemel::const_string("bar") < elemel::const_string("foo"));
    assert(elemel::const_string("bar") <= elemel::const_string("foo"));
    assert(!(elemel::const_string("bar") >= elemel::const_string("foo")));
    assert(!(elemel::const_string("bar") > elemel::const_string("foo")));

    assert(!(elemel::const_string("bar") == "foo"));
    assert(elemel::const_string("bar") != "foo");
    assert(elemel::const_string("bar") < "foo");
    assert(elemel::const_string("bar") <= "foo");
    assert(!(elemel::const_string("bar") >= "foo"));
    assert(!(elemel::const_string("bar") > "foo"));

    assert(!("bar" == elemel::const_string("foo")));
    assert("bar" != elemel::const_string("foo"));
    assert("bar" < elemel::const_string("foo"));
    assert("bar" <= elemel::const_string("foo"));
    assert(!("bar" >= elemel::const_string("foo")));
    assert(!("bar" > elemel::const_string("foo")));

    assert(elemel::const_string("foo") == elemel::const_string("foo"));
    assert(!(elemel::const_string("foo") != elemel::const_string("foo")));
    assert(!(elemel::const_string("foo") < elemel::const_string("foo")));
    assert(elemel::const_string("foo") <= elemel::const_string("foo"));
    assert(elemel::const_string("foo") >= elemel::const_string("foo"));
    assert(!(elemel::const_string("foo") > elemel::const_string("foo")));

    assert(elemel::const_string("foo") == "foo");
    assert(!(elemel::const_string("foo") != "foo"));
    assert(!(elemel::const_string("foo") < "foo"));
    assert(elemel::const_string("foo") <= "foo");
    assert(elemel::const_string("foo") >= "foo");
    assert(!(elemel::const_string("foo") > "foo"));

    assert("foo" == elemel::const_string("foo"));
    assert(!("foo" != elemel::const_string("foo")));
    assert(!("foo" < elemel::const_string("foo")));
    assert("foo" <= elemel::const_string("foo"));
    assert("foo" >= elemel::const_string("foo"));
    assert(!("foo" > elemel::const_string("foo")));

    assert(!(elemel::const_string("foo") == elemel::const_string("bar")));
    assert(elemel::const_string("foo") != elemel::const_string("bar"));
    assert(!(elemel::const_string("foo") < elemel::const_string("bar")));
    assert(!(elemel::const_string("foo") <= elemel::const_string("bar")));
    assert(elemel::const_string("foo") >= elemel::const_string("bar"));
    assert(elemel::const_string("foo") > elemel::const_string("bar"));

    assert(!(elemel::const_string("foo") == "bar"));
    assert(elemel::const_string("foo") != "bar");
    assert(!(elemel::const_string("foo") < "bar"));
    assert(!(elemel::const_string("foo") <= "bar"));
    assert(elemel::const_string("foo") >= "bar");
    assert(elemel::const_string("foo") > "bar");

    assert(!("foo" == elemel::const_string("bar")));
    assert("foo" != elemel::const_string("bar"));
    assert(!("foo" < elemel::const_string("bar")));
    assert(!("foo" <= elemel::const_string("bar")));
    assert("foo" >= elemel::const_string("bar"));
    assert("foo" > elemel::const_string("bar"));
}

int main(int argc, char *argv[])
{
    test_compare();
    return 0;
}
