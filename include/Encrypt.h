#pragma once
#ifndef ENCRYPT_H
#define ENCRYPT_H
#include <string>

std::string hashStringToHex(const std::string& input);
std::string generateSaltStr(int length = 16);
std::string sha256(const std::string& input);




#endif