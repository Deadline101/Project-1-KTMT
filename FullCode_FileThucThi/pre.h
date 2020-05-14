#ifndef PRE_H_
#define PRE_H_

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

#include "string"
#include "math.h"
#include <vector>
#include <fstream>
#include <sstream>

enum ERROR {
    OUT_OF_RANGE,
    WRONG_FORMAT,
    DIVIDE_BY_ZERO
};

void catchError(ERROR e) {
    switch (e) {
        case OUT_OF_RANGE: {
            cout << "Data out of range\n";
        } break;

        case WRONG_FORMAT: {
            cout << "Wrong format\n";
        } break;

        case DIVIDE_BY_ZERO: {
            cout << "Divide by zero\n";
        } break;
    }
}

#endif