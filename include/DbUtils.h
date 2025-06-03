#pragma once
#ifndef DBUTILS_H
#define DBUTILS_H
#include <arrow/api.h>
#include <arrow/io/api.h>
#include "arrow/io/file.h"
#include "User.h"
#include <string>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <map>
#include "json.hpp"
using json = nlohmann::json;

// arrow::Status getTableFromFile(const std::string& filename, std::shared_ptr<arrow::Table>& existing_table);
// arrow::Status AppendUserParquetRow(std::string& filename, 
//                                     std::string& FullName, 
//                                     std::string& UserName, 
//                                     std::string& UserPassword, 
//                                     std::string& Salt, 
//                                     int Point, 
//                                     std::string& WalletId);
// std::vector<std::vector<std::string>> ReadCSV(const std::string& filename);
// bool saveUserToDbFromCSV(std::string& filename);
User * loginUser(std::shared_ptr<arrow::io::ReadableFile> infile, std::string userName, std::string userpassword);
// arrow::Status printUserInfoFromDb();
arrow::Status updateUserInfo(const std::string& filename,
                             User*& user,
                            const std::map<std::string, 
                            std::string>& updated_values,
                            bool allow_point_update = false);
arrow::Status registerUser(User *& user);
std::string trim(const std::string& str);
json getUserInfoTable();
arrow::Status searchUser(std::string userName, User *& currentUser);
// arrow::Status transferPoint(const std::string& filename, User *& currentUser);
// void logTransaction(const std::string& senderWalletId,
//                     const std::string& senderuserName,
//                     const std::string& senderFullName, 
//                     const std::string& receiverWalletId,
//                     const std::string& receiveruserName,
//                     const std::string& receiverFullName, 
//                     int64_t transferPoint,
//                     bool isSuccess,
//                     const std::string& errorMessage = "");
json checkWalletIdAndFullName(const std::string& walletId, 
    const std::string& fullName,
    std::string& errorMessage);

#endif