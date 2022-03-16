#ifndef ALAN_POINT_H
#define ALAN_POINT_H


#include <fstream>

class Point {
private:
    int x_coord, y_coord;
public:
    Point() : x_coord(0), y_coord(0) {}

    Point(int x, int y) : x_coord(x), y_coord(y) {}

    ~Point() = default;

    [[nodiscard]] int x() const;

    [[nodiscard]] int y() const;

    void set_x(int val);

    void set_y(int val);

    friend std::ifstream &operator>>(std::ifstream &fin, Point &point);

    friend std::ofstream &operator<<(std::ofstream &out, const Point &point);
};


#endif //ALAN_POINT_H
