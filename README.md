# Project 1 - Môn Kiến trúc máy tính & Hợp ngữ  

* Đồ án lập trình số lớn 128bit và số chấm động độ chính xác bố của cao  

## Chức năng  

1. Chuyển đổi giữa các hệ cơ số 16, thập phân, nhị phân (số nguyên)  
2. Chuyển đổi giữa các hệ cơ số thập phân và nhị phần (số chấm động có độ chính xác cao)  
3. Thực hiện cộng, trừ, nhân, chia số nguyên trong các hệ 16, nhị phân, thập phân  
4. Thực hiện các phép toán `AND, OR, XOR, NOT, >=, <=, >, <`  
5. Thực hiện các phép toán `Dịch trái (<<), Dịch phải (>>), Quay trái (ROL), Quay phải (ROR)`  

## Giới hạn thực hiện phép toán  

* Đồ án sử dụng 128bit để lưu trữ số nguyên và số thập phân  
* Giới hạn lưu trữ số nguyên (-2^127 <= x <= 2^127 - 1):  
    `-170141183460469231731687303715884105728 <= x <= 170141183460469231731687303715884105727`  
* Giới hạn lưu trữ số thực:  
    Số dương: `2^-16383 <= x <= (2 - 2^-112) * 2^16384`  
    Số âm: `(2^-112 - 2) * 2^16384 <= x <= -2^-16383`  
