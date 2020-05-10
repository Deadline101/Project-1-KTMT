#include <iostream>
#include <string>
#include "pre.h"
using namespace std;

class QFloat
{
private:
	int _data[4];
public:
	void ScanQFloat()
	{
		try {
			cout << "Enter decimal: ";
			string soThuc;
			getline(cin, soThuc);
			ScanQFloat(*this, soThuc);
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

	void ScanQFloat(QFloat& q, string soThuc)
	{
		if (!checkSpelling(soThuc)) {
			throw WRONG_FORMAT;
		}
		int posDot = soThuc.find('.');
		string Nguyen = soThuc.substr(0, posDot); //phần nguyên
		string thapPhan = soThuc.substr(posDot + 1, soThuc.size() - posDot - 1);//phần thập phân

		//Chuyển phần nguyên sang dạng nhị phân
		string bitNguyen;
		bool sign = false;
		if (Nguyen[0] == '-') {
			sign = true;
			Nguyen = Nguyen.substr(1);
		}
		setBit(0, sign, q);
		setBitNguyen(Nguyen, bitNguyen);
		Nguyen = bitNguyen;

		//Chuyển phần thập phân sang dạng nhị phân
		while (thapPhan[thapPhan.length() - 1] == '0') //Xóa số 0 sau cùng
		{
			thapPhan.erase(thapPhan.begin() + thapPhan.length() - 1);
		}
		string bitThapPhan;
		string res;
		setBitThapPhan(thapPhan, res, bitThapPhan);
		thapPhan = bitThapPhan;

		//Chuyển về dạng chấm động
		string bitSoThuc;
		string e;
		string bitMu;
		string bitTri;
		int i = 0;
		if (Nguyen == "0" && thapPhan != "") {
			bitSoThuc = thapPhan;

			while (bitSoThuc[0] != '1') {
				i++;
				bitSoThuc.insert(i, ".");
			}
			e.insert(0, to_string(16383 - i)); //Phần mũ (K=16383 do có 15 bit)
			bitTri = bitSoThuc.substr(2); //bit phần định trị
			setBitNguyen(e, bitMu);
			if (bitTri.length() < 112) {
				for (int j = 0; j < 112 - bitTri.length(); j++)
					bitTri += "0";
			}
		}

		if (Nguyen != "0" && thapPhan != "") {
			bitSoThuc = Nguyen + thapPhan;
			while (bitSoThuc[0] != '1') {
				i++;
				bitSoThuc.insert(i, ".");
			}
			e.insert(0, to_string(16383 + Nguyen.length() - i)); //Phần mũ (K=16383 do có 15 bit)
			bitTri = bitSoThuc.substr(2); //bit phần định trị
			setBitNguyen(e, bitMu);
			if (bitTri.length() < 112) {
				for (int j = 0; j < 112 - bitTri.length(); j++)
					bitTri += "0";
			}
		}
		for (int i = 0; i < 15; i++)
			bitSoThuc += bitMu;
		for (int i = 0; i < 112; i++)
			bitSoThuc += bitTri;
		setBitSequence(bitSoThuc, q);
	}

	string PrintQFloat(QFloat q)
	{
		string Mu = "0";
		string dec;
		if (getBitAt(0, q) == 1) {
			dec = dec.insert(0, "-");
		}

		for (int i = 15; i > 0; i--) {
			if (getBitAt(i, q) != 0) {
				Mu = findSum(Mu, power("2", to_string(15 - i)));
				Mu = AsubB(Mu, "16383");
			}
		}
		if (Mu[0] == '-') {
			Mu = Mu.substr(1);
			
		}
		//CHƯA XONG
		return dec;
	}

	int getBitAt(int index, QFloat n) {
		int q = index / 32;
		int r = index % 32;

		return (n._data[q] >> (31 - r)) & 1;
	}

	void DecToBin()
	{
		try {
			cout << "Enter decimal: ";
			string str;
			getline(cin, str);
			QFloat q;
			ScanQFloat(q, str);
			cout << "Output: " << DecToBin(q) << endl;
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

	string DecToBin(QFloat x) {
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

	QFloat BinToDec(string dec, QFloat x)
	{
		if (!checkSpellingBitString(dec)) {
			throw WRONG_FORMAT;
		}
		if (dec.length() > 128) {
			throw OUT_OF_RANGE;
		}

		string str;
		for (int i = 0; i < 128; i++) {
			str += to_string(getBitAt(i, x));
		}
		if (str[0] == '1') {
			dec += "-";
		}
    //CHƯA XONG
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

	string power(string str1, string str2) {
		string res = "1";
		for (int i = 0; i < atoi(str2.c_str()); i++) {
			res = AxB(res, str1);
		}
		return res;
	}

	string AxB(string a, string b) {
		string res = "0";
		for (int i = 0; i < atoi(b.c_str()); i++) {
			res = findSum(res, a);
		}
		return res;
	}

	string AsubB(string a, string b) //A-B
	{
		string kq;
		int i = a.length();
		int j = b.length();
		int dem = 0;
		int d = 0;
		if (a == b)
			return "0";
		if (i < j)
		{
			swap(a, b);
			findSub(a, b, kq);
			d = 1;
		}
		else
		{
			if (i == j) {
				for (int k = 0; k < i; k++)
				{
					if (a[dem] > b[dem]) {
						d = 0;
						break;
					}
					else if (a[dem] < b[dem]) {
						d = 1;
						break;
					}
					else dem++;
				}
				if (d == 1)
				{
					swap(a, b);
				}
			}
			findSub(a, b, kq);

		}
		if (d == 1)
			kq.insert(0, "-");
		return kq;
	}

	void findSub(string& a, string& b, string& kq)
	{
		int nho = 0;
		int i = a.length();
		int j = b.length();
		int t = (int)(b[j - 1] - 48);
		for (int k = 0; k < i - j; k++)
			b.insert(0, "0");
		for (int k = 0; k < i - 1; k++) {
			if ((int)(a[i - k - 1] - 48) < t) {
				t = 10 + (int)(a[i - k - 1] - 48) - t;
				kq.insert(0, to_string(t));
				nho = 1;
				t = nho + (int)(b[i - k - 2] - 48);
			}
			else {
				t = (int)(a[i - k - 1] - 48) - t;
				kq.insert(0, to_string(t));
				nho = 0;
				t = nho + (int)(b[i - k - 2] - 48);
			}
		}
		t = (int)(a[0] - 48) - (int)(b[0] - 48);
		kq.insert(0, to_string(t));
	}

	void swap(string& str1, string& str2) {
		string temp = str1;
		str1 = str2;
		str2 = temp;
	}

	void multiplyByTwo(string str, string& res)
	{
		int d = str.length() - 1;
		int t;
		int nho = 0;
		if (str.length() == 1) {
			int a = (int)(str[0] - 48);
			t = a * 2;
			res.insert(0, to_string(t));
		}
		else {
			for (int i = d; i >= 0; i--)
			{
				int a = (int)(str[i] - 48);
				if (i == 0) {
					t = a * 2 + nho;
				}
				else {
					if ((a * 2) > 9) {
						t = a * 2 - 10 + nho;
						nho = 1;
					}
					else {
						t = a * 2 + nho;
						nho = 0;
					}
				}
				res.insert(0, to_string(t));
			}
		}
	}

	void setBitSequence(string str, QFloat& q)
	{
		int count = 127;
		// setup QFloat x
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

	void setBit(int pos, bool value, QFloat& n) {
		int q = pos / 32;
		int r = pos % 32;

		n._data[q] = n._data[q] | (value << (31 - r));
	}

	void setBitThapPhan(string thapPhan, string res, string bitThapPhan)
	{
		int count = 111;
		while (true) {
			if (thapPhan == "") {
				break;
			}
			else {
				count--;
				int d = thapPhan.length();
				multiplyByTwo(thapPhan, res);
				thapPhan = res;

				if (thapPhan.length() > d) {
					res.insert(1, ".");

					bitThapPhan += "1";

				}
				else {
					bitThapPhan += "0";
					res.insert(0, "0.");
				}
				while (res[res.length() - 1] == '0') //Xóa số 0 sau cùng
				{
					res.erase(res.begin() + res.length() - 1);
				}
				if (res == "1.") {
					break;
				}
				if (res[0] == '1' && res != "1.")
					thapPhan = thapPhan.substr(1);

				if (count < -1) {
					break;
				}
				res = "";
			}
		}

		if (count > 0) {
			for (int i = 0; i <= count; i++)
				bitThapPhan += "0";
		}
	}

	void setBitNguyen(string Nguyen, string bitNguyen) //
	{
		int count = 14;
		while (true) {
			// setup QFloat x
			if ((int)(Nguyen[Nguyen.length() - 1] - 48) % 2 == 0) {
				bitNguyen.insert(0, to_string(0));
				count--;
			}
			else {
				bitNguyen.insert(0, to_string(1));
				count--;
			}
			// throw OUT_OF_RANGE
			// count = -1 is ok because if bit[0] is assigned then count = -1
			if (count < -1) {
				throw OUT_OF_RANGE;
			}
			string res = "";
			divideByTwo(Nguyen, res);
			Nguyen = res;
			if (Nguyen == "") {
				break;
			}
		}

	}

	void divideByTwo(string str, string& res)
	{
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

	bool checkSpellingBitString(string bit) {
		for (int i = 0; i < bit.length(); i++) {
			if (bit[i] != '0' && bit[i] != '1') {
				return false;
			}
		}
		return true;
	}

	QFloat operator=(string str) {
		for (int i = 0; i < 4; i++) {
			_data[i] = 0;
		}
		try {
			ScanQFloat(*this, str);
		}
		catch (ERROR e) {
			if (e == WRONG_FORMAT) {
				cout << "Wrong format\n";
			}
			else if (e == OUT_OF_RANGE) {
				cout << "Input is out of range\n";
			}
		}
		return *this;
	}

	QFloat()
	{
		for (int i = 0; i < 4; i++) {
			_data[i] = 0;
		}
	}
	
};

