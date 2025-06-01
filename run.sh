#!/bin/bash
rm -r build
mkdir -p build    # -p để tránh lỗi nếu thư mục đã tồn tại
cd build || exit 1 # nếu cd thất bại thì thoát script
cmake ..
make
./main