#include <main_header.hpp>

int test_w_crow()
{
    sw::redis::Redis redis("tcp://myredis:6379");
    crow::SimpleApp app;
    CROW_ROUTE(app, "/data")
    ([&redis](const crow::request& req)
    {
        auto val = redis.get("key");
        if (val)
        {
            return crow::response(200, *val);
        }
        else
        {
            return crow::response(404, "Data not found");
        }
    });
    app.port(18080).multithreaded().run();
    // app.bindaddr("127.0.0.1")
    // .port(18080)
    // .multithreaded()
    // .run();
    return EXIT_SUCCESS;
}