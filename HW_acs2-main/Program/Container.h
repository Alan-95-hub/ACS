#ifndef ALAN_CONTAINER_H
#define ALAN_CONTAINER_H


#define MAX_SIZE 10000

#include "Figure.h"
#include <fstream>
#include <vector>
#include <memory>


class Container {
private:
    std::vector<std::shared_ptr<Figure>> array;
public:
    Container() : array(std::vector<std::shared_ptr<Figure>>(MAX_SIZE, std::shared_ptr<Figure>())) {}

    explicit Container(std::ifstream &fin);

    ~Container() = default;

    std::shared_ptr<Figure> &operator[](int i);

    friend std::ofstream &operator<<(std::ofstream &out, const Container &container);

    void shaker_sort();
};


#endif //ALAN_CONTAINER_H
