#include "pre.h"
#include "QInt.h"
// #include "QFloat.h"

string DecToHex(string bit) {
    string res = "";
    string tempstr = "";
    int tempnum = 0;

    int count = 0;
    for (int i = bit.length() - 1; i >= 0; i--) {
        tempstr = tempstr.insert(0, to_string(bit[i] - 48));
        count++;
        if (count == 4) {
            count = 0;                      // reset counter
            tempnum = QInt::binToDec(tempstr);    // convert bin -> dec (apply for small num)
            tempstr = "";                   // reset tempstr
            if (tempnum >= 0 && tempnum <= 9) {
                res = res.insert(0, to_string(tempnum));
            }
            else {
                switch (tempnum) {
                    case 10: {
                        res = res.insert(0, "A");
                    } break;

                    case 11: {
                        res = res.insert(0, "B");
                    } break;

                    case 12: {
                        res = res.insert(0, "C");
                    } break;

                    case 13: {
                        res = res.insert(0, "D");
                    } break;

                    case 14: {
                        res = res.insert(0, "E");
                    } break;

                    case 15: {
                        res = res.insert(0, "F");
                    } break;
                }
            }
        }
    }
    while (true) {
        if (res[0] == '0') {
            res = res.substr(1);
        }
        else {
            break;
        }
    }
    return res;
}


int main(int argc, char const *argv[]) {
    // int a = 0xE;
    // // cout << to_string(a) << endl;
    // int b = 14;
    // printf("%X\n", b);

    string str = "10101011";
    // cout << QInt::binToDec(str) << endl;
    cout << DecToHex(str);

    return 0;
}
