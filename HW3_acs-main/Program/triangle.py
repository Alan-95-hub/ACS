import math

from shape import *
from point import *


# Класс треугольника (наследуется от Shape).
class Triangle(Shape):
    def __init__(self):
        self.a = Point()
        self.b = Point()
        self.c = Point()

    # Создание треугольника по данным из общего массива.
    def ReadStrArray(self, strArray, i):
        # Проверка на то,
        # что в массиве будет достаточно элементов уже производится в методе ReadStrArray.
        self.a.x = int(strArray[i])
        self.a.y = int(strArray[i + 1])
        self.b.x = int(strArray[i + 2])
        self.b.y = int(strArray[i + 3])
        self.c.x = int(strArray[i + 4])
        self.c.y = int(strArray[i + 5])
        i += 6
        return i

    # Вывод данных о треугольнике в консоль.
    def Print(self):
        print(f"It is a Triangle:\n"
              f"\tcolor - {self.GetColorString()}\n"
              f"\ta = {self.a.x} {self.a.y}\n"
              f"\tb = {self.b.x} {self.b.y}\n"
              f"\tc = {self.c.x} {self.c.y}\n"
              f"\tSquare = {self.Square()}")
        pass

    # Вывод данных о треугольнике в файл.
    def Write(self, ostream):
        ostream.write(f"It is a Triangle:\n"
                      f"\tcolor - {self.GetColorString()}\n"
                      f"\ta = {self.a.x} {self.a.y}\n"
                      f"\tb = {self.b.x} {self.b.y}\n"
                      f"\tc = {self.c.x} {self.c.y}\n"
                      f"\tSquare = {self.Square()}")
        pass

    def Square(self):
        p = float(math.ceil(math.pow(self.a.x - self.b.x, 2) + math.pow(self.a.y - self.b.y, 2)) +
                  math.ceil(math.pow(self.c.x - self.b.x, 2) + math.pow(self.c.y - self.b.y, 2)) +
                  math.ceil(math.pow(self.a.x - self.c.x, 2) + math.pow(self.a.y - self.c.y, 2)))
        a = math.ceil(math.pow(self.a.x - self.b.x, 2) + math.pow(self.a.y - self.b.y, 2))
        b = math.ceil(math.pow(self.c.x - self.b.x, 2) + math.pow(self.c.y - self.b.y, 2))
        c = math.ceil(math.pow(self.a.x - self.c.x, 2) + math.pow(self.a.y - self.c.y, 2))
        m1 = self.a.x - self.c.x
        m2 = self.a.y - self.c.y
        m3 = self.b.x - self.c.x
        m4 = self.b.y - self.c.y
        square = abs(m1 * m4 - m2 * m3) / 2
        return square
