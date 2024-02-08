#ifndef __MY_TESTS_H_
#define __MY_TESTS_H_

#include <main_header.hpp>

int simple_connection_test();
const char* googletest_simple_query(const std::string& key, const std::string& val);
const char* toConstChar(std::optional<std::string> optString);
int test_w_crow();
int test_json();
int googletest_json(std::string jsonStr);
std::vector<std::uint8_t> fromCSVtoMsgPack(const std::string& filename);
int testMsgPacktoHiredis();
#endif