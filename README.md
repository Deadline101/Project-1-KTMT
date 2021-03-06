# Project 1 - Môn Kiến trúc máy tính & Hợp ngữ  

* Đồ án lập trình tính toán và lưu trữ số nguyên lớn và số chấm động độ chính xác bố của cao có độ dài 128 bit  
* Team đồ án:  
    1. Nguyễn Bảo Long  
    2. Võ Thế Minh  
    3. Trà Anh Toàn  
    4. Phạm Văn Minh Phương  
    5. Mai Ngọc Tú  

## Chức năng  

1. Chuyển đổi giữa các hệ cơ số 16, thập phân, nhị phân (số nguyên)  
2. Chuyển đổi giữa các hệ cơ số thập phân và nhị phần (số chấm động có độ chính xác cao)  
3. Thực hiện cộng, trừ, nhân, chia số nguyên trong các hệ 16, nhị phân, thập phân  
4. Thực hiện các phép toán `AND, OR, XOR, NOT, >=, <=, >, <`  
5. Thực hiện các phép toán `Dịch trái (<<), Dịch phải (>>), Quay trái (ROL), Quay phải (ROR)`  

## Giới hạn thực hiện phép toán  

* Đồ án sử dụng 128bit để lưu trữ số nguyên và số thập phân  
* Giới hạn lưu trữ số nguyên (`-2^127 <= x <= 2^127 - 1`):  
    `-170141183460469231731687303715884105728 <= x <= 170141183460469231731687303715884105727`  
* Giới hạn lưu trữ số thực:  
    Số dương: `2^-16383 <= x <= (2 - 2^-112) * 2^16384`  
    Số âm: `(2^-112 - 2) * 2^16384 <= x <= -2^-16383`  

## Demo hình ảnh  

* Ảnh màn hình chính  
![Ảnh màn hình chính](./commit/home.png)  
  
* Chuyển từ nhị phân sang thập phân và hệ 16  
![Chuyển từ nhị phân sang thập phân và hệ 16](./commit/binToDecAndHex.png)  
  
* Chuyển từ hệ thập phân sang hệ 16 và nhị phân  
![Chuyển từ hệ thập phân sang hệ 16 và nhị phân](./commit/DecToBinAndHex.png)  
  
* Chuyển từ hệ thập phân sang hệ nhị phân đối với số thực  
![Chuyển từ hệ thập phân sang hệ nhị phân đối với số thực](./commit/decToBinReal.png)  
  
* Chuyển từ nhị phân sang thập phân đối với số thực  
![Chuyển từ nhị phân sang thập phân đối với số thực](./commit/binToDecReal.png)  
  
* Thực hiện các phép toán `AND, OR, XOR, NOT, >=, <=, >, <`: Có thể chọn hệ số  
![Thực hiện các phép toán `AND, OR, XOR, NOT, >=, <=, >, <`](./commit/andOrXorNot.png)  
  
* Thực hiện các phép toán `+, -, *, /`: Có thể chọn hệ cơ số ở bản chọn bên cạnh  
![Thực hiện các phép toán `+, -, *, /`](./commit/calculate2Num.png)  
  
* Thực hiện các phép toán `Dịch trái (<<), Dịch phải (>>), Quay trái (ROL), Quay phải (ROR)`: Có thể chọn loại cơ số ở bảng chọn bên cạnh  
![Thực hiện các phép toán `Dịch trái (<<), Dịch phải (>>), Quay trái (ROL), Quay phải (ROR)`](./commit/rotate_dichBit.png)  
