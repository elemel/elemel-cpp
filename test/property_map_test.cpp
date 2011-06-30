#include <elemel/property_map.hpp>

#include <string>

int main(int argc, char *argv[])
{
    elemel::property_map<std::string, std::string> prototype;
    elemel::property_map<std::string, std::string> instance(&prototype);
    prototype.set("left", "red");
    prototype.set("right", "blue");
    prototype.set("center", "green");
    instance.set("right", "black");
    instance.set("top", "yellow");
    instance.set("bottom", "white");
    assert(instance.get("bottom") == "white");
    assert(instance.get("left") == "red");
    assert(instance.get("right") == "black");
    return 0;
}
