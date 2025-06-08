## Giới thiệu về CPPUserManagementServer
CPPUserMaangementServer đóng vai trò là server của branch API trong repo CPPUserManagement, chịu trách nhiệm lưu trữ cơ sở dữ liệu và vào ra cơ sở dữ liệu

### Server đóng vai trò chức năng chính liên quan tới cơ sở dữ liệu, song song với Kafka Broker được cài đặt trên máy chủ và các producer/consumer được khai báo trên máy khách
- Sử dụng thư viện httplib để nhận các POST request từ máy khách, dữ liệu nhận được được chuyển qua định dạng json (nhờ thư viện nlohmann/json), sau đó dựa trên mục purpose để phân loại request, sau đó xử lý request và trả về kết quả


### Build và chạy chương trình (Sử dụng hệ điều hành Linux: Ubuntu/Ubuntu server/Linux Mint/...)
```
git clone https://github.com/ChauBacHozz/CPPUserManagementServer.git
bash run.sh
```

##  License

Dự án này được phát triển phục vụ mục đích học tập tại PTIT. Không sử dụng cho mục đích thương mại.
