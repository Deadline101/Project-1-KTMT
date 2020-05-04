#ifndef QINT_H_
#define QINT_H_

#include "pre.h"

class QInt {
    public:

    #pragma region interface :)

        /************* INPUT // not completed yet :))// *************/
        void ScanQInt() {
            QInt x;

            try {
                // not completed yet :))
                ScanQInt(x);
            }
            catch (ERROR e) {
                if (e == WRONG_FORMAT) {
                    cout << "Wrong format\n";
                }
                else if (e == OUT_OF_RANGE) {
                    cout << "Input is out of range\n";
                }
            }
        }

        /************* LOGIC: OPERATOR AND (&)(not tested yet) *************/
        QInt operator&(QInt q) {
            QInt res;
            int a;
            for (int i = 0; i < 128; i++) {
                a = getBitAt(i) & q.getBitAt(i);
                if (a) {
                    res.setBit1(i);
                }
                else {
                    res.setBit0(i);
                }
            }
            return res;
        }

        /************* LOGIC: OPERATOR OR (|)(not tested yet) *************/
        QInt operator|(QInt q) {
            QInt res;
            int a;
            for (int i = 0; i < 128; i++) {
                a = getBitAt(i) | q.getBitAt(i);
                if (a) {
                    res.setBit1(i);
                }
                else {
                    res.setBit0(i);
                }
            }
            return res;
        }

        /************* LOGIC: OPERATOR XOR (^)(not tested yet) *************/
        QInt operator^(QInt q) {
            QInt res;
            int a;
            for (int i = 0; i < 128; i++) {
                a = getBitAt(i) ^ q.getBitAt(i);
                if (a) {
                    res.setBit1(i);
                }
                else {
                    res.setBit0(i);
                }
            }
            return res;
        }

        /************* LOGIC: OPERATOR NOT (~)(not tested yet) *************/
        QInt operator~() {
            QInt res;
            for (int i = 0; i < 128; i++) {
                if (getBitAt(i)) {
                    res.setBit0(i);
                }
                else {
                    res.setBit1(i);
                }
            }
        }

        /************* LOGIC: OPERATOR > *************/
        bool operator>(QInt q) {

        }

        /************* OPERATOR < *************/
        /************* OPERATOR <= *************/
        /************* OPERATOR >= *************/
        /************* OPERATOR == *************/
        /************* OPERATOR = *************/

        /************* dec->hex *************/
        void DecToHex() {
            QInt x;
            // in a basic way :))
            try {
                ScanQInt(x);
                string res = DecToHex(x);
                cout << res << endl;
            }
            catch (ERROR e) {
                if (e == WRONG_FORMAT) {
                    cout << "Wrong format\n";
                }
                else if (e == OUT_OF_RANGE) {
                    cout << "Input is out of range\n";
                }
            }
        }

    #pragma endregion

        string DecToHex(QInt x) {
            string res = "";
            string tempstr = "";
            int tempnum = 0;

            int count = 0;
            for (int i = 127; i >= 0; i--) {
                tempstr = tempstr.insert(0, to_string(getBitAt(i)));
                count++;
                if (count == 4) {
                    count = 0;                      // reset counter
                    tempnum = binToDec(tempstr);    // convert bin -> dec (apply for small num)
                    tempstr = "";                   // reset tempstr
                    if (tempnum >= 0 || tempnum <= 9) {
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

        void divideByTwo(string str, string &res) {
            if (str.length() == 1 && str[0] < '2') {
                return;
            }
            if (str[0] < '2') {
                int a = (int)(str[0] - 48) * 10 + (int)(str[1] - 48);
                res = res + to_string(a / 2);
                a = a - (a / 2) * 2;
                str = str.substr(2);
                str.insert(0, to_string(a));
                divideByTwo(str, res);
            }
            else {
                int a = (int)(str[0] - 48);
                res = res + to_string(a / 2);
                a = a - (a / 2) * 2;
                str = str.substr(1);
                str.insert(0, to_string(a));
                divideByTwo(str, res);
            }
        }

        bool checkSpell(string str) {
            // check if input = "@#qwi123123" -> throw wrong_input
            if (!(str[0] == '-' || str[0] == '+' || (str[0] >= '0' && str[0] <= '9'))) {
                return false;
            }
            for (int i = 1; i < str.length(); i++) {
                if (!(str[i] >= '0' && str[i] <= '9')) {
                    return false;
                }
            }
            return true;
        }

        // not done yet
        void ScanQInt(QInt &x) {
            string str;
            cout << "Enter QInt: ";
            getline(cin, str);

            if (!checkSpell(str)) {
                throw WRONG_FORMAT;
            }

            bool sign;
            if (str[0] == '-') {
                sign = 1;
                str = str.substr(1);
            }
            else {
                sign = 0;
                // "+123" -> "123"
                if (str[0] == '+') {
                    str = str.substr(1);
                }
            }

            // may throw out_of_range
            setBitSequence(str);

            // if str == "-something" is true
            if (sign) {
                ~*this;
                setBit1(0);

            }

            // // out of range
            // if (!sign && getBitAt(0) == 1 || (sign && getBitAt(0) == 0)) {
            //     throw OUT_OF_RANGE;
            // }
        }

        // make a bit string (128 bits)
        void setBitSequence(string str) {
            int count = 127;
            while (true) {
                // setup QInt x
                if ((int)(str[str.length() - 1] - 48) % 2 == 0) {
                    setBit0(count);
                    count--;
                }
                else {
                    setBit1(count);
                    count--;
                }
                // throw OUT_OF_RANGE
                // count = -1 is ok because if bit[0] is assigned then count = -1
                if (count < -1) {
                    throw OUT_OF_RANGE;
                }
                string res = "";
                divideByTwo(str, res);
                str = res;
                if (str == "") {
                    break;
                }
            }
        }

        void setBit1(int index) {
            int q = index / 32;
            int r = index % 32;

            _data[q] | (1 << (31 - r));
        }

        void setBit0(int index) {
            int q = index / 32;
            int r = index % 32;

            _data[q] | (0 << (31 - r));
        }

        int getBitAt(int index) {
            int q = index / 32;
            int r = index % 32;

            return (_data[q] >> (31 - r)) & 1;
        }

        QInt() {
            for (int i = 0; i < 4; i++) {
                _data[0] = 0;
            }
        }

        string getData() {

        }

        void setData() {

        }

        // apply for small num
        static
        int binToDec(string bitStr) {
            int res = 0;
            for (int i = bitStr.length() - 1; i >= 0; i--) {
                res += (int)(bitStr[i] - 48) * pow(2, bitStr.length() - i - 1);
            }
            return res;
        }
    private:

        int _data[4];
};

#endif