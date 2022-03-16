#ifndef ALAN_FIGURE_H
#define ALAN_FIGURE_H

#include <fstream>

enum class Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    DARK_BLUE,
    PURPLE
};


class Figure {
protected:
    Colors color;
public:
    explicit Figure(Colors figure_color) : color(figure_color) {}

    virtual ~Figure() = default;

    virtual double square() = 0;

    [[nodiscard]] Colors get_color();

    virtual std::ofstream &output(std::ofstream &out) = 0;
};


#endif //ALAN_FIGURE_H
