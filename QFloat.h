#include "pre.h"

string MultiplyStr2(string s);
string SubString1(string s);
string SubString2(string s);
bool ModString2(string s);
bool isStrZero(string s);
string NormalizeString(std::string& s);
string DivideString2(string s);
void Padding(string& a, string& b);
bool isLargerOrEqual(string a, string b);
string SubtractString(string a, string b);
string AddString(string a, string b);

string MultiplyStr2(string s) {
	string ans;
	int n = s.size();
	int b = 0;
	for (int i = n - 1; i >= 0; i--) {
		int t = (s[i] - '0') * 2 + b;

		if (t / 10 > 0)
			b = 1;
		else
			b = 0;

		t = t % 10;

		ans.push_back(t + '0');
	}

	if (b)
		ans.push_back('1');

	n = ans.size();
	for (int i = 0; i < n / 2; i++) {
		char temp = ans[i];
		ans[i] = ans[n - i - 1];
		ans[n - i - 1] = temp;
	}

	return ans;
}


//Lấy phần nguyên của chuỗi
string SubString1(string s) {
	string ans;
	int i = 0;
	while (s[i] != '.') {
		ans.push_back(s[i]);
		i++;
	}

	return ans;
}

//Lấy phần thập phân của chuỗi
string SubString2(string s) {
	string ans;
	int i = -1;
	while (s[++i] != '.')
		;

	ans = s.substr(i);
	return ans;
}

//Chuỗi nguyên
bool ModString2(string s) {
	int n = s.size();
	return (s[n - 1] - '0') % 2;
}

//Chuỗi đã chuẩn hóa
bool isStrZero(string s) {
	int n = s.size();
	if (n == 0 || (n == 1 && s[0] == '.'))
		return true;
	return false;
}

//Chuẩn hóa chuỗi - bỏ số 0 dư
std::string NormalizeString(std::string& s) {
	int i = 0;
	bool neg = false;
	if (s[0] == '-' || s[0] == '+') {
		if (s[0] == '-')
			neg = true;
		i++;
	}

	//Nếu không có dấu chấm thì thêm vào
	bool point = false;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '.') {
			point = true;
			break;
		}
	if (!point)
		s.push_back('.');

	while (s[i] == '0')		//Bỏ các số 0 đầu
		i++;

	s = s.substr(i);
	i = s.size() - 1;
	while (s[i] == '0') {	//Bỏ các số 0 cuối
		s.pop_back();
		i--;
	}

	if (neg)
		s.insert(s.begin(), '-');
	return s;
}

//string NormalizeNum(string s) { return s; }

//Chia phần nguyên cho số cần đổi, chia thập phân để lấy base của 2
//Chia nguyên bỏ dư, chia thập phân thì cứ chia tới hết digit :) 
string DivideString2(string s) {
	string ans;
	int n = s.size();
	char q, t, r = 0;

	//Chuỗi là phần Thập phân
	if (s[0] == '.') {
		ans.push_back('.');
		int i = 1;
		while (i < n || r) { //Chia hết chiều dài hoặc khi còn dư
			if (i < n)
				t = s[i] - '0';
			else
				t = 0;
			q = (10 * r + t) / 2;
			r = t % 2;
			ans.push_back(q + '0');
			i++;
		}
	}

	//Chuỗi là Số nguyên
	else {
		int i = 0;
		while (i < n) {
			t = s[i] - '0';
			q = (10 * r + t) / 2;
			r = t % 2;

			ans.push_back(q + '0');
			i++;
		}
		if (ans[0] == '0')
			ans = ans.substr(1);
	}
	return ans;
}

void Padding(string& a, string& b) {
	NormalizeString(a);
	NormalizeString(b);
	int la, lb, la1, lb1;		//Chiều dài chuỗi a, b, chiều dài phần nguyên a, b
	la1 = lb1 = 0;

	la = a.size();
	lb = b.size();

	while (a[la1] != '.')
		la1++;

	while (b[lb1] != '.')
		lb1++;

	//Chiều dài phần TP
	la = la - la1;
	lb = lb - lb1;


	//Thêm 0 vào trước cho chiều dài nguyên bằng nhau
	while (la1 < lb1) {
		a.insert(a.begin(), '0');
		la1++;
	}

	while (lb1 < la1) {
		b.insert(b.begin(), '0');
		lb1++;
	}

	//Thêm 0 vào TP
	while (la < lb) {
		a.push_back('0');
		la++;
	}

	while (lb < la) {
		b.push_back('0');
		lb++;
	}
}

bool isLargerOrEqual(string a, string b) {
	Padding(a, b);
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i])
			return true;
		if (a[i] < b[i])
			return false;
	}
	return true;
}

