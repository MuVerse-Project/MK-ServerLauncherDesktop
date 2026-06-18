

#include "FileGuy.hpp"

CMS::FileManager::FileManager(const std::shared_ptr<spdlog::logger>& logger, const std::filesystem::path& ExeDir):logger_(logger)
{
    logger_->info("Initialized file system, executable directory: {}", ExeDir_.string());
    const std::filesystem::path logdir=ExeDir_/"Logs";
    const std::filesystem::path setdir=ExeDir/"Settings.json";

    if (!std::filesystem::exists(logdir)) {
        if (!std::filesystem::create_directories(logdir))
            {logger_->error("Failed to create log directory: {}", logdir.string());throw std::runtime_error("Cannot create log directory");}
    }
    if (!std::filesystem::exists(setdir)) {
        try
        {
            std::fstream File;File.open(setdir,std::ios::out);if (!File)throw std::runtime_error("Cannot create Settings.json");
            nlohmann::json j;
            // 彳亍
            j["MKSL"]={CMS::Hex_CSM3("ILoveMu")};File << j.dump(4);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            logger_->critical("Failed to create Settings.json: {}", e.what());
        }
    }

    LogDir_=logdir;
    SetDir_=setdir;
    logger_->info("Setted log dir and Settings.json \n{}\n{}",LogDir_.string(),SetDir_.string());
}

std::filesystem::path CMS::FileManager::GetLogFilePath() const
{
    return LogDir_/"App.log";
}

