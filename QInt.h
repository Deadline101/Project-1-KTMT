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
                str = DecToBin(q);

                // print :> a little bit of make color
                int count = 0;
                cout << "Output: ";
                for (int i = 0; i < str.length(); i++) {
                    cout << str[i];
                    count++;
                    if (count == 4) {
                        count = 0;
                        cout << " ";
                    }
                }
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

        // operator ==
        bool operator==(QInt q) {
            for (int i = 0; i < 128; i++) {
                if (getBitAt(i, *this) != getBitAt(i, q)) {
                    return false;
                }
            }
            return true;
        }

/*  * operator+, written by TheMinh, rewrite by BaoLong
    QInt operator +(QInt & const qint) {
		string newStringBin;
		newStringBin = this->Cong2DayBit(this->StringBin(), qint.StringBin());
		this->modifireStringBin(newStringBin);
		return *this;
	}
*/
        QInt operator+(QInt q) {
            try {
                // recall optAdd(QInt, QInt): return QInt
                return optAdd(*this, q, false);
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

/*  * operator-, written by TheMinh, reWrite by BaoLong
	QInt operator -(QInt & const qint) {
		string newStringBin;
		newStringBin = this->Cong2DayBit(this->StringBin(), QInt::Offset2(qint.StringBin()));
		this->modifireStringBin(newStringBin);
		return *this;
	}
*/
        QInt operator-(QInt q) {
            // // create a two'2 complement number
            // QInt temp = convertToTwoComplement(q);
            // // QInt temp;
            // // temp = "1";
            // // // temp = temp + ~q;
            // // temp = optAdd(temp, ~q);

            // // return *this + that two'2 complement number (using operator +)
            // return *this + temp;
            if (*this == q) {
                return *(new QInt());
            }
            try {
                return optSub(*this, q, false);
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

/*  * operator *
	QInt operator *(QInt & const qint) {
		string multi = QInt::Nhan2Daybit(this->StringBin(), qint.StringBin());
		string newStringBin = multi;
		this->modifireStringBin(newStringBin);
		return *this;
	}
*/
        // operator *
        QInt operator*(QInt q) {
            try {
                return optMultiply(*this, q);
            }
            catch (ERROR e) {
                catchError(e);
            }
        }
/*
    Qint operator /(Qint & const qint) {
        string newStringBin = Qint::Chia2Daybit(this->StringBin(), qint.StringBin());
        return Qint(newStringBin, 1);
    }
*/
        QInt operator/(QInt q) {
            try {
                return optDivide(*this, q);
            }
            catch (ERROR e) {
                catchError(e);
            }
        }

        // operator>>
        QInt operator>>(int n) {
            return optShiftRight(*this, n);
        }

        // operator<<
        QInt operator<<(int n) {
            return optShiftLeft(*this, n);
        }

        // rol
        QInt rol(QInt q, int n) {
            QInt res = q;
            string str = DecToBin(res);

            int temp;
            // temp = bit[0]
            // delete bit[0] in bit string
            // bit string += bit[0]
            for (int i = 0; i < n; i++) {
                temp = (int)(str[0] - 48);
                str = str.substr(0);
                str += to_string(temp);
            }

            res = BinToDec(str);
            return res;
        }

        // ror
        QInt ror(QInt q, int n) {
            QInt res = q;
            string str = DecToBin(res);

            int temp;
            // temp = bit[127]
            // delete bit[127] in bit string
            // insert bit[127] into bit string at pos 0
            for (int i = 0; i < n; i++) {
                temp = (int)(str[127] - 48);
                str = str.substr(0, 127);
                str.insert(0, to_string(temp));
            }

            res = BinToDec(str);
            return res;
        }

        // operator >
        bool operator>(QInt q) {
            return optGreaterThan(*this, q);
        }

        // operator <
        bool operator<(QInt q) {
            return optSmallerThan(*this, q);
        }

        // operator <=
        bool operator<=(QInt q) {
            return optSmallerThanOrEqual(*this, q);
        }

        // operator >=
        bool operator>=(QInt q) {
            return optGreaterThanOrEqual(*this, q);
        }

/////////////////////////////////////////////////////////////////////////////////////////////////////////

        QInt optSub(QInt q1, QInt q2, bool mys) {
            QInt temp = convertToTwoComplement(q2);
            return optAdd(q1, temp, mys);
        }

        bool isMin(QInt q) {
            if (getBitAt(0, q) == 1) {
                for (int i = 1; i < 128; i++) {
                    if (getBitAt(i, q) != 0) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        QInt convertToTwoComplement(QInt q) {
            if (isMin(q)) {
                return q;
            }
            QInt temp;
            temp = "1";
            return optAdd(temp, ~q, false);
        }

        /*  divide: q1/q2
            input: 2 QInt
            output: QInt res 
        */
        QInt optDivide(QInt q1, QInt q2) {
            QInt zero;
            zero = "0";
            if (q2 == zero) {
                throw DIVIDE_BY_ZERO;
            }
            bool s1 = false, s2 = false;
            if (getBitAt(0, q1) == 1) {
                s1 = true;
                // QInt temp;
                // temp = "1";
                // // q1 = ~q1 + temp;
                // q1 = optAdd(~q1, temp);
                q1 = convertToTwoComplement(q1);
            }
            if (getBitAt(0, q2) == 1) {
                s2 = true;
                // QInt temp; 
                // temp = "1";
                // // q2 = ~q2 + temp;
                // q2 = optAdd(~q2, temp);
                q2 = convertToTwoComplement(q2);
            }

            string str1 = DecToBin(q1);
            string str2 = DecToBin(q2);
            string res = divideTwoString(str1, str2, s1, s2);

            string testRange = convertBinaryStringToDecimalString(res);
            if (inputOutOfRange(testRange)) {
                throw OUT_OF_RANGE;
            }

            return BinToDec(res);
        }

        /*  divide by 2 signed string (binary)
            input: 2 positive string, 2 signed of these strings
            output: bit string res (signed)
        */
        string divideTwoString(string Q, string M, bool s1, bool s2) {
            string A = (new QInt())->DecToBin(*(new QInt()));
            int k = 128;
            while (k > 0) {
                A.erase(A.begin());
                A.insert(A.end(), Q[0]);
                Q.erase(Q.begin());
                Q.insert(Q.end(), '0');
                // A = DecToBin(optAdd(BinToDec(A), BinToDec(M)));
                // A = DecToBin(BinToDec(A) - BinToDec(M));
                A = DecToBin(optSub(BinToDec(A), BinToDec(M), true));
                if (A[0] == '1') {
                    Q[Q.length() - 1] = '0';
                    // A = DecToBin((BinToDec(A) + BinToDec(M)));
                    A = DecToBin(optAdd(BinToDec(A), BinToDec(M), true));
                }
                else {
                    Q[Q.length() - 1] = '1';
                }
                k--;
            }

            // Q[128] -> Q[129] (bit 0 is for signal)
            if (isMin(BinToDec(Q))) {
                if (s1 != s2) {
                    Q = Q.insert(0, "1");
                }
                else {
                    Q = Q.insert(0, "0");
                }
                return Q;
            }

            if (s1 != s2) {
                // QInt temp;
                // temp = "1";
                // Q = DecToBin(optAdd(~BinToDec(Q), temp));
                // Q = DecToBin(~BinToDec(Q) + temp);
                Q = DecToBin(convertToTwoComplement(BinToDec(Q)));
            }
            return Q;
        }

        /*  multiply 2 QInt
            input: 2 QInt
            output: QInt (res)
        */
        QInt optMultiply(QInt q1, QInt q2) {
            bool s1 = false, s2 = false;
            if (getBitAt(0, q1) == 1) {
                s1 = true;
                // QInt temp;
                // temp = "1";
                // // q1 = ~q1 + temp;
                // q1 = optAdd(~q1, temp);
                q1 = convertToTwoComplement(q1);
            }
            if (getBitAt(0, q2) == 1) {
                s2 = true;
                // QInt temp; 
                // temp = "1";
                // // q2 = ~q2 + temp;
                // q2 = optAdd(~q2, temp);
                q2 = convertToTwoComplement(q2);
            }

            string str1 = DecToBin(q1);
            string str2 = DecToBin(q2);
            string res = multiplyTwoString(str1, str2, s1, s2);

            string testRange = convertBinaryStringToDecimalString(res);
            if (inputOutOfRange(testRange)) {
                throw OUT_OF_RANGE;
            }

            res = res.substr(129, 128);
            return BinToDec(res);
        }

        // input: signed bit string
        // output: signed decimal string
        string convertBinaryStringToDecimalString (string bit) {
            bool s = false;
            if (bit[0] == '1') {
                s = true;
                // bit = ~bit
                for (int i = 0; i < bit.length(); i++) {
                    if (bit[i] == '1') {
                        bit[i] = '0';
                    }
                    else {
                        bit[i] = '1';
                    }
                }

                // bit = bit + 1
                int temp1 = 0;
                int temp2 = 1;  // suppose 1 is remainder
                for (int i = bit.length() - 1; i >= 0; i--) {
                    temp1 = (int)(bit[i] - 48) + 0 + temp2;
                    if (temp1 == 2) {
                        // res[i] = '0';
                        // setBit(i, 0, res);
                        bit[i] = '0';
                        temp2 = 1;
                    }
                    else if (temp1 == 0) {
                        // res[i] = '0';
                        // setBit(i, 0, res);
                        bit[i] = '0';
                        temp2 = 0;
                    }
                    else if (temp1 == 1){
                        // res[i] = '1';
                        // setBit(i, 1, res);
                        bit[i] = '1';
                        temp2 = 0;
                    }
                    else if (temp1 == 3) {
                        // res[i] = '1';
                        // setBit(i, 1, res);
                        bit[i] = '1';
                        temp2 = 1;
                    }
                }
            }

            string res = "";
            for (int i = bit.length() - 1; i >= 0; i--) {
                if (bit[i] != '0') {
                    res = findSum(res, power("2", to_string(bit.length() - 1 - i)));
                }
            }
            if (s) {
                res = res.insert(0, "-");
            }

            return res == "" ? "0" : res;
        }

        /*  multiply 2 positive string (binary)
            input: 2 positive string, 2 signed of these strings
            output: bit string res (signed)
        */
        string multiplyTwoString(string bit1, string bit2, bool s1, bool s2) {
            string res = "";
            res = bit2;
            for (int i = 0; i < 129; i++) {
                res = '0' + res;
            }
            int k = 128;
            string m, q;
            while (k > 0) {
                if (res[256] == '1') {
                    m = res.substr(1, 128);
                    q = res.substr(129, 128);
                    m = DecToBin(optAdd(BinToDec(m), BinToDec(bit1), true));
                    res = '0' + m + q;
                }
                res.erase(res.end() - 1);
                res.insert(res.begin(), '0');
                k--;
            }
            // res = res.substr(129, 128);
            if (s1 != s2) {
                // bit = ~bit
                for (int i = 0; i < res.length(); i++) {
                    if (res[i] == '1') {
                        res[i] = '0';
                    }
                    else {
                        res[i] = '1';
                    }
                }

                // bit = bit + 1
                int temp1 = 0;
                int temp2 = 1;  // suppose 1 is remainder
                for (int i = res.length() - 1; i >= 0; i--) {
                    temp1 = (int)(res[i] - 48) + 0 + temp2;
                    if (temp1 == 2) {
                        // res[i] = '0';
                        // setBit(i, 0, res);
                        res[i] = '0';
                        temp2 = 1;
                    }
                    else if (temp1 == 0) {
                        // res[i] = '0';
                        // setBit(i, 0, res);
                        res[i] = '0';
                        temp2 = 0;
                    }
                    else if (temp1 == 1){
                        // res[i] = '1';
                        // setBit(i, 1, res);
                        res[i] = '1';
                        temp2 = 0;
                    }
                    else if (temp1 == 3) {
                        // res[i] = '1';
                        // setBit(i, 1, res);
                        res[i] = '1';
                        temp2 = 1;
                    }
                }
            }
            return res;
        }

        /*  opt <<
            input: QInt, n
            output: QInt (res)
        */
        QInt optShiftLeft(QInt q1, int n) {
            string str = DecToBin(q1);
            str = str.substr(n);

            while (str.length() != 128) {
                str += "0";
            }

            QInt q = BinToDec(str);
            return q;
        }

        /*  opt >>
            input: QInt, n
            output: QInt (res)
        */
        QInt optShiftRight(QInt q1, int n) {
            string str = DecToBin(q1);
            str = str.substr(0, str.length() - n);

            if (str[0] == '1') {
                while (str.length() != 128) {
                    str.insert(0, "1");
                }
            }
            else {
                while (str.length() != 128) {
                    str.insert(0, "0");
                }
            }

            QInt q = BinToDec(str);
            return q;
        }

        /*  bin to hex 
            input: bit string
            output: string (hexadecimal)
        */
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

        /*  bin to dec
            input: bit (unchecked)
            output: QInt (just setbit into QInt)
        */
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

        /*  dec to bin
            input: QInt (input from keyboard)
            output: string (binary)
        */
        string DecToBin(QInt x) {
            string str;
            for (int i = 0; i < 128; i++) {
                str += to_string(getBitAt(i, x));
            }
            return str;
        }

        /*  printQInt
            input: QInt
            output: string (decimal)
        */
        string PrintQInt(QInt q) {
            string str = "0";
            QInt temp = q;
            // convert to positive number for calculating
            if (getBitAt(0, temp) == 1) {
                temp = convertToTwoComplement(temp);
            }

            // calculating
            for (int i = 127; i >= 0; i--) {
                if (getBitAt(i, temp) != 0) {
                    str = findSum(str, power("2", to_string(128 - 1 - i)));
                }
            }

            // and signed 
            if (getBitAt(0, q) == 1) {
                str = str.insert(0, "-");
            }
            return str;
        }

        void ScanQInt(QInt &q, string str) {
            if (!checkSpelling(str)) {
                throw WRONG_FORMAT;
            }
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
                q = convertToTwoComplement(q);
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
        QInt optAdd(QInt q1, QInt q2, bool mys) {
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

            if (mys) {
                return res;
            }
            if (getBitAt(0, q1) == getBitAt(0, q2) && getBitAt(0, q1) != getBitAt(0, res)) {
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

        // str: unsigned decimal
        // res stands for result :))
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

        // check if str (signed decimal) is out of range or not
        bool inputOutOfRange(string str) {
            string min = MIN_QINT, max = MAX_QINT;

            if (str == min || str == max) {
                return false;
            }
            // if str > max
            if (greaterThan(str, max)) {
                return true;
            }
            // if str <= min. but str cant equal to min because the first if-clause has already solved that :)
            if (!greaterThan(str, min)) {
                return true;
            }
        }

        /*  compare 2 string
            input: 2 signed string
            output: str1 > str2 ? true : false
        */
        bool greaterThan(string str1, string str2) {
            if (str1 == str2) {
                return false;
            }

            bool s1 = false, s2 = false;
            if (str1[0] == '-') {
                s1 = true;
                str1 = str1.substr(1);
            }
            if (str2[0] == '-') {
                s2 = true;
                str2 = str2.substr(1);
            }

            // compare negative to positive
            if (s1 == true && s2 == false) {
                return false;
            }
            // compare positive to negative
            else if (s1 == false && s2 == true) {
                return true;
            }

            bool isGreaterThan; // compate 2 unsigned string
            if (str1.length() > str2.length()) {
                isGreaterThan = true;
            }
            else if (str1.length() < str2.length()) {
                isGreaterThan = false;
            }
            else {
                // str1.length() = str2.length()
                int count = 0;
                while (str2[count] == str1[count]) {
                    count++;
                }
                if (str1[count] > str2[count]) {
                    isGreaterThan = true;
                }
                else {
                    isGreaterThan = false;
                }
            }

            if (s1 == true && s2 == true) {
                return !isGreaterThan;
            }
            else if (s1 == false && s2 == false) {
                return isGreaterThan;
            }
        }

        /*  opt >
            input: QInt, QInt
            output: q1 > q2 ? true : false
        */
        bool optGreaterThan(QInt q1, QInt q2) {
            string str1 = PrintQInt(q1);
            string str2 = PrintQInt(q2);

            return greaterThan(str1, str2);
        } 

        /*  opt <
            input: QInt, QInt
            output: q1 < q2 ? true : false
        */
        bool optSmallerThan(QInt q1,QInt q2) {
            if (!optGreaterThan(q1, q2) && !(q1 == q2)) {
                return true;
            }
            return false;
        }

        /*  opt >=
            input: QInt, QInt
            output: q1 >= q2 ? true : false
        */
        bool optGreaterThanOrEqual(QInt q1,QInt q2) {
            if (optGreaterThan(q1, q2) || q1 == q2) {
                return true;
            }
            return false;
        }

        /*  opt <=
            input: QInt, QInt
            output: q1 <= q2 ? true : false
        */
        bool optSmallerThanOrEqual(QInt q1,QInt q2) {
            if (!optGreaterThan(q1, q2)) {
                return true;
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

        // return bitSequence of QInt q
        void testScan() {
            testScan(*this);
        }

        // constructor
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

        // copy constructor
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
};


#endif