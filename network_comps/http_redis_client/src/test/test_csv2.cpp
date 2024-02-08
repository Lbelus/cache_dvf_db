#include <main_header.hpp>

int testMsgPacktoHiredis()
{
    sw::redis::Redis redis("tcp://myredis:6379");
    nlohmann::json j_from_msgpack;
    try
    {
        std::vector<std::uint8_t> messagePack = fromCSVtoMsgPack("localfile.csv");
        std::string_view messagePackView(reinterpret_cast<const char*>(messagePack.data()), messagePack.size());
        redis.set("mykey", messagePackView);
    }
    catch (const sw::redis::Error &err)
    {
        std::cerr << "Redis error: " << err.what() << std::endl;
        return 1;
    }
    auto val = redis.get("mykey");
    if (val)
    {
        std::vector<std::uint8_t> retrievedMessagePack(val->begin(), val->end());
        j_from_msgpack = nlohmann::json::from_msgpack(retrievedMessagePack);
    }
    std::string j_dump = j_from_msgpack.dump();
    std::cout << j_dump << std::endl;
    // std::cout << j_from_msgpack << std::endl;

    return 0;
}