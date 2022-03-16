#include "Triangle.h"
#include <cmath>

double Triangle::square() {
    return double(abs(
            (second.x() - first.x()) * (third.y() - first.y()) - (third.x() - first.x()) * (second.y() - first.y())
    )) / 2;
}

Triangle::Triangle(std::ifstream &fin, Colors clr) : Figure(clr) {
    fin >> first >> second >> third;
    if (fin.fail()) {
        throw std::invalid_argument("Stream ended unexpectedly");
    }
}

std::ofstream &Triangle::output(std::ofstream &out) {
    out << "TRIANGLE:\n\tpoint 1: ";
    out << first << "\n\tpoint 2: ";
    out << second << "\n\tpoint 3: ";
    out << third;
    return out;
}
