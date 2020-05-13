#pragma once
#include "QFloat.h"

vector<string> loadDataFromFileFloat(string filename)
{
	fstream file;
	file.open(filename, ios::in);
	vector<string> resault;
	if (file) {
		while (!file.eof()) {
			string str;
			getline(file, str);
			resault.push_back(str);
		}
	}
	file.close();
	return resault;
}

struct DataFloat
{
	string base1, base2;
	string num;
};

vector<DataFloat> loadDataFromArrayStringFloat(vector<string> str)
{
	vector<DataFloat> resault;
	for (int i = 0; i < str.size(); ++i) {
		DataFloat data;
		stringstream ss(str[i]);
		ss >> data.base1 >> data.base2 >> data.num;
		resault.push_back(data);
	}
	return resault;
}

vector<string> setDataToVectorStringFloat(vector<DataFloat> vData)
{
	vector<string> resault;
	for (int i = 0; i < vData.size(); ++i) {
		string str;
		if (vData[i].base1 == "10" && vData[i].base2 == "2") {
			Qfloat qfloat(vData[i].num);
			str = Qfloat::DecToBin(qfloat);
		}
		else if (vData[i].base1 == "2" && vData[i].base2 == "10") {
			str = Qfloat::BinToDec(vData[i].num).Print(0);

		}
		resault.push_back(str);
	}
	return resault;
}