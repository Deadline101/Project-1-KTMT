#include <iostream>
using namespace std;
#include <string>
#include <conio.h>
#include <fstream>

void reset(string &a)
{
	a = "1";
	for (int i = 0; i < 38; ++i) {
		a = "0" + a;
	}
}

class Qint
{
	unsigned int _element[4];
private:
	static string scanDecimal() {
		string str;
		char c;
		cout << "Nhap chuoi(Decimal): ";
		while (true) {
			if (c = _getch()) {
				if (c == '-' && str.size() == 0) {
					str += c;
					//cout << c;
				}
				if (c >= '0' && c <= '9') {
					str += c;
					//cout << c;
				}
				else if (c == 8 && str.size() != 0) {
					str.erase(str.end() - 1);
				}
				else if (c == 13) {
					cout << c;
					break;
				}
				system("@cls");
				cout << "Nhap chuoi(Decimal): " << str;
			}
		}
		cout << endl;
		if (Qint::isOutRangeDecimal(str) || str.size() == 0 || str == "-") {
			cout << "So nhap vao sai" << endl;
			return "";
		}
		//cout << "So vua nhap: " << str << endl;
		return str;
	}
	static string scanBinary() {
		string str;
		char c;
		cout << "Nhap chuoi(Binary): ";
		while (true) {
			if (c = _getch()) {
				if (c == '0' || c == '1') {
					str += c;
					//cout << c;
				}
				else if (c == 8 && str.size() != 0) {
					str.erase(str.end() - 1);
				}
				else if (c == 13) {
					cout << c;
					break;
				}
				system("@cls");
				cout << "Nhap chuoi(Binary): " << str;
			}
		}
		cout << endl;
		if (Qint::isOutRangeBin(str) || str.size() == 0) {
			cout << "So nhap vao sai" << endl;
			return "";
		}
		//cout << "So vua nhap: " << str << endl;
		return str;
	}
	void printQInt(Qint qint) {
		string a = ElementToStringBin(0),
			b = ElementToStringBin(1),
			c = ElementToStringBin(2),
			d = ElementToStringBin(3);
		cout << "DecimalVer: " << this->StringDecimal() << endl;
		cout << "HexadecimalVer: " << this->StringHexadecimal() << endl;
		cout << "BinaryVer: " << this->StringBin() << endl;
		cout << "subString 0: " << a << endl;
		cout << "subString 1: " << b << endl;
		cout << "subString 2: " << c << endl;
		cout << "subString 3: " << d << endl;
		cout << "e0: " << this->_element[0] << endl;
		cout << "e1: " << this->_element[1] << endl;
		cout << "e2: " << this->_element[2] << endl;
		cout << "e3: " << this->_element[3] << endl;
	}
	string scanQint(Qint &qint) {
		string str = Qint::scanDecimal();
		this->modifireStringBin(this->StringDecToStringBin(str, 128));
		return str;
	}
	string DecToBin(Qint &qint) {
		this->scanQint();
		cout << "BINARY: " << this->StringBin() << endl;
		return this->StringBin();
	}
	string BinToDec(Qint &qint) {
		string str = Qint::scanBinary();
		this->modifireStringBin(str);
		cout << "DECIMAL: " << this->StringDecimal() << endl;
		return this->StringDecimal();
	}
	string BinToHex(Qint &qint) {
		string str = Qint::scanBinary();
		this->modifireStringBin(str);
		cout << "HEXADECIMAL: " << this->StringHexadecimal() << endl;
		return this->StringHexadecimal();
	}
	string DecToHex(Qint &qint) {
		string str = Qint::scanDecimal();
		this->modifireStringBin(StringDecToStringBin(str, 128));
		cout << "HEXADECIMAL: " << this->StringHexadecimal() << endl;
		return this->StringHexadecimal();
	}
public:
	static string setStringTo128bits(string str) {
		int n = str.size();
		for (int i = 0; i < 128 - n; ++i) {
			str = '0' + str;
		}
		return str;
	}
	static string Offset2(string str) {
		string resault = str;
		string value1 = "1";
		value1 = Qint::setStringTo128bits(value1);
		for (int i = 0; i < 128; ++i) {
			if (resault[i] == '1') {
				resault[i] = '0';
			}
			else if (resault[i] == '0') {
				resault[i] = '1';
			}
		}
		int excess = 0;
		for (int i = 127; i >= 0; --i) {
			resault[i] = (resault[i] - '0') + (value1[i] - '0') + '0' + excess;
			if (resault[i] - '0' == 3) {
				resault[i] = '1';
				excess = 1;
			}
			else if (resault[i] - '0' == 2) {
				resault[i] = '0';
				excess = 1;
			}
			else if (resault[i] - '0' == 1) {
				resault[i] = '1';
				excess = 0;
			}
			else if (resault[i] - '0' == 0) {
				resault[i] = '0';
				excess = 0;
			}
		}
		return resault;
	}
	static string Cong2DayBit(string a, string b) {
		string c;
		a = Qint::setStringTo128bits(a);
		b = Qint::setStringTo128bits(b);
		c = Qint::setStringTo128bits(c);
		int excess = 0;

		for (int i = 127; i >= 0; --i) {
			c[i] = a[i] + b[i] - '0' + excess;
			if (c[i] == '0') {
				excess = 0;
			}
			else if (c[i] == '1') {
				excess = 0;
			}
			else if (c[i] == '2') {
				c[i] = '0';
				excess = 1;
			}
			else if (c[i] == '3') {
				c[i] = '1';
				excess = 1;
			}
		}
		return c;
	}
	static string Tru2DayBit(string a, string b) {
		string c;
		a = Qint::setStringTo128bits(a);
		b = Qint::setStringTo128bits(b);
		c = Qint::setStringTo128bits(c);
		b = Qint::Offset2(b);
		c = Qint::Cong2DayBit(a, b);
		return c;
	}
	static string Nhan2Daybit(string a, string b) {
		a = Qint::setStringTo128bits(a);
		b = Qint::setStringTo128bits(b);
		bool isOpposite = 0;
		if (a[0] == '1' && b[0] == '1') {
			a = Qint::Offset2(a);
			b = Qint::Offset2(b);
		}
		else if (a[0] != b[0]) {
			isOpposite = 1;
			if (a[0] == '1') {
				a = Qint::Offset2(a);
			}
			else if (b[0] == '1') {
				b = Qint::Offset2(b);
			}
		}
		string c;
		c = b;
		for (int i = 0; i < 129; ++i) {
			c = '0' + c;
		}
		int k = 128;
		string m, q;
		while (k > 0) {
			if (c[256] == '1') {
				m = c.substr(1, 128);
				q = c.substr(129, 128);
				m = Qint::Cong2DayBit(m, a);
				c = '0' + m + q;
			}
			c.erase(c.end() - 1);
			c.insert(c.begin(), '0');
			--k;
		}
		c = c.substr(129, 128);
		if (isOpposite) {
			c = Qint::Offset2(c);
		}
		return c;
	}
	static string Chia2Daybit(string Q, string M) {
		Q = Qint::setStringTo128bits(Q);
		M = Qint::setStringTo128bits(M);
		string A;
		A = Qint::setStringTo128bits(A);

		int k = 128;
		bool signQ = 0, signM = 0;
		if (Q[0] == '1') {
			signQ = 1;
			Q = Qint::Offset2(Q);
		}
		if (A[0] == '1') {
			signM = 1;
			M = Qint::Offset2(M);
		}
		while (k > 0) {
			A.erase(A.begin());
			A.insert(A.end(), Q[0]);
			Q.erase(Q.begin());
			Q.insert(Q.end(), '0');
			A = Qint::Tru2DayBit(A, M);
			if (A[0] == '1') {
				Q[Q.size() - 1] = '0';
				A = Qint::Cong2DayBit(A, M);
			}
			else {
				Q[Q.size() - 1] = '1';
			}
			--k;
		}
		if (signQ != signM) {
			Q = Qint::Offset2(Q);
		}
		cout << "Thuong: " << Qint::StringBinToStringDec(Q) << endl;
		cout << "Du: " << Qint::StringBinToStringDec(A) << endl;
		return Q;
	}
	static string Cong2ChuoiIntDuong(string a, string b) {
		string c;
		for (int i = 0; i < 39; ++i) {
			c = '0' + c;
		}
		int excess = 0;
		int temp = 0;
		for (int i = 38; i >= 0; --i) {
			temp = a[i] + b[i] - '0' - '0' + excess;
			c[i] = (a[i] + b[i] - '0' - '0' + excess) % 10 + '0';
			if (temp >= 10) {
				excess = 1;
			}
			else {
				excess = 0;
			}
			if (i > a.size() && i > b.size()) {
				break;
			}
		}
		return c;
	}
	static string XoayTrai(string a, string b) {
		a = Qint::setStringTo128bits(a);
		for (int i = 0; i < stoi(b); ++i) {
			a.insert(a.end(), a[0]);
			a.erase(a.begin());
		}
		return a;
	}
	static string XoayPhai(string a, string b) {
		a = Qint::setStringTo128bits(a);
		for (int i = 0; i < stoi(b); ++i) {
			a.insert(a.begin(), a[127]);
			a.erase(a.end() - 1);
		}
		return a;
	}
	static string StringDecToStringBin(string str, int nBits) {
		int PHUGIA = 0;
		string newString;
		int tmp = 0;
		bool isNegative = 0;
		if (str[0] == '-') {
			isNegative = 1;
			str.erase(str.begin());
		}
		while (str.size() != 0) {
			if ((str[str.size() - 1] - '0') % 2 == 0) {
				newString = '0' + newString;
			}
			else {
				newString = '1' + newString;
			}
			PHUGIA = 0;
			for (int i = 0; i < str.size(); ++i) {
				tmp = str[i] - '0';
				str[i] = ((str[i] - '0') / 2) + PHUGIA + '0';
				if (tmp % 2 == 0) {
					PHUGIA = 0;
				}
				else if (tmp % 2 == 1) {
					PHUGIA = 5;
				}
			}
			if (str[0] - '0' == 0) {
				str.erase(str.begin());
			}
		}
		int newStringLength = newString.size();
		for (int i = 0; i < nBits - newStringLength; ++i) {
			newString = '0' + newString;
		}
		if (isNegative) {
			newString = Qint::Offset2(newString);
		}
		return newString;
	}
	static string StringBinToStringDec(string str) {
		if (str == "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000") {
			return "-170141183460469231731687303715884105728";
		}
		int strLength = str.length();
		str = Qint::setStringTo128bits(str);
		bool isNegative = 0;
		if (str[0] == '1') {
			isNegative = 1;
			str = Qint::Offset2(str);
		}
		string c;
		string resault;
		for (int i = 0; i < 39; ++i) {
			resault = resault += '0';
		}
		int count1 = 0;
		int excess1 = 0;
		int tmp1 = 0;
		for (int i = 1; i < 128; i++) { //Tong day nhi phan
			reset(c);
			if (str[i] == '1') {
				for (int k = 0; k < 127 - i; ++k) { //Nhan 2 n lan
					count1 = 0;
					tmp1 = 0;
					while (true) { //Nhan 2
						if (39 - count1 == 0) {
							break;
						}
						tmp1 = c[38 - count1] - '0';
						c[38 - count1] = ((c[38 - count1] - '0') * 2 % 10) + excess1 + '0';
						if (tmp1 >= 5) {
							excess1 = 1;
						}
						else {
							excess1 = 0;
						}
						count1++;
					}
				}
				resault = Qint::Cong2ChuoiIntDuong(resault, c);
			}
		}
		while (true) {
			if (resault[0] != '0' || resault.size() == 1) {
				break;
			}
			resault.erase(resault.begin());
		}
		if (isNegative) {
			resault = '-' + resault;
		}
		return resault;
	}
	static string StringHexToStringBin(string str) {
		bool isNegative = 0;
		if (str[0] == '-') {
			isNegative = 1;
			str.erase(str.begin());
		}
		string resault;
		string tmp;
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '0')
				resault += "0000";
			else if (str[i] == '1')
				resault += "0001";
			else if (str[i] == '2')
				resault += "0010";
			else if (str[i] == '3')
				resault += "0011";
			else if (str[i] == '4')
				resault += "0100";
			else if (str[i] == '5')
				resault += "0101";
			else if (str[i] == '6')
				resault += "0110";
			else if (str[i] == '7')
				resault += "0111";
			else if (str[i] == '8')
				resault += "1000";
			else if (str[i] == '9')
				resault += "1001";
			else if (str[i] == 'A' || str[i] == 'a')
				resault += "1010";
			else if (str[i] == 'B' || str[i] == 'b')
				resault += "1011";
			else if (str[i] == 'C' || str[i] == 'c')
				resault += "1100";
			else if (str[i] == 'D' || str[i] == 'd')
				resault += "1101";
			else if (str[i] == 'E' || str[i] == 'e')
				resault += "1110";
			else if (str[i] == 'F' || str[i] == 'f')
				resault += "1111";
		}
		resault = Qint::setStringTo128bits(resault);
		if (isNegative) {
			resault = Qint::Offset2(resault);
		}
		return resault;
	}
	static string StringHexToStringDec(string str) {
		return Qint::StringBinToStringDec(Qint::StringHexToStringBin(str));
	}
	int StringBinToInt(string str, int nBits) {
		int resault = 0;
		for (int i = 0; i < nBits; ++i) {
			resault += (str[i] - '0') * pow(2, nBits - 1 - i);
		}
		return resault;
	}
	string ElementToStringBin(int i) {
		return(this->StringDecToStringBin(to_string(_element[i]), 32));
	}
	string StringBin() {
		return ElementToStringBin(0) + ElementToStringBin(1) + ElementToStringBin(2) + ElementToStringBin(3);
	}
	string StringDecimal() {
		return this->StringBinToStringDec(this->StringBin());
	}
	string StringHexadecimal() {
		string binString = this->StringBin();
		string hexadecimalString;
		string tmp;
		bool isNegative = 0;
		if (binString[0] == '1') {
			binString = Qint::Offset2(binString);
			isNegative = 1;
		}
		for (int i = 0; i < 32; ++i) {
			tmp = binString.substr(4 * i, 4);
			char tmpp;
			if (tmp == "0000")
				tmpp = '0';
			else if (tmp == "0001")
				tmpp = '1';
			else if (tmp == "0010")
				tmpp = '2';
			else if (tmp == "0011")
				tmpp = '3';
			else if (tmp == "0100")
				tmpp = '4';
			else if (tmp == "0101")
				tmpp = '5';
			else if (tmp == "0110")
				tmpp = '6';
			else if (tmp == "0111")
				tmpp = '7';
			else if (tmp == "1000")
				tmpp = '8';
			else if (tmp == "1001")
				tmpp = '9';
			else if (tmp == "1010")
				tmpp = 'A';
			else if (tmp == "1011")
				tmpp = 'B';
			else if (tmp == "1100")
				tmpp = 'C';
			else if (tmp == "1101")
				tmpp = 'D';
			else if (tmp == "1110")
				tmpp = 'E';
			else if (tmp == "1111")
				tmpp = 'F';
			hexadecimalString += tmpp;
		}
		while (true) {
			if (hexadecimalString[0] != '0' || hexadecimalString.size() == 1) {
				break;
			}
			hexadecimalString.erase(hexadecimalString.begin());
		}
		if (isNegative) {
			hexadecimalString = '-' + hexadecimalString;
		}

		return hexadecimalString;
	}
	void modifireStringBin(string newStringBin) {
		newStringBin = Qint::setStringTo128bits(newStringBin);
		string initString0, initString1, initString2, initString3;
		initString0 = newStringBin.substr(0, 32);
		initString1 = newStringBin.substr(32, 32);
		initString2 = newStringBin.substr(64, 32);
		initString3 = newStringBin.substr(96, 32);

		_element[0] = this->StringBinToInt(initString0, 32);
		_element[1] = this->StringBinToInt(initString1, 32);
		_element[2] = this->StringBinToInt(initString2, 32);
		_element[3] = this->StringBinToInt(initString3, 32);
	}
	Qint() {
		_element[0] = _element[1] = _element[2] = _element[3] = 0;
	}
	Qint(string series) {
		_element[0] = _element[1] = _element[2] = _element[3] = 0;
		if (Qint::isOutRangeDecimal(series)) {
			cout << ">>>Khoi tao that bai<<<" << endl;
			return;
		}
		string newString = this->StringDecToStringBin(series, 128);

		string initString0, initString1, initString2, initString3;
		initString0 = newString.substr(0, 32);
		initString1 = newString.substr(32, 32);
		initString2 = newString.substr(64, 32);
		initString3 = newString.substr(96, 32);

		_element[0] = this->StringBinToInt(initString0, 32);
		_element[1] = this->StringBinToInt(initString1, 32);
		_element[2] = this->StringBinToInt(initString2, 32);
		_element[3] = this->StringBinToInt(initString3, 32);
	}
	Qint(string strBin, bool isBin) {
		_element[0] = _element[1] = _element[2] = _element[3] = 0;
		if (Qint::isOutRangeBin(strBin)) {
			cout << ">>>Khoi tao that bai<<<" << endl;
			return;
		}
		strBin = Qint::setStringTo128bits(strBin);
		string initString0, initString1, initString2, initString3;
		initString0 = strBin.substr(0, 32);
		initString1 = strBin.substr(32, 32);
		initString2 = strBin.substr(64, 32);
		initString3 = strBin.substr(96, 32);

		_element[0] = this->StringBinToInt(initString0, 32);
		_element[1] = this->StringBinToInt(initString1, 32);
		_element[2] = this->StringBinToInt(initString2, 32);
		_element[3] = this->StringBinToInt(initString3, 32);
	}
	static bool isOutRangeDecimal(string str) {
		string maxInt = "170141183460469231731687303715884105727";
		string minInt = "170141183460469231731687303715884105728";
		if (str[0] == '-') {
			string newString = str.substr(1, str.length() - 1);
			if (newString.length() > minInt.length()) {
				return true;
			}
			else if (newString.length() == minInt.length()) {
				if (newString > minInt) {
					return true;
				}
				return false;
			}
			return false;
		}
		else {
			if (str.length() > maxInt.length()) {
				return true;
			}
			else if (str.length() == maxInt.length()) {
				if (str > maxInt) {
					return true;
				}
				return false;
			}
			return false;
		}
	}
	static bool isOutRangeBin(string str) {
		string maxInt = "01111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
		string minInt = "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		if (str.size() < 128) {
			return false;
		}
		if (str[0] == '1') {
			string newString = str;
			if (newString.length() > minInt.length()) {
				return true;
			}
			else if (newString.length() == minInt.length()) {
				return false;
			}
			return false;
		}
		else if (str[0] == '0') {
			if (str.length() > maxInt.length()) {
				return true;
			}
			else if (str.length() == maxInt.length()) {
				return false;
			}
			return false;
		}
	}
	void scanQint() {
		this->scanQint(*this);
	}
	void printQInt() {
		this->printQInt(*this);
	}
	void DecToBin() {
		this->DecToBin(*this);
	}
	void BinToDec() {
		this->BinToDec(*this);
	}
	void BinToHex() {
		this->BinToHex(*this);
	}
	void DecToHex() {
		this->DecToHex(*this);
	}
	Qint operator +(Qint & const qint) {
		string newStringBin;
		newStringBin = this->Cong2DayBit(this->StringBin(), qint.StringBin());
		return Qint(newStringBin, 1);
	}
	Qint operator -(Qint & const qint) {
		string newStringBin;
		newStringBin = this->Cong2DayBit(this->StringBin(), Qint::Offset2(qint.StringBin()));
		return Qint(newStringBin, 1);
	}
	Qint operator *(Qint & const qint) {
		string multi = Qint::Nhan2Daybit(this->StringBin(), qint.StringBin());
		string newStringBin = multi;
		return Qint(newStringBin, 1);
	}
	Qint operator /(Qint & const qint) {
		string newStringBin = Qint::Chia2Daybit(this->StringBin(), qint.StringBin());
		return Qint(newStringBin, 1);
	}
	bool operator ==(Qint & const qint) {
		if (this->StringBin() == qint.StringBin()) {
			return true;
		}
		return false;
	}
	bool operator !=(Qint & const qint) {
		if (*this == qint) {
			return false;
		}
		return true;
	}
	bool operator <=(Qint & const qint) {
		if (*this == qint) {
			return true;
		}
		string a = this->StringBin(), b = qint.StringBin();
		if (a[0] == '0' && b[0] == '1') {
			return false;
		}
		else if (a[0] == '1' && b[0] == '0') {
			return true;
		}
		else {
			if (a < b) {
				return true;
			}
			return false;
		}
	}
	bool operator >=(Qint & const qint) {
		if (*this == qint) {
			return true;
		}
		string a = this->StringBin(), b = qint.StringBin();
		if (a[0] == '0' && b[0] == '1') {
			return true;
		}
		else if (a[0] == '1' && b[0] == '0') {
			return false;
		}
		else {
			if (a > b) {
				return true;
			}
			return false;
		}
	}
	bool operator >(Qint & const qint) {
		if (*this <= qint) {
			return false;
		}
		return true;
	}
	bool operator <(Qint & const qint) {
		if (*this >= qint) {
			return false;
		}
		return true;
	}
	Qint & operator &(Qint &const qint) {
		string newStringBin;
		string a = this->StringBin(), b = qint.StringBin();
		for (int i = 0; i < 128; ++i) {
			if (a[i] == '1' && b[i] == '1') {
				newStringBin = newStringBin + '1';
				continue;
			}
			newStringBin = newStringBin + '0';
		}
		this->modifireStringBin(newStringBin);
		return *this;
	}
	Qint & operator |(Qint &const qint) {
		string newStringBin;
		string a = this->StringBin(), b = qint.StringBin();
		for (int i = 0; i < 128; ++i) {
			if (a[i] == '1' | b[i] == '1') {
				newStringBin = newStringBin + '1';
				continue;
			}
			newStringBin = newStringBin + '0';
		}
		this->modifireStringBin(newStringBin);
		return *this;
	}
	Qint & operator ^(Qint &const qint) {
		string newStringBin;
		string a = this->StringBin(), b = qint.StringBin();
		for (int i = 0; i < 128; ++i) {
			if (a[i] != b[i]) {
				newStringBin = newStringBin + '1';
				continue;
			}
			newStringBin = newStringBin + '0';
		}
		this->modifireStringBin(newStringBin);
		return *this;
	}
	Qint & operator ~() {
		string newStringBin = this->StringBin();
		for (int i = 0; i < 128; ++i) {
			if (newStringBin[i] == '0') {
				newStringBin[i] = '1';
				continue;
			}
			newStringBin[i] = '0';
		}
		this->modifireStringBin(newStringBin);
		return *this;
	}
	Qint & operator <<(int n) {
		string a = this->StringBin();
		a = a.substr(n, 128 - n);
		int length = a.size();
		for (int i = 0; i < length; ++i) {
			a = a + '0';
		}
		this->modifireStringBin(a);
		return *this;
	}
	Qint & operator >>(int n) {
		string a = this->StringBin();
		a = a.substr(0, 128 - n);
		if (a[0] == '1') {
			for (int i = 0; i < n; ++i) {
				a = '1' + a;
			}
		}
		else {
			a = Qint::setStringTo128bits(a);
		}
		
		this->modifireStringBin(a);
		return *this;
	}
};

