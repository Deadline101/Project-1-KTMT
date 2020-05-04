#ifndef QINT_H_
#define QINT_H_

#include "pre.h"

class QInt {
    public:

    #pragma region interface :)

        /************* INPUT *************/
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

        /************* LOGIC: OPERATOR AND (&) *************/
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

        /************* LOGIC: OPERATOR OR (|) *************/
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

        /************* LOGIC: OPERATOR XOR (^) *************/
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

        /************* LOGIC: OPERATOR NOT (~) *************/
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
        // bool operator>(QInt q) {

        // }

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

    private:
        int _data[4];
};

#endif