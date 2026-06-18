#ifndef HASHER_H
#define HASHER_H
#include <cryptopp/crc.h>
#include <cryptopp/sha.h>
#include <cryptopp/sm3.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <string>
std::string CCRC32(const std::string &Text);
std::vector<CryptoPP::byte> Bin_CCRC32(const std::string &Text);
#endif