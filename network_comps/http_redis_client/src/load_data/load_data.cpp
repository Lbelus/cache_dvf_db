#include <main_header.hpp>

bool fileExists(const std::string& filename)
{
    if (std::filesystem::exists(filename))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// can make a lower level implementation.
std::vector<std::filesystem::path> listFilesInDirectory(const std::string& directoryPath)
{
    std::vector<std::filesystem::path> fileList;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (std::filesystem::is_regular_file(entry.status()))
        {
            fileList.push_back(entry.path());
        }
    }
    return fileList;
}

std::vector<std::filesystem::path> listDirectoriesInDirectory(const std::string& directoryPath)
{
    std::vector<std::filesystem::path> dirList;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (std::filesystem::is_directory(entry.status()))
        {
            dirList.push_back(entry.path());
        }
    }
    return dirList;
}


// hardcoded solution 
std::string create_key(std::filesystem::path year, std::filesystem::path filepath)
{
    std::string key;
    std::string file;
    std::string fileStr = filepath.filename().string();
    size_t pos = fileStr.find(".");
    fileStr.resize(pos);
    key = year.filename().string() + "-" + fileStr;
    return key;
}

int serializeAndLoad()
{
    sw::redis::Redis redis("tcp://myredis:6379");
    std::string key;
    try
    {
        size_t pos = 0;
        auto yearsDir = listDirectoriesInDirectory("../../bash_script/dvf_db/");
        for (const auto& year : yearsDir)
        {
            auto depdir = listDirectoriesInDirectory(year.string());
            for (const auto& dep : depdir)
            {
                auto files = listFilesInDirectory(dep.string());
                for (const auto& file : files)
                {
                    pos = file.string().find(".gz");
                    if (pos == std::string::npos)
                    {
                        std::vector<std::uint8_t> messagePack = fromCSVtoMsgPack(file.string());
                        std::string_view messagePackView(reinterpret_cast<const char*>(messagePack.data()), messagePack.size());
                        key = create_key(year, file);
                        redis.set(key, messagePackView);
                    }
                }
                std::cout << "processed dep:" << dep << " with starting file :" << files[0].filename().string() <<" on key:" << key << std::endl;
            }
        }
    }
    catch (const sw::redis::Error &err)
    {
        std::cerr << "Redis error: " << err.what() << std::endl;
        return 1;
    }
    return 0;
}


int fetch_data(std::string key)
{
    nlohmann::json j_from_msgpack;
    sw::redis::Redis redis("tcp://myredis:6379");
    auto val = redis.get(key);
    if (val)
    {
        std::vector<std::uint8_t> retrievedMessagePack(val->begin(), val->end());
        j_from_msgpack = nlohmann::json::from_msgpack(retrievedMessagePack);
    }
    std::string j_dump = j_from_msgpack.dump();
    std::cout << j_dump << std::endl;
    return EXIT_SUCCESS;
}
