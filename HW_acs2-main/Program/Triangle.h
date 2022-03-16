#ifndef ALAN_TRIANGLE_H
#define ALAN_TRIANGLE_H

#include "Figure.h"
#include "Point.h"

class Triangle : public Figure {
private:
    Point first, second, third;
public:
    Triangle(int first_x, int first_y, int second_x, int second_y, int third_x, int third_y, Colors color) :
            Figure(color), first(first_x, first_y), second(second_x, second_y), third(third_x, third_y) {}

    Triangle(std::ifstream &fin, Colors clr);

    ~Triangle() override = default;

    std::ofstream &output(std::ofstream &out) override;

    double square() override;
};


#endif //ALAN_TRIANGLE_H
