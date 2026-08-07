

#include "FileGuy.hpp"

#include "Hasher.hpp"

CMS::FileManager::FileManager(const std::shared_ptr<spdlog::logger>& logger, const std::filesystem::path& ExeDir):logger_(logger)
{

    logger_->info("Initialized file system, executable directory: {}", ExeDir.string());
    const std::filesystem::path logdir=ExeDir/"Logs";
    const std::filesystem::path setdir=ExeDir/"Settings.json";

    if (!std::filesystem::exists(logdir)) {
        if (!std::filesystem::create_directories(logdir))
            {logger_->error("Failed to create log directory: {}", logdir.string());throw std::runtime_error("Cannot create log directory");}
    }
    if (!std::filesystem::exists(setdir)) {
        try
        {
            std::fstream File;File.open(setdir,std::ios::out);if (!File)throw std::runtime_error("Cannot create Settings.json");

            // 彳亍
            j_["MKSL"]={CMS::Hex_CSM3("ILoveMu")};File << j_.dump(4);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            logger_->critical("Failed to create Settings.json: {}", e.what());
        }
    }

    LogDir_=logdir;
    SetDir_=setdir;
    ExeDir_=ExeDir;
    std::fstream File;File.open(setdir,std::ios::in);if (!File)throw std::runtime_error("Cannot open Settings.json");

    File >> j_;
    logger_->info("Setted log dir and Settings.json \n{}\n{}",LogDir_.string(),SetDir_.string());
    logger_->info(j_.dump(4));
    MuDir_=ExeDir_/"MuView-all.jar";

    JavaDir_=boost::process::environment::find_executable("java.exe").string();






}

std::string CMS::FileManager::InitJava()
{
    std::string tmp;

        if (!j_.contains("JavaDir"))
        {
            std::cout <<"\nCouldn't find the java pls input a dir to save it\n";

            while (true)
            {
                std::cout << "> ";std::cout.flush();std::getline(std::cin, tmp);
                if (tmp.empty() || !std::filesystem::exists(tmp)) {logger_->warn("{}", tmp);continue;}logger_->info("{}", tmp);
                break;
            }

            j_["JavaDir"] = tmp;
            std::fstream File;File.open(SetDir_,std::ios::out);File << j_.dump(4);File.close();
        }
        else{return j_["JavaDir"];}

    return tmp;
}

std::filesystem::path CMS::FileManager::GetLogFilePath() const
{
    return LogDir_/"App.log";
}

bool CMS::FileManager::CheckMu() const
{
    return std::filesystem::exists(MuDir_);
}

