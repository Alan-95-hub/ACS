#ifndef ALAN_RECTANGLE_H
#define ALAN_RECTANGLE_H


#include "Figure.h"
#include "Point.h"

class Rectangle : public Figure {
private:
    Point left_up, right_down;
public:
    Rectangle(int l_up_x, int l_up_y, int r_down_x, int r_down_y, Colors color) :
            Figure(color), left_up(l_up_x, l_up_y), right_down(r_down_x, r_down_y) {}

    Rectangle(std::ifstream &fin, Colors clr);

    ~Rectangle() override = default;

    std::ofstream &output(std::ofstream &out) override;

    double square() override;
};


#endif //ALAN_RECTANGLE_H
