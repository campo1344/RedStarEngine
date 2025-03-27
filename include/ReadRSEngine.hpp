#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <json.hpp>

inline void ReadDataOfFileString(const char *FilePath, std::string *Data)
{
    std::ifstream FileData;
    FileData.exceptions(std::fstream::badbit | std::fstream::failbit);

    try
    {
        std::stringstream DataRead;
        FileData.open(FilePath);
        DataRead << FileData.rdbuf();
        FileData.close();
        *Data = DataRead.str();
    }
    catch (const std::ifstream::failure &e)
    {
        std::cerr << e.what() << '\n';
    }
}

inline void ReadDataOfFileJson(const char *FilePath, nlohmann::json *Data)
{
    std::ifstream DataFile;
    DataFile.exceptions(std::fstream::badbit | std::fstream::failbit);

    try
    {
        std::stringstream DataRead;
        DataFile.open(FilePath);
        DataRead << DataFile.rdbuf();
        DataFile.close();
        *Data = nlohmann::json::parse(DataRead.str());
    }
    catch (const std::ifstream::failure &e)
    {
        std::cerr << e.what() << '\n';
    }
}