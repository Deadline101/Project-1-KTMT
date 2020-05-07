#ifndef QINT_H_
#define QINT_H_

#include "pre.h"

#define MIN_QINT "-170141183460469231731687303715884105728"
#define MAX_QINT  "170141183460469231731687303715884105727"

class QInt {
    public:

        // input
        void ScanQInt() {
            try {
                cout << "Enter decimal: ";
                string str;
                getline(cin, str);
                ScanQInt(*this, str);
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

        // output
        void PrintQInt() {
            cout << "Output: "<< PrintQInt(*this) << endl;
        }

        // dec to bin
        void DecToBin() {
            try {
                cout << "Enter decimal: ";
                string str;
                getline(cin, str);
                QInt q;
                ScanQInt(q, str);
                cout << "Output: " << DecToBin(q) << endl;
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

        // bin to dec
        void BinToDec() {
            try {
                cout << "Enter bit string: ";
                string str;
                getline(cin, str);
                cout << "Output: " << PrintQInt(BinToDec(str)) << endl;
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

        // bin to hex
        void BinToHex() {
            try {
                cout << "Enter bit string: ";
                string str;// = "10100101";
                getline(cin, str);
                cout << "Output: " << BinToHex(str) << endl;
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

        // dec to hex
        void DecToHex() {
            try {
                cout << "Enter decimal: ";
                string str;
                getline(cin, str);
                QInt q;
                ScanQInt(q, str);
                string bit = "";
                for (int i = 0; i < 128; i++) {
                    bit += to_string(getBitAt(i, q));
                }
                cout << "Output: " << BinToHex(bit) << endl;
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

        // operator and
        QInt operator&(QInt q) {
            return optAnd(*this, q);
        }

        // operator or
        QInt operator|(QInt q) {
            return optOr(*this, q);
        }

        // operator xor
        QInt operator^(QInt q) {
            return optXor(*this, q);
        }

        // operator not
        QInt operator~() {
            return optNot(*this);
        }

        // operator = 
        QInt operator=(QInt q) {
            if (this != &q) {
                for (int i = 0; i < 4; i++) {
                    _data[i] = q._data[i];
                }
            }
            return *this;
        }

        // operator = (string)
        QInt operator=(string str) {
            for (int i = 0; i < 4; i++) {
                _data[i] = 0;
            }
            try {
                ScanQInt(*this, str);
            }
            catch (ERROR e) {
                catchError(e);
            }
            return *this;
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////

        // input: bit string
        // output: string (hexadecimal)
        string BinToHex(string bit) {
            while (bit[0] == '0') {
                bit = bit.substr(1);
            }
            if (!checkSpellingBitString(bit)) {
                throw WRONG_FORMAT;
            }
            if (bit.length() > 128) {
                throw OUT_OF_RANGE;
            }

            // insert 0 into bitstring at head 
            while (bit.length() % 4 != 0) {
                bit = bit.insert(0, "0");
            }

            string res = "";
            int count = 0;
            string temp = "";
            for (int i = bit.length() - 1; i >= 0; i--) {
                temp = temp.insert(0, to_string(bit[i] - 48));
                count++;
                if (count == 4) {
                    count = 0;
                    temp = PrintQInt(BinToDec(temp));
                    int temp1 = atoi(temp.c_str());
                    temp = ""; // reset temp
                    if (temp1 >= 0 && temp1 <= 9) {
                        res = res.insert(0, to_string(temp1));
                    }
                    else {
                        switch (temp1) {
                            case 10:
                                res = res.insert(0, "A");
                                break;

                            case 11: 
                                res = res.insert(0, "B");
                                break;

                            case 12: 
                                res = res.insert(0, "C");
                                break;

                            case 13:
                                res = res.insert(0, "D");
                                break;

                            case 14: 
                                res = res.insert(0, "E");
                                break;

                            case 15:
                                res = res.insert(0, "F");
                                break;
                        }
                    }
                }
            }

            return res == "" ? "0" : res;
        }

        // check input bit string
        bool checkSpellingBitString(string bit) {
            for (int i = 0; i < bit.length(); i++) {
                if (bit[i] != '0' && bit[i] != '1') {
                    return false;
                }
            }
            return true;
        }

        // input: bit (unchecked)
        // output: QInt (just setbit into QInt)
        QInt BinToDec(string bit) {
            while (bit[0] == '0') { // bit = "00000001" -> bit = "1"
                bit = bit.substr(1);
            }
            if (!checkSpellingBitString(bit)) {
                throw WRONG_FORMAT;
            }
            if (bit.length() > 128) {
                throw OUT_OF_RANGE;
            }

            QInt q;
            int count = 127;
            for (int i = bit.length() - 1; i >= 0; i--) {
                setBit(count, (bool)(bit[i] - 48), q);
                count--;
            }
            return q;
        }

        // input: QInt (input from keyboard)
        // output: string (binary)
        string DecToBin(QInt x) {
            string str;
            int count = 0;
            for (int i = 0; i < 128; i++) {
                str += to_string(getBitAt(i, x));
                count++;
                if (count == 4) {
                    count = 0;
                    str += ' ';
                }
            }
            return str;
        }

        string PrintQInt(QInt q) {
            string str = "0";
            QInt temp = q;
            if (getBitAt(0, temp) == 1) {
                QInt one;
                ScanQInt(one, "1");
                temp = optAdd(optNot(temp), one);
            }

            for (int i = 127; i >= 0; i--) {
                if (getBitAt(i, temp) != 0) {
                    str = findSum(str, power("2", to_string(128 - 1 - i)));
                }
            }

            if (getBitAt(0, q) == 1) {
                str = str.insert(0, "-");
            }
            return str;
        }


        void ScanQInt(QInt &q, string str) {
            if (!checkSpelling(str)) {
                throw WRONG_FORMAT;
            }
            // outOfRange hasn't been written yet
            if (inputOutOfRange(str)) {
                throw OUT_OF_RANGE;
            }

            bool sign = false;
            if (str[0] == '-') {
                sign = true;
                str = str.substr(1);
            } 
            setBitSequence(str, q); 
            if (sign) {
                q = optNot(q);
                QInt temp;
                ScanQInt(temp, "1");
                q = optAdd(q, temp);
            }
        }

        // operator ~
        QInt optNot(QInt q) {
            QInt res;
            for (int i = 0; i < 128; i++) {
                if (getBitAt(i, q) == 1) {
                    setBit(i, 0, res);
                }
                else {
                    setBit(i, 1, res);
                }
            }
            return res;
        }

        // operator &
        QInt optAnd(QInt q1, QInt q2) {
            QInt res;
            for (int i = 0; i < 128; i++) {
                // getBitAt(i, q1) & getBitAt(i, q2): int & int. Not QInt & QInt
                setBit(i, getBitAt(i, q1) & getBitAt(i, q2), res);
            }
            return res;
        }

        // operator |
        QInt optOr(QInt q1, QInt q2) {
            QInt res;
            for (int i = 0; i < 128; i++) {
                // getBitAt(i, q1) | getBitAt(i, q2): int | int. Not QInt | QInt
                setBit(i, getBitAt(i, q1) | getBitAt(i, q2), res);
            }
            return res;
        }

        // operator ^
        QInt optXor(QInt q1, QInt q2) {
            QInt res;
            for (int i = 0; i < 128; i++) {
                if (getBitAt(i, q1) != getBitAt(i, q2)) {
                    setBit(i, 1, res);
                }
                else {
                    setBit(i, 0, res);
                }
            }
            return res;
        }

        // operator + (QInt + QInt)
        QInt optAdd(QInt q1, QInt q2) {
            QInt res;

            int temp1 = 0;   
            int temp2 = 0;  

            for (int i = 127; i >= 0; i--) {
                temp1 = getBitAt(i, q1) + getBitAt(i, q2) + temp2;
                if (temp1 == 2) {
                    // res[i] = '0';
                    setBit(i, 0, res);
                    temp2 = 1;
                }
                else if (temp1 == 0) {
                    // res[i] = '0';
                    setBit(i, 0, res);
                    temp2 = 0;
                }
                else if (temp1 == 1){
                    // res[i] = '1';
                    setBit(i, 1, res);
                    temp2 = 0;
                }
                else if (temp1 == 3) {
                    // res[i] = '1';
                    setBit(i, 1, res);
                    temp2 = 1;
                }
            }
            // if positive + positive = negative or negative + negative = positive
            if ((getBitAt(0, q1) == 1 && getBitAt(0, q2) == 1 && getBitAt(0, res) == 0) || (getBitAt(0, q1) == 0 && getBitAt(0, q2) == 0 && getBitAt(0, res) == 1)) {
                throw OUT_OF_RANGE;
            }
            return res;
        }

        void setBitSequence(string str, QInt &q) {
            int count = 127;
            // setup QInt x
            while (true) {
                // if the last num of dec string % 2 == 0 => setBit
                if ((int)(str[str.length() - 1] - 48) % 2 == 0) {
                    setBit(count, 0, q);
                    count--;
                }
                else {
                    setBit(count, 1, q);
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


        // check spelling of input string 
        bool checkSpelling(string str) {
            // "-123" and "123" are ok but "+123" is not :>
            if (!(str[0] == '-' || (str[0] >= '0' && str[0] <= '9'))) {
                return false;
            }
            // range of num: [0, 9]
            for (int i = 1; i < str.length(); i++) {
                if (!(str[i] >= '0' && str[i] <= '9')) {
                    return false;
                }
            }
            return true;
        }

        static void divideByTwo(string str, string &res) {
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

        bool inputOutOfRange(string str) {
            string min = MIN_QINT, max = MAX_QINT;
            min = min.substr(1);

            bool sign = false;
            if (str[0] == '-') {
                sign = true;
                str = str.substr(1);
            }

            // from now on: min.length() = max.length()
            if (str.length() < min.length()) {
                return false;
            }
            else if (str.length() > min.length()) {
                return true;
            }
            else if (min == str || max == str) {
                return false;
            } 

            // str.length() = min.length()
            int count = 0;
            while (true) {
                if (sign) {
                    if (str[count] == min[count]) {
                        count++;
                    }
                }
                else {
                    if (str[count] == max[count]) {
                        count++;
                    }
                }
            }

            if (sign) {
                if (str[count] > min[count]) {
                    return true;
                }
            }
            else {
                if (str[count] > max[count]) {
                    return true;
                }
            }
            return false;
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////

        // return bitSequence of QInt q
        void testScan(QInt q) {
            int count = 0;
            for (int i = 0; i < 128; i++) {
                cout << getBitAt(i, q);
                count++;
                if (count == 4) {
                    cout << " ";
                    count = 0;
                }
            }
            cout << endl;
        }

        QInt() {
            for (int i = 0; i < 4; i++) {
                _data[i] = 0;
            }
        }

        void setBit(int pos, bool value, QInt &n) {
            int q = pos / 32;
            int r = pos % 32;

            n._data[q] = n._data[q] | (value << (31 - r));
        }

        int getBitAt(int index, QInt n) {
            int q = index / 32;
            int r = index % 32;

            return (n._data[q] >> (31 - r)) & 1;
        }

        QInt (const QInt &q) {
            for (int i = 0; i < 4; i++) {
                _data[i] = q._data[i];
            }
        }

    private:
        int _data[4];

        void swap(string &str1, string &str2) {
            string temp = str1;
            str1 = str2;
            str2 = temp;
        }

        string findSum(string str1, string str2) {
            string res = "";
            if (str1.length() < str2.length()) {
                swap(str1, str2);
            }
            int n1 = str1.length(), n2 = str2.length();
            for (int i = 0; i < n1 - n2; i++) {
                str2 = str2.insert(0, "0");
            }

            int temp1 = 0, temp2 = 0;
            for (int i = n1 - 1; i >= 0; i--) {
                temp1 = (int)(str1[i] - 48) + (int)(str2[i] - 48) + temp2;
                temp2 = temp1 / 10;
                temp1 = temp1 % 10;
                // res[i] = char(temp1 + 48);
                res = res.insert(0, to_string(temp1));
            }
            if (temp2 != 0) {
                res = res.insert(0, to_string(temp2));
            }
            return res == "" ? "0" : res;
        }

        string AxB(string a, string b) {
            string res = "0";
            for (int i = 0; i < atoi(b.c_str()); i++) {
                res = findSum(res, a);
            }
            return res;
        }

        string power(string str1, string str2) {
            string res = "1";
            for (int i = 0; i < atoi(str2.c_str()); i++) {
                res = AxB(res, str1);
            }
            return res;
        }

        // // use this func to convert 4bits unsigned like: hex (1010(2) --> A(16))
        // // only work with small number (4bits)
        // int binToDec(string bitStr) {
        //     int res = 0;
        //     for (int i = bitStr.length() - 1; i >= 0; i--) {
        //         res += (int)(bitStr[i] - 48) * pow(2, bitStr.length() - i - 1);
        //     }
        //     return res;
        // }
};


#endif
