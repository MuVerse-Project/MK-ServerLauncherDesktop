
#ifndef CMS_FILEGUY_H
#define CMS_FILEGUY_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/logger.h>
#include <yaml-cpp/yaml.h>
#include "Hasher.hpp"
namespace CMS{
class FileManager
{
public:
    explicit FileManager(const std::shared_ptr<spdlog::logger>& logger, const std::filesystem::path& ExeDir);
    std::filesystem::path GetLogFilePath() const;

private:
    std::shared_ptr<spdlog::logger> logger_;
    std::filesystem::path ExeDir_;
    std::filesystem::path LogDir_;
    std::filesystem::path SetDir_;
};
}
#endif //CMS_FILEGUY_H