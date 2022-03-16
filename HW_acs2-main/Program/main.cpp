#include <iostream>
#include <cstring>
#include "Triangle.h"
#include "Container.h"

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 4) {
        throw std::runtime_error("Invalid amount of arguments given: " + std::to_string(argc) + ". 3 needed");
    }
    std::ifstream fin(argv[1]); // Первый аргумент - входной файл
    if (!fin) {
        std::cerr << "Unable to open this file. Make sure the path is correct";
        return 1;
    }
    std::ofstream out(argv[2]); // Второй аргумент - выходной
    if (!out) {
        std::cerr << "Unable to open/create this file";
    }
    Container a(fin);
    if (argc == 4) {
        if (strcmp(argv[3], "-s") == 0) {
            a.shaker_sort();
        } else {
            std::cerr << "Extra argument is invalid. No sorting will be done";
        }
    }
    out << a;
    fin.close();
    out.close();
    return 0;
}
