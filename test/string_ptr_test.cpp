#include <elemel/string_ptr.hpp>

#include <cassert>
#include <string>

int main(int argc, char *argv[])
{
    assert(elemel::string_ptr("foo") == elemel::string_ptr("foo"));
    return 0;
}
