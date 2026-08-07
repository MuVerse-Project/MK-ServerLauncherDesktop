
#ifndef CMS_FILEGUY_H
#define CMS_FILEGUY_H

#include "HolyHead.hpp"

namespace CMS{
class FileManager
{
public:
    explicit FileManager(const std::shared_ptr<spdlog::logger>& logger, const std::filesystem::path& ExeDir);
    std::filesystem::path GetLogFilePath() const;
    bool CheckMu() const;
    std::string InitJava() ;

private:
    std::shared_ptr<spdlog::logger> logger_;
    std::filesystem::path ExeDir_;
    std::filesystem::path LogDir_;
    std::filesystem::path SetDir_;
    std::filesystem::path MuDir_;
    std::filesystem::path JavaDir_;
    nlohmann::json j_;
};
}
#endif //CMS_FILEGUY_H