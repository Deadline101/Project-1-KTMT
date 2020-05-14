#pragma once
#include "QFloat.h"

vector<string> loadDataFromFileFloat(string filename)
{
	fstream file;
	file.open(filename, ios::in);
	vector<string> result;
	if (file) {
		while (!file.eof()) {
			string str;
			getline(file, str);
			result.push_back(str);
		}
	}
	file.close();
	return result;
}

struct DataFloat
{
	string base1, base2;
	string num;
};

vector<DataFloat> loadDataFromArrayStringFloat(vector<string> str)
{
	vector<DataFloat> result;
	for (int i = 0; i < str.size(); ++i) {
		DataFloat data;
		stringstream ss(str[i]);
		ss >> data.base1 >> data.base2 >> data.num;
		result.push_back(data);
	}
	return result;
}

vector<string> setDataToVectorStringFloat(vector<DataFloat> vData)
{
	vector<string> result;
	for (int i = 0; i < vData.size(); ++i) {
		string str;
		if (vData[i].base1 == "10" && vData[i].base2 == "2") {
			Qfloat qfloat(vData[i].num);
			str = Qfloat::DecToBin(qfloat);
		}
		else if (vData[i].base1 == "2" && vData[i].base2 == "10") {
			str = Qfloat::BinToDec(vData[i].num).Print(0);

		}
		result.push_back(str);
	}
	return result;
}