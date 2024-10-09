#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath> //Для sqrt
#include <string>
#include <vector>

using namespace std;

class Point {
private:
	double x; //Координата x
	double y; //Координата y

public:
	//Конструктор по умолчанию
	Point() : x(0), y(0) {}

	//Конструктор с параметрами
	Point(double x, double y) : x(x), y(y) {}

	//Метод для получения координаты x
	double getX() const {
		return x;
	}

	//Метод для получения координаты y
	double getY() const {
		return y;
	}

	//Метод для установки координаты x
	double setX(double x) {
		this->x = x;
	}

	//Метод для установки координаты y
	double setY(double y) {
		this->y = y;
	}

};

int chekPointPosition(const Point& oCircle,double rCircle, const Point& dot) {
	double distanceSquared = (dot.getX() - oCircle.getX()) * (dot.getX() - oCircle.getX()) +
		(dot.getY() - oCircle.getY()) * (dot.getY() - oCircle.getY());
	double radiusSquared = rCircle * rCircle;

	if (distanceSquared < radiusSquared) {
		return 1; //Точка внутри окружности
	}
	else if (distanceSquared == radiusSquared) {
		return 0; //Точка на окружности
	}
	else {
		return 2; //Точка снаружи окружности
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	//Проверяем количество передаваемых аргументов (имя программы + 2 пути)
	if (argc != 3) {
		cerr << "Необходимо передать в: " << argv[0] << " путь к файлу circle.txt и путь к файлу dot.txt" << "\n";
		return 1;
	}

	//Принимаем параметры пути к файлам дано
	string circlePath = argv[1];
	string dotPath = argv[2];

	//Проверяем открытие
	ifstream inpitCircle(circlePath);
	if (!inpitCircle) {
		cerr << "не удалось открыть файл" << "\n";
		return 1; //Завершаем с ошибкой если не удалось открыть файл
	}

	int rCircle;
	double oCirclex, oCircley;
	//Записываем вводные круга
	inpitCircle >> oCirclex >> oCircley;
	Point oCircle(oCirclex, oCircley);
	
	inpitCircle >> rCircle;

	inpitCircle.close();

	vector<Point> dots; //Вектор точек
	double x, y;

	//Проверяем открытие
	ifstream inpitDots(dotPath);
	if (!inpitDots) {
		cerr << "не удалось открыть файл" << "\n";
		return 1; //Завершаем с ошибкой если не удалось открыть файл
	}

	while (inpitDots >> x >> y) {
		dots.emplace_back(x, y); //Создаём объект point, добавляем его в вектор
	}

	inpitDots.close();

	for (auto el : dots) {
		cout << chekPointPosition(oCircle, rCircle, el) << "\n";
	}

	return 0;
}