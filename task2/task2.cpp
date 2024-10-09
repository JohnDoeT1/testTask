#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath> //��� sqrt
#include <string>
#include <vector>

using namespace std;

class Point {
private:
	double x; //���������� x
	double y; //���������� y

public:
	//����������� �� ���������
	Point() : x(0), y(0) {}

	//����������� � �����������
	Point(double x, double y) : x(x), y(y) {}

	//����� ��� ��������� ���������� x
	double getX() const {
		return x;
	}

	//����� ��� ��������� ���������� y
	double getY() const {
		return y;
	}

	//����� ��� ��������� ���������� x
	double setX(double x) {
		this->x = x;
	}

	//����� ��� ��������� ���������� y
	double setY(double y) {
		this->y = y;
	}

};

int chekPointPosition(const Point& oCircle,double rCircle, const Point& dot) {
	double distanceSquared = (dot.getX() - oCircle.getX()) * (dot.getX() - oCircle.getX()) +
		(dot.getY() - oCircle.getY()) * (dot.getY() - oCircle.getY());
	double radiusSquared = rCircle * rCircle;

	if (distanceSquared < radiusSquared) {
		return 1; //����� ������ ����������
	}
	else if (distanceSquared == radiusSquared) {
		return 0; //����� �� ����������
	}
	else {
		return 2; //����� ������� ����������
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	//��������� ���������� ������������ ���������� (��� ��������� + 2 ����)
	if (argc != 3) {
		cerr << "���������� �������� �: " << argv[0] << " ���� � ����� circle.txt � ���� � ����� dot.txt" << "\n";
		return 1;
	}

	//��������� ��������� ���� � ������ ����
	string circlePath = argv[1];
	string dotPath = argv[2];

	//��������� ��������
	ifstream inpitCircle(circlePath);
	if (!inpitCircle) {
		cerr << "�� ������� ������� ����" << "\n";
		return 1; //��������� � ������� ���� �� ������� ������� ����
	}

	int rCircle;
	double oCirclex, oCircley;
	//���������� ������� �����
	inpitCircle >> oCirclex >> oCircley;
	Point oCircle(oCirclex, oCircley);
	
	inpitCircle >> rCircle;

	inpitCircle.close();

	vector<Point> dots; //������ �����
	double x, y;

	//��������� ��������
	ifstream inpitDots(dotPath);
	if (!inpitDots) {
		cerr << "�� ������� ������� ����" << "\n";
		return 1; //��������� � ������� ���� �� ������� ������� ����
	}

	while (inpitDots >> x >> y) {
		dots.emplace_back(x, y); //������ ������ point, ��������� ��� � ������
	}

	inpitDots.close();

	for (auto el : dots) {
		cout << chekPointPosition(oCircle, rCircle, el) << "\n";
	}

	return 0;
}