#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc,char* argv[]) {
	setlocale(LC_ALL, "ru");
	//ѕровер€ем количество передаваемых аргументов (им€ программы + 2 числа)
	if (argc != 3) {
		cerr << "Ќеобходимо передать в: " << argv[0] << " число n - длина кругового массива и m - интервал длины." << "\n";
		return 1;
	}

	//преобразуем аргументы из строк в целые числа
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		arr[i] = i + 1; //заполнение массива значени€ми от 1 до n
	}

	int current = 0;
	//¬ыводим путь
	do {
		cout << arr[current] << " ";
		current = (current + m - 1) % n;
	} while (current != 0);

	return 0;
}