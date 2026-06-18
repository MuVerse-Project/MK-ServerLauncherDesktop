#include "Hasher.hpp"


std::string CMS::Hex_CCRC32(const std::string& Text)
{
    CryptoPP::CRC32 crc;
    std::string digest;
    CryptoPP::StringSource(Text, true,
        new CryptoPP::HashFilter(crc,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest),false
                )));
    return digest;
}
std::vector<CryptoPP::byte> CMS::Bin_CCRC32(const std::string &Text)
{
    CryptoPP::CRC32 crc;
    std::vector<CryptoPP::byte> digest;
    CryptoPP::StringSource(Text, true,
        new CryptoPP::HashFilter(crc,
            new CryptoPP::VectorSink(digest)
        ));
    return digest;
}
std::string CMS::Hex_CSM3(const std::string &Text)
{
    CryptoPP::SM3 sm;
    std::string digest;
    CryptoPP::StringSource(Text, true,
        new CryptoPP::HashFilter(sm,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest),false
                )));
    return digest;
}
std::vector<CryptoPP::byte> CMS::Bin_CSM3(const std::string &Text)
{
    CryptoPP::SM3 sm;
    std::vector<CryptoPP::byte> digest;
    CryptoPP::StringSource(Text, true,
        new CryptoPP::HashFilter(sm,
            new CryptoPP::VectorSink(digest)
        ));
    return digest;
}

