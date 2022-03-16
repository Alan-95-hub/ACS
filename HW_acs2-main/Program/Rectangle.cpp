#include "Rectangle.h"

double Rectangle::square() {
    return abs(right_down.x() - left_up.x()) * abs(left_up.y() - right_down.y());
}

Rectangle::Rectangle(std::ifstream &fin, Colors clr) : Figure(clr) {
    fin >> left_up >> right_down;
    if (fin.fail()) {
        throw std::invalid_argument("Stream ended unexpectedly");
    }
}

std::ofstream &Rectangle::output(std::ofstream &out) {
    out << "RECTANGLE:\n\tTop left point: ";
    out << left_up << "\n\tBottom right point: ";
    out << right_down;
    return out;
}
