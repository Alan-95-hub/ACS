#include "Container.h"
#include <stdexcept>
#include <string>
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"


#define HUGE_AMOUNT 500

std::ofstream &operator<<(std::ofstream &out, const Container &container) {
    out << "Container contains " << container.array.size() << " elements.\n";
    int number = 1;
    for (const auto &elem: container.array) {
        out << number << ". ";
        elem->output(out) << "\n\tColor: ";
        switch (elem->get_color()) {
            case Colors::RED:
                out << "RED";
                break;
            case Colors::ORANGE:
                out << "ORANGE";
                break;
            case Colors::YELLOW:
                out << "YELLOW";
                break;
            case Colors::GREEN:
                out << "GREEN";
                break;
            case Colors::BLUE:
                out << "BLUE";
                break;
            case Colors::DARK_BLUE:
                out << "DARK_BLUE";
                break;
            case Colors::PURPLE:
                out << "PURPLE";
                break;
            default:
                throw std::invalid_argument("Color is incorrect");
        }
        out << "\n\tSquare = " << elem->square() << '\n';
        number++;
    }
    return out;
}

Container::Container(std::ifstream &fin) {
    std::string figure_type;
    int number_of_elements, color;
    fin >> number_of_elements;
    if (number_of_elements > HUGE_AMOUNT) {
        //random generation
        srand(time(NULL));

        int x, y, r;
        for (int i = 0; i < number_of_elements; i++) {
            color = random() % 7;
            switch (random() % 3 + 1) {
                case 1:
                    array.push_back(std::make_shared<Circle>(
                            Point(random() % 1000, random() % 1000),
                            random() % 100, static_cast<Colors>(color)));
                    break;
                case 2:
                    array.push_back(std::make_shared<Rectangle>(random() % 1000, random() % 1000, random() % 1000,
                                                                random() % 1000, static_cast<Colors>(color)));
                    break;
                case 3:
                    array.push_back(std::make_shared<Triangle>(random() % 1000, random() % 1000, random() % 1000,
                                                               random() % 1000, random() % 1000, random() % 1000,
                                                               static_cast<Colors>(color)));
                    break;
            }
        }
    } else {
        for (int i = 0; i < number_of_elements; i++) {
            fin >> figure_type >> color;
            if (figure_type == "CIRCLE") {
                array.push_back(std::make_shared<Circle>(fin, static_cast<Colors>(color)));
            } else if (figure_type == "RECTANGLE") {
                array.push_back(std::make_shared<Rectangle>(fin, static_cast<Colors>(color)));
            } else if (figure_type == "TRIANGLE") {
                array.push_back(std::make_shared<Triangle>(fin, static_cast<Colors>(color)));
            }
        }
    }
}

std::shared_ptr<Figure> &Container::operator[](int i) {
    return array[i];
}

void Container::shaker_sort() {
    int left = 0, right = array.size() - 1; // левая и правая границы сортируемой области массива
    int flag = 1;  // флаг наличия перемещений
    // Выполнение цикла пока левая граница не сомкнётся с правой
    // и пока в массиве имеются перемещения
    while ((left < right) && flag > 0) {
        flag = 0;
        for (int i = left; i < right; i++)  //двигаемся слева направо
        {
            if (array[i]->square() > array[i + 1]->square()) // если следующий элемент меньше текущего,
            {             // меняем их местами
                std::swap(array[i], array[i + 1]);
                flag = 1;// перемещения в этом цикле были
            }
        }
        right--; // сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
            if (array[i - 1]->square() > array[i]->square()) // если предыдущий элемент больше текущего,
            {            // меняем их местами
                std::swap(array[i - 1], array[i]);
                flag = 1;// перемещения в этом цикле были
            }
        }
        left++; // сдвигаем левую границу на следующий элемент
    }
}
