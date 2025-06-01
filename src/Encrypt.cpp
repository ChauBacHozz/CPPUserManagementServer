#include "Encrypt.h"
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <random>

std::string hashStringToHex(const std::string& input) {
    std::hash<std::string> hasher;
    size_t hash = hasher(input);

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}

std::string generateSaltStr(int length) {
    static const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);


    std::string salt;
    for (int i = 0; i < length; i++)
    {
        salt += charset[dist(rng)];
    }
    return salt;
}

std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *> (input.c_str()), input.length(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();    
}