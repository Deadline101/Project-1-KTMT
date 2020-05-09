#include "../pre.h"
#include "sstream"
#include "vector"
#include "iostream"
#include "fstream"

struct Data {
    string base1;
    string base2;
    string num1;
    string num2;
    string oper;
};
Data SaveData[20];
typedef struct Data data;
vector<string> SetDataToVector(string fileName) // đọc file thành từng dòng ra vector 
{
    string s;
    vector<string> res;
    fstream file;
    file.open(fileName,ios::in);
    while(!file.eof())
    {
        getline(file,s);
        res.push_back(s);
    }
    file.close();
    return res;
}

void SetDataToStruct(vector<string> ListData) // Đọc data từ từng dòng vào struct 
{
    Data *SaveData = new Data[ListData.size()];
    stringstream ss;
    string s1;
    // neu có oper thì có num1 và num2 có base 1 base 2 = 0  trừ toán tử ~ chỉ có num1
    // neu k co oper thi có base1 base2 và num1
    string ListOpe[] = {"+","-","*","/",">","<",">=","<=","==","&","|","^","<<",">>","ror","rol"};
    for(int i = 0; i < ListData.size(); i++)
    {   
        ss << ListData[i];
        for(int j = 0;j < 16;j++)
        {
            if(ListData[i].find(ListOpe[j]))
            {
                // set data vào struct
                ss >> SaveData[i].base1;
                ss >> SaveData[i].num1;
                ss >> SaveData[i].oper;
                ss >> SaveData[i].num2;
                SaveData[i].base2="";
                return;
            }
        }
        if(ListData[i].find('~') == 0)
        {
            // set data
            ss >> SaveData[i].base1;
            ss >> SaveData[i].oper;
            ss >> SaveData[i].num1;
            SaveData[i].base2="";
            SaveData[i].num2="";
        }
        else
        {
            // set data
            ss >> SaveData[i].base1;
            ss >> SaveData[i].base2;
            ss >> SaveData[i].num1;
            SaveData[i].oper="";
            SaveData[i].num2="";
        }
    }
}
