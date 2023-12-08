#include "DATA_generator.h"
#include "backend.h"
std::vector<double> generate_data_point(double W) {
    std::vector<double> vec;
    double time = GetCurrentUTCTimeSeconds();
    vec.push_back(time);
    vec.push_back(sin(W * time));
    return vec;
}

