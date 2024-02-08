#include <main_header.hpp>


const char* toConstChar(std::optional<std::string> optString)
{
    const char* cStr = nullptr;
    if (optString)
    {
        cStr = optString->c_str();
    }
    return cStr;
}

int simple_connection_test()
{
    try
    {
        sw::redis::Redis redis("tcp://myredis:6379");
        redis.set("key00", "value00");
        auto val = redis.get("key00");
        if (val)
        {
            std::cout << *val << std::endl;
        }
    }
    catch (const sw::redis::Error &err)
    {
        std::cerr << "Redis error: " << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

const char* googletest_simple_query(const std::string& key, const std::string& val)
{
    std::optional<std::__cxx11::basic_string<char> > result;
    try
    {
        sw::redis::Redis redis("tcp://myredis:6379");
        redis.set(key, val);
        result = redis.get(key);
        if (result == val)
        {
            return toConstChar(result);
        }
    }
    catch (const sw::redis::Error &err)
    {
        std::cerr << "Redis error: " << err.what() << std::endl;
        result = "Value not available";
        return toConstChar(result);
    }
    return toConstChar(result);
}