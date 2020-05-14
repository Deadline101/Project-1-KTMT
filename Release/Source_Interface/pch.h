#pragma once

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "string"
#include "math.h"
#include <vector>
#include <fstream>
#include <sstream>

enum nERROR {
    OUT_OF_RANGE,
    WRONG_FORMAT,
    DIVIDE_BY_ZERO
}; 

//void meo(nERROR e);

inline void catchError(nERROR e) {
    switch (e) {
    case OUT_OF_RANGE: {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Out of range error!\nPlease re-enter the number!", //Nội dung thông báo
            (LPCWSTR)L"ERROR!", //Tên Message Box Error
            MB_ICONERROR | MB_OK //Icon warning và 1 nút OK
        );
    } break;

    case WRONG_FORMAT: {
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Wrong format error!\nPlease re-enter the number!", //Nội dung thông báo
            (LPCWSTR)L"ERROR!", //Tên Message Box Error
            MB_ICONERROR | MB_OK //Icon warning và 1 nút OK
        );
    } break;

    case DIVIDE_BY_ZERO: {
        //int msgboxID = MessageBox(
        //    NULL,
        //    (LPCWSTR)L"Divide by Zero error!\nPlease re-enter the number!", //Nội dung thông báo
        //    (LPCWSTR)L"ERROR!", //Tên Message Box Error
        //    MB_ICONERROR | MB_OK //Icon warning và 1 nút OK
        //);
    } break;
    }
}

