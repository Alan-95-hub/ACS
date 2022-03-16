#include "Point.h"

int Point::x() const {
    return x_coord;
}

int Point::y() const {
    return y_coord;
}

std::ifstream &operator>>(std::ifstream &fin, Point &point) {
    fin >> point.x_coord >> point.y_coord;
    return fin;
}

void Point::set_x(int val) {
    x_coord = val;
}

void Point::set_y(int val) {
    y_coord = val;
}

std::ofstream &operator<<(std::ofstream &out, const Point &point) {
    out << point.x_coord << ' ' << point.y_coord;
    return out;
}
