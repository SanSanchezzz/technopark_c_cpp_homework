#ifndef TEST_H
#define TEST_H

extern "C" {
    #include "../source/types.h"
    #include "../source/read_data.h"
    #include "../source/multy_proc.h"
    #include "../source/single_proc.h"
    #include "../source/single_proc.h"
    #include <sys/sysinfo.h>
}

#include <iostream>
#include <chrono>
#include <string>

#define ERROR 1

using namespace std;
using namespace std::chrono;

class Timer {
public:
    explicit Timer(): start(steady_clock::now()) {}

    ~Timer() {
        time_point<steady_clock> finish = steady_clock::now();
        high_resolution_clock::duration dur = finish - start;
        cout << duration_cast<milliseconds>(dur).count()
             << " ms" << endl;
    }
private:
    steady_clock::time_point start;
};


#endif //TEST_H
