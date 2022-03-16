#include "Circle.h"
#include <cmath>

double Circle::square() {
    return acos(-1) * r * r;
}

Circle::Circle(std::ifstream &fin, Colors clr) : Figure(clr) {
    fin >> center >> r;
    if (fin.fail()) {
        throw std::invalid_argument("Stream ended unexpectedly");
    }
}

std::ofstream &Circle::output(std::ofstream &out) {
    out << "CIRCLE:\n\tCenter point: ";
    out << center << "\n\tRadius: " << r;
    return out;
}
