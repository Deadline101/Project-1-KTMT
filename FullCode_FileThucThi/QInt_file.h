#ifndef HANDLE_OUTPUT_H_
#define HANDLE_OUTPUT_H_

#include "pre.h"
#include "QInt.h"

struct DataInt {
	string base1;
	string base2;
	string num1;
	string num2;
	string opt;
	int format = 0;
};

// đọc file thành từng dòng ra vector 
vector<string> loadDataFromFileInt(string fileName) {
	string s;
	vector<string> res;
	fstream file;
	file.open(fileName, ios::in);
	while (!file.eof()) {
		getline(file, s);
		res.push_back(s);
	}
	file.close();
	return res;
}

vector<DataInt> loadDataFromArrayStringInt(vector<string> ListData) // Đọc data từ từng dòng vào struct 
{
	vector<DataInt> SaveData;
	// neu có oper thì có num1 và num2 có base 1 base 2 = 0  trừ toán tử ~ chỉ có num1
	// neu k co oper thi có base1 base2 và num1
	string ListOpe[] = { "+","- ","*","/",">","<",">=","<=","==","&","|","^","<<",">>","ror","rol" };
	for (int i = 0; i < ListData.size(); i++) {
		stringstream ss(ListData[i]);
		DataInt data;
		for (int j = 0; j < 16; j++) {
			if (ListData[i].find(ListOpe[j]) < 306 && ListData[i].find(ListOpe[j]) >= 0) {
				// set data vào struct
				ss >> data.base1;
				ss >> data.num1;
				ss >> data.opt;
				ss >> data.num2;
				data.format = 1;
				SaveData.push_back(data);
				goto end;
			}
		}
		if (ListData[i].find('~') == 2) {
			// set data
			ss >> data.base1;
			ss >> data.opt;
			ss >> data.num1;
			data.base2 = "";
			data.num2 = "";
			data.format = 2;
			SaveData.push_back(data);
		}
		else {
			// set data
			ss >> data.base1;
			ss >> data.base2;
			ss >> data.num1;
			data.opt = "";
			data.num2 = "";
			data.format = 3;
			SaveData.push_back(data);
		}
	end: {}
	}
	return SaveData;
}

vector<string> setDataToVectorStringInt(vector<DataInt> data) {
	vector<string> vector_result;
	// string listOpt[] = {"+","-","*","/",">","<",">=","<=","==","&","|","^","<<",">>","ror","rol"};
	for (int i = 0; i < data.size(); i++) {
		string result = "";
		// toán tử 2 ngôi 
		if (data[i].format == 1) {
			QInt q1, q2, res;
			switch (stoi(data[i].base1)) {
				case 10: {
					q1.mScanQInt(data[i].num1);
					if (data[i].opt != ">>" && data[i].opt != "<<") {
						q2.mScanQInt(data[i].num2);
					}
				} break;

				case 2: {
					q1.mScanBin(data[i].num1);
					if (data[i].opt != ">>" && data[i].opt != "<<" && data[i].opt != "ror" && data[i].opt != "rol") {
						q2.mScanBin(data[i].num2);
					}
				} break;

				case 16: {
					q1.mScanHex(data[i].num1);
					if (data[i].opt != ">>" && data[i].opt != "<<" && data[i].opt != "ror" && data[i].opt != "rol") {
						q2.mScanHex(data[i].num2);
					}
				} break;
			}

			if (data[i].opt == "+") {
				res = q1 + q2;
			}
			else if (data[i].opt == "-") {
				res = q1 - q2;
			}
			else if (data[i].opt == "*") {
				res = q1 * q2;
			}
			else if (data[i].opt == "/") {
				res = q1 / q2;
			}
			else if (data[i].opt == ">") {
				if (q1 > q2) {
					result = "TRUE";
				}
				else {
					result = "FALSE";
				}
				// vector_result.push_back(result);
			}
			else if (data[i].opt == "<") {
				if (q1 < q2) {
					result = "TRUE";
				}
				else {
					result = "FALSE";
				}
				// vector_result.push_back(result);
			}
			else if (data[i].opt == ">=") {
				if (q1 >= q2) {
					result = "TRUE";
				}
				else {
					result = "FALSE";
				}
				// vector_result.push_back(result);
			}
			else if (data[i].opt == "<=") {
				if (q1 <= q2) {
					result = "TRUE";
				}
				else {
					result = "FALSE";
				}
				// vector_result.push_back(result);
			}
			else if (data[i].opt == "==") {
				if (q1 == q2) {
					result = "TRUE";
				}
				else {
					result = "FALSE";
				}
				// vector_result.push_back(result);
			}
			else if (data[i].opt == ">>") {
				res = q1 >> stoi(data[i].num2);
			}
			else if (data[i].opt == "<<") {
				res = q1 << stoi(data[i].num2);
			}
			else if (data[i].opt == "ror") {
				res = q1.ror(stoi(data[i].num2));
			}
			else if (data[i].opt == "rol") {
				res = q1.rol(stoi(data[i].num2));
			}
			else if (data[i].opt == "&") {
				res = q1 & q2;
			}
			else if (data[i].opt == "|") {
				res = q1 | q2;
			}
			else if (data[i].opt == "^") {
				res = q1 ^ q2;
			}

			if (data[i].opt != ">" && data[i].opt != "<" && data[i].opt != ">=" && data[i].opt != "<=" && data[i].opt != "==") {
				switch (stoi(data[i].base1)) {
					case 10: {
						result = res.PrintQInt(res);
					} break;

					case 2: {
						result = res.DecToBin(res);
					} break;

					case 16: {
						result = res.BinToHex(res.DecToBin(res));
					} break;
				}
			}
		}

		// toán tử not :)) 
		else if (data[i].format == 2) {
			QInt q;
			switch (stoi(data[i].base1)) {
				case 10: {
					q.mScanQInt(data[i].num1);
				} break;

				case 2: {
					q.mScanBin(data[i].num1);
				} break;

				case 16: {
					q.mScanHex(data[i].num1);
				} break;
			}

			q = ~q;
			switch (stoi(data[i].base1)) {
				case 10: {
					result = q.PrintQInt(q);
				} break;

				case 2: {
					result = q.DecToBin(q);
				} break;

				case 16: {
					result = q.BinToHex(q.DecToBin(q));
				} break;
			}
		}

		// convert
		else if (data[i].format == 3) {
			QInt q;
			if (data[i].base1 == "10" && data[i].base2 == "2") {
				q.mScanQInt(data[i].num1);
				result = q.DecToBin(q);
			}
			else if (data[i].base1 == "10" && data[i].base2 == "16") {
				q.mScanQInt(data[i].num1);
				result = q.BinToHex(q.DecToBin(q));
			}
			else if (data[i].base1 == "16" && data[i].base2 == "2") {
				q.mScanHex(data[i].num1);
				result = q.DecToBin(q);
			}
			else if (data[i].base1 == "16" && data[i].base2 == "10") {
				q.mScanHex(data[i].num1);
				result = q.PrintQInt(q);
			}
			else if (data[i].base1 == "2" && data[i].base2 == "10") {
				q.mScanBin(data[i].num1);
				result = q.PrintQInt(q);
			}
			else if (data[i].base1 == "2" && data[i].base2 == "16") {
				q.mScanBin(data[i].num1);
				result = q.BinToHex(q.DecToBin(q));
			}
		}

		vector_result.push_back(result);
		// cout << vector_result.size() << " " << vector_result[vector_result.size() - 1] << endl;
	}
	return vector_result;
}


#endif