//Mặc định a lớn hơn b (kiểm tra trước khi gọi hàm này)
//Lấy từ hàm cộng
string SubtractString(string a, string b) {
	Padding(a, b);

	string ans;
	char temp = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] == '.') {
			ans.insert(ans.begin(), '.');
			continue;
		}

		char val = a[i] - b[i] - temp;

		//Nhớ
		if (val < 0) {
			val += 10;
			temp = 1;
		}
		else
			temp = 0;

		ans.insert(ans.begin(), val + '0');
	}
	return ans;
}

//Cộng 2 chuỗi không âm
string AddString(string a, string b) {

	Padding(a, b);

	string ans;
	char temp = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] == '.') {
			ans.insert(ans.begin(), '.');
			continue;
		}

		char val = a[i] - '0' + b[i] - '0' + temp;

		//Nhớ
		if (val >= 10)
			temp = 1;
		else
			temp = 0;

		val %= 10;

		ans.insert(ans.begin(), val + '0');
	}

	if (temp)
		ans.insert(ans.begin(), '1');

	return ans;
}

class Qfloat
{
	unsigned int _element[4];
public:
	bool GetBitI(int i) {
		if (i > 127)
			return false;

		int n = i / 32, m = i % 32;
		return (_element[n] >> (31 - m)) & 1;
	}
	void SetBitI(int i, bool val) {
		if (i > 127)
			return;

		int n = i / 32, m = i % 32;
		unsigned int b = 1;

		b <<= (31 - m); // Dịch trái số 1 (31-m) bit
		if (!val)// Nếu bit cần sửa là 0 thì phải đảo hết cả chuỗi bit thành 11...0..111
			b = ~b;

		if (val)
			_element[n] = _element[n] | b;
		else
			_element[n] = _element[n] & b;

	}
	Qfloat() {
		_element[0] = _element[1] = _element[2] = _element[3] = 0;
	}
	//s = chuỗi hệ 10
	Qfloat(string s) {
		for (int i = 0; i < 4; i++)
			_element[i] = 0;

		NormalizeString(s);
		if (s[0] == '-') {
			SetBitI(0, true);
			s = s.substr(1);
		}
		//Lấy phần nguyên
		string nguyen = SubString1(s);
		vector<bool> bitNguyen;

		while (!isStrZero(nguyen)) {
			bitNguyen.push_back(ModString2(nguyen)); //Thứ tự bị ngược
			nguyen = DivideString2(nguyen);
		}
		//Lấy phần thập phân
		string tphan = SubString2(s);
		string temp = ".5";
		vector<bool> bitTP;
		int i = 114; //Số bit tối đa

		while (i > 0 && !isStrZero(tphan)) {
			if (isLargerOrEqual(tphan, temp)) {
				bitTP.push_back(true); //Thứ tự thuận
				tphan = SubtractString(tphan, temp);
			}
			else {
				bitTP.push_back(false);
			}
			temp = DivideString2(temp);
			i--;
		}

		//Tìm exp => mantissa
		int32_t exp;
		//Phần nguyên = 0
		if (bitNguyen.size() == 0)
			//Số 0
			if (bitTP.size() == 0)
				return;
		//Trường hợp 0.000xxx
			else {
				int j = 1;
				while (bitTP[j - 1] == 0)
					j++;
				exp = -j;
			}
		//Phần nguyên khác không
		else
			exp = bitNguyen.size() - 1;

		//Điền giá trị exp
		//Trường hợp số quá nhỏ -> số dạng ko chuẩn. Số lớn -> NaN? nên ko quan tâm?

		exp = exp + 0x00004000 - 1; // Cộng với 2^14 (bias) trừ 1
		i = 15;

		if (exp <= 0)
			for (int i = 1; i < 16; i++)
				SetBitI(i, false);

		int exp1 = exp;
		while (exp > 0) {
			SetBitI(i, exp & 1);
			exp = exp >> 1;
			i--;
		}

		//Điền Mantissa
		int n = bitNguyen.size(), m = bitTP.size();

		//Tìm bit số 1 đầu tiên trong dãy nhị phân
		if (n > 0) {
			bitNguyen.pop_back();
			n--;
		}
		else {
			while (m > 0) {
				if (!bitTP[0]) {
					bitTP.erase(bitTP.begin());
					m--;
				}
				else
					break;
			}
			//Tìm thấy số 1 đầu tiên, xóa nó luôn
			bitTP.erase(bitTP.begin());
			m--;
		}

		//Nếu là số dạng ko chuẩn, điền số 1 lại, thêm số 0 lại cho đủ :v
		if (exp1 <= 0) {
			exp1++;
			bitTP.insert(bitTP.begin(), true);
			m++;
			while (exp1 <= 0) {
				exp1++;
				bitTP.insert(bitTP.begin(), false);
				m++;
			}
		}

		//Điền
		i = 16;
		while (n > 0 && i < 128) {
			SetBitI(i, bitNguyen[n - 1]);
			bitNguyen.pop_back();
			n--;
			i++;
		}
		while (m > 0 && i < 128) {
			SetBitI(i, bitTP[0]);
			bitTP.erase(bitTP.begin());
			m--;
			i++;
		}
	}
	string Print(bool print_console) {
		//Tính ra phần mũ
		int exp = 0;
		int base = 1;
		int i;
		int spec = 0; //Số 0, NaN, Inf
					  //Spec: 0: số không chuẩn và chuẩn, 1: số không, 2: NaN, 3: Inf
		bool subnormal = false; //Số không chuẩn
		string ans = ".";

		//Kiểm tra số 0, NaN hay Inf
		bool tmp = GetBitI(1);
		for (i = 2; i < 16; i++) {
			if (GetBitI(i) != tmp)
				break;
		}
		if (i == 16) {
			if (tmp) {//Toàn bit 1 ở phần exp 
				spec = 3; //Inf
				for (; i < 128; i++)
					if (GetBitI(i)) {
						//Nếu có bit ở phần trị khác không thì không phải Inf
						spec = 2;
						break;
					}
			}
			else {//Toàn bit 0 
				spec = 1;
				for (; i < 128; i++)
					if (GetBitI(i)) {
						spec = 0;
						break;
					}
			}
		}

		else spec = 0;
		if (spec == 0) { //Khác không


			for (i = 0; i < 15; i++) {
				exp += base * GetBitI(15 - i);
				base *= 2;
			}

			// if (exp == 0) {
			// 	subnormal = true;
			// 	return "Denormalized number";
			// }//xử lý cho số không chuẩn



			exp += 1 - 0x00004000; //Trừ lại cho bias
								   //Chuyển về dạng nhị phân mà không có nhân 2 mũ
			vector<bool> nguyen, tphan;
			//Luôn có số 1 ở phần nguyên nếu là số chuẩn
			if (!subnormal)
				nguyen.push_back(true);

			i = 16;
			if (exp >= 0) {
				while (exp > 0) {
					nguyen.push_back(GetBitI(i));
					i++;
					exp--;
				}
				while (i < 128) {
					tphan.push_back(GetBitI(i));
					i++;
				}
			}
			else {
				//Đưa số 1 ở phần nguyên vào sau dấu chấm hoặc số 0 nếu là số ko chuẩn
				nguyen.clear();
				tphan.push_back(!subnormal);
				exp++;
				//Thêm các số 0 vào 
				while (exp < 0) {
					tphan.insert(tphan.begin(), false);
					exp++;
				}
				//Đưa các số phần thập phân vào
				while (i < 128) {
					tphan.push_back(GetBitI(i));
					i++;
				}
			}

			string ngn = "1";
			//Phần thập phân, bắt đầu từ 0.5, tìm tới đâu chia đôi tới đó
			string tp = ".5";

			int n = nguyen.size(), m = tphan.size();
			i = 0;

			//Cộng các lũy thừa dương của 2 vào phần nguyên
			while (i < n) {
				if (nguyen[n - 1 - i])
					ans = AddString(ans, ngn);
				ngn = MultiplyStr2(ngn);
				i++;
			}

			i = 0;
			//Cộng các lũy thừa âm của 2 vào phần thập phân
			while (i < m) {
				if (tphan[i])
					ans = AddString(ans, tp);
				tp = DivideString2(tp);
				i++;
			}

			//chèn thêm 0 vào trước các số chưa có phần nguyên
			if (ans[0] == '.')
				ans.insert(ans.begin(), '0');

			//Nếu là số âm
			if (GetBitI(0)) {
				if (print_console)
					//cout << '-';
					ans.insert(ans.begin(), '-');
			}
		}
		else {
			switch (spec) {
			case 1: ans = "0.0"; break;
			case 2: ans = "NaN"; break;
			case 3:
				if (GetBitI(0))
					ans.insert(ans.begin(), '-');
				ans.append("Inf"); break;
			}

		}
		if (print_console)
			cout << ans << endl;
		return ans;
	}
	void PrintBit() {
		for (int i = 0; i <= 127; i++) {
			if (i <= 16) {
				if (i == 1) {
					cout << " ";
				}
				else if (i == 16) {
					cout << " ";
				}
				cout << GetBitI(i);
				continue;
			}
			if (i % 8 == 0 && i > 0)
				cout << ' ';
			cout << GetBitI(i);
		}
		cout << endl;
	}
	//Đầu vào là Qfloat, đầu ra là chuỗi số chấm động 128 bit
	static string DecToBin(Qfloat x) {
		string ans;
		for (int i = 0; i <= 127; i++)
			ans.push_back((char)x.GetBitI(i) + '0');
		return ans;
	}
	//bit phải là chuỗi bit đủ 128 bits
	static Qfloat BinToDec(string bit) {
		Qfloat ans;
		int n = bit.size();
		while (n < 128) {
			bit.push_back('0');
			n++;
		}
		for (int i = 0; i <= 127; i++) ans.SetBitI(i, bit[i] - '0');
		return ans;
	}
};

