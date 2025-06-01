#include "httplib.h"
#include "json.hpp"
#include "User.h"
#include "DbUtils.h"
#include "arrow/io/file.h"
#include <memory>

using json = nlohmann::json;

std::map<std::string, std::string> jsonToMap(const json& j) {
    std::map<std::string, std::string> result;
    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it.value().is_string())
            result[it.key()] = it.value();
        else
            result[it.key()] = it.value().dump(); // Convert non-strings (e.g. numbers) to string
    }
    return result;
}
int main() {
    httplib::Server svr;
    svr.Post("/login", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json data = json::parse(req.body);
            std::string purpose = data["purpose"];

            std::shared_ptr<arrow::io::ReadableFile> infile;

            if (purpose == "USERLOGIN") {
                json result; 
                std::string username = data["username"];
                std::string password = data["password"];
                User * logedUser = loginUser(infile, username, password);
                if (logedUser == nullptr) {
                    result["status"] = "false";
                    res.status = 401;
                } else {
                    result["status"] = true;
                    result["user"] = {
                        {"fullname", logedUser->fullName()},
                        {"username", logedUser->accountName()},
                        {"password", logedUser->password()},
                        {"salt", logedUser->salt()},
                        {"point", std::to_string(logedUser->point())},
                        {"wallet", logedUser->wallet()},
                    };
                }
                res.set_content(result.dump(), "application/json");
            } else if (purpose == "USEREDIT") {
                // std::cout << data << std::endl;
                // json parsed_data = json::parse(data);
                // json result;
                
                User * user = new User(data["userinfo"]["fullname"].get<std::string>(),
                                    data["userinfo"]["username"].get<std::string>(),
                                    data["userinfo"]["password"].get<std::string>(),
                                    data["userinfo"]["point"].get<int>(),
                                    data["userinfo"]["salt"].get<std::string>(),
                                    data["userinfo"]["wallet"].get<std::string>());
                std::string filename = "../assets/users.parquet";
                std::map<std::string, std::string> updatedvalues = jsonToMap(data["updatedvalues"]);
                updateUserInfo(filename, user, updatedvalues);
            }

            // std::string username = data["username"];
            // std::string password = data["password"];

            // json result;
            // if (username == "admin" && password == "123456") {
            //     // Trả về thông tin user
            //     result["status"] = "success";
            //     result["user"] = {
            //         {"username", "admin"},
            //         {"role", "admin"},
            //         {"email", "admin@example.com"}
            //     };
            //     res.set_content(result.dump(), "application/json");
            // } else {
            //     result["status"] = "fail";
            //     result["message"] = "Invalid credentials";
            //     res.status = 401;
            //     res.set_content(result.dump(), "application/json");
            // }
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"bad request\"}", "application/json");
        }
    });

    std::cout << "Server running at http://100.116.29.42:8080\n";
    svr.listen("100.116.29.42", 8080);
}
