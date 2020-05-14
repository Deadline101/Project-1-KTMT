#include "pre.h"
#include "HandleFileQInt.h"
#include "HandleFileQFloat.h"

int main(int argc, char ** argv)
{
	if (strcmp(argv[3], "1") == 0) {
		vector<string> filedataInt = SetDataToVectorString(argv[1]);

		vector<Data> dataInt = SetDataToStruct(filedataInt);

		vector<string> dataForFileInt = getOutput(dataInt);

		fstream file;
		file.open(argv[2], ios::out);
		if (file) {
			for (int i = 0; i < dataForFileInt.size(); ++i) {
				//cout << i + 1 << " " << dataForFileInt[i] << endl;
				file << dataForFileInt[i];
				if (i == dataForFileInt.size() - 1) {
					continue;
				}
				file << endl;
			}
		}
	}
	else if (strcmp(argv[3], "2") == 0) {
		vector<string> filedataFloat = loadDataFromFileFloat(argv[1]);

		vector<DataFloat> dataFloat = loadDataFromArrayStringFloat(filedataFloat);

		vector<string> dataForFileFloat = setDataToVectorStringFloat(dataFloat);

		fstream file;
		file.open(argv[2], ios::out);
		if (file) {
			for (int i = 0; i < dataForFileFloat.size(); ++i) {
				//cout << i + 1 << " " << dataForFileFloat[i] << endl;
				file << dataForFileFloat[i];
				if (i == dataForFileFloat.size() - 1) {
					continue;
				}
				file << endl;
			}
		}
	}
	
	//Project1.exe QFloat_input.txt QFloat_output.txt 2
	//Project1.exe QInt_input.txt QInt_output.txt 1
	return 1;
}
