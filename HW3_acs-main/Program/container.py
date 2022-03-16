from extender import *


class Container:
    def __init__(self):
        self.store = []

    # Вывод информации о содержимом контейнера в консоль.
    def Print(self):
        print("Container is store", len(self.store), "shapes:")
        for shape in self.store:
            shape.Print()
        print("Summa of Square  = ", self.Square())
        pass

    # Вывод информации о содержимом контейнера в файл.
    def Write(self, ostream):
        ostream.write("Container is store {} shapes:\n".format(len(self.store)))
        for shape in self.store:
            shape.Write(ostream)
            ostream.write("\n")
        ostream.write("Summa of Square  = {}\n".format(self.Square()))
        pass

    # Подсчет суммы пермитрев всех фигур.
    def Square(self):
        square = 0.0
        for shape in self.store:
            square += shape.Square()
        return square

    def GetAverageSquare(self):
        return self.Square() / len(self.store)
