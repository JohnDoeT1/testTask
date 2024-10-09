#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc,char* argv[]) {
	setlocale(LC_ALL, "ru");
	//��������� ���������� ������������ ���������� (��� ��������� + 2 �����)
	if (argc != 3) {
		cerr << "���������� �������� �: " << argv[0] << " ����� n - ����� ��������� ������� � m - �������� �����." << "\n";
		return 1;
	}

	//����������� ��������� �� ����� � ����� �����
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		arr[i] = i + 1; //���������� ������� ���������� �� 1 �� n
	}

	int current = 0;
	//������� ����
	do {
		cout << arr[current] << " ";
		current = (current + m - 1) % n;
	} while (current != 0);

	return 0;
}