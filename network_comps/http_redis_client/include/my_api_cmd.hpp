#ifndef __MY_CMD_API_H_
#define __MY_CMD_API_H_

#include <main_header.hpp>


// load file onto redis server;
bool fileExists(const std::string& filename);
std::vector<std::filesystem::path> listFilesInDirectory(const std::string& directoryPath);
std::vector<std::filesystem::path> listDirectoriesInDirectory(const std::string& directoryPath);
int serializeAndLoad();
int fetch_data(std::string key);


#endif