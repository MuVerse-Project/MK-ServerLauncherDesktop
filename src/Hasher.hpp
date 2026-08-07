#ifndef HASHER_H
#define HASHER_H
#include "HolyHead.hpp"
namespace CMS
{
    std::string Hex_CCRC32(const std::string &Text);
    std::vector<CryptoPP::byte> Bin_CCRC32(const std::string &Text);
    std::string Hex_CSM3(const std::string &Text);
    std::vector<CryptoPP::byte> Bin_CSM3(const std::string &Text);

}
#endif