#ifndef HASHER_H
#define HASHER_H
#include <cryptopp/crc.h>
#include <cryptopp/sha.h>
#include <cryptopp/sm3.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <string>
namespace CMS
{
    std::string Hex_CCRC32(const std::string &Text);
    std::vector<CryptoPP::byte> Bin_CCRC32(const std::string &Text);
    std::string Hex_CSM3(const std::string &Text);
    std::vector<CryptoPP::byte> Bin_CSM3(const std::string &Text);

}
#endif