void menu()
{
	cout << ">>>>>>>>>MENU<<<<<<<<<<" << endl;
	cout << "1. scanQint" << endl;
	cout << "2. printQint" << endl;
	cout << "3. DecToBin" << endl;
	cout << "4. BinToDec" << endl;
	cout << "5. BinToHex" << endl;
	cout << "6. DecToHex" << endl;
	cout << "7. Cong/Tru/Nhan/Chia" << endl;
	cout << "8. Toan tu dac biet" << endl;
	cout << "9. Toan tu logic" << endl;
	cout << "10. Dich trai/phai" << endl;
}

void launch()
{
	int option = 0;
	menu();
	cout << ">> "; cin >> option; cin.ignore();
	if (option == 1) {
		Qint qint;
		qint.scanQint();
		qint.printQInt();
	}
	else if (option == 2) {
		Qint qint;
		qint.scanQint();
		qint.printQInt();
	}
	else if (option == 3) {
		Qint qint;
		qint.DecToBin();
		qint.printQInt();
	}
	else if (option == 4) {
		Qint qint;
		qint.BinToDec();
		qint.printQInt();
	}
	else if (option == 5) {
		Qint qint;
		qint.BinToHex();
		qint.printQInt();
	}
	else if (option == 6) {
		Qint qint;
		qint.DecToHex();
		qint.printQInt();
	}
	else if (option == 7) {
		Qint qint1, qint2;
		cout << "-------qint1-------";
		qint1.scanQint();
		cout << "-------qint2-------";
		qint2.scanQint();
		char c; cout << "Toan tu(+,-,*,/): "; cin >> c;
		if (c == '+') {
			Qint qint3 = qint1 + qint2;
			qint3.printQInt();
		}
		else if (c == '-') {
			Qint qint3 = qint1 - qint2;
			qint3.printQInt();
		}
		else if (c == '*') {
			Qint qint3 = qint1 * qint2;
			qint3.printQInt();
		}
		else if (c == '/') {
			Qint qint3 = qint1 / qint2;
			qint3.printQInt();
		}
	}
	else if (option == 8) {
		Qint qint1, qint2;
		cout << "-------qint1-------";
		qint1.scanQint();
		cout << "-------qint2-------";
		qint2.scanQint();
		char c; cout << "Toan tu(&,|,^,~): "; cin >> c;
		if (c == '&') {
			qint1 = qint1 & qint2;
			qint1.printQInt();
		}
		else if (c == '|') {
			qint1 = qint1 | qint2;
			qint1.printQInt();
		}
		else if (c == '^') {
			qint1 = qint1 ^ qint2;
			qint1.printQInt();
		}
		else if (c == '~') {
			qint1 = ~qint1;
			qint1.printQInt();
			qint2 = ~qint2;
			qint1.printQInt();
		}
	}
	else if (option == 9) {
		Qint qint1, qint2;
		cout << "-------qint1-------";
		qint1.scanQint();
		cout << "-------qint2-------";
		qint2.scanQint();
		if (qint1 == qint2) {
			cout << "qint1 == qint2" << endl;
		}
		else if (qint1 < qint2) {
			cout << "qint1 < qint2" << endl;
		}
		else if (qint1 > qint2) {
			cout << "qint1 > qint2" << endl;
		}
	}
	else if (option == 10) {
		Qint qint;
		qint.scanQint();
		string oper; cout << "<<,>>: "; getline(cin, oper);
		if (oper == ">>") {
			int nn = 0; cout << "qint>>(n)"; cin >> nn; cin.ignore();
			qint = qint >> nn;
		}
		if (oper == "<<") {
			int nn = 0; cout << "qint<<(n)"; cin >> nn; cin.ignore();
			qint = qint << nn;
		}
		qint.printQInt();
	}
}



int main(int argc, char** argv)
{
	/*while (true) {
		launch();
	}
*/
	Qint qint1("-170141183460469231731687303715884105728"), qint2("1");
	Qint qint3 = qint1 * qint2;
	qint1.printQInt();
	qint2.printQInt();
	qint3.printQInt();
	return 0;
}