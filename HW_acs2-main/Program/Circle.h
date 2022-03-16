#ifndef ALAN_CIRCLE_H
#define ALAN_CIRCLE_H

#include "Figure.h"
#include "Point.h"
#include <fstream>

class Circle : public Figure {
private:
    int r;
    Point center;
public:
    Circle(Point center_point, int radius, Colors figure_color) : Figure(figure_color), r(radius),
                                                                                   center(center_point) {}

    Circle(std::ifstream &fin, Colors clr);

    std::ofstream &output(std::ofstream &out) override;

    double square() override;
};


#endif //ALAN_CIRCLE_H
