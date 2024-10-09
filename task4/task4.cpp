#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib> // ��� abs

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");
    //��������� ���������� ������������ ���������� (��� ��������� + ���� � �����)
    if (argc != 2) {
        cerr << "���������� �������� �: " << argv[0] << " ���� � ����� numbers.txt" << "\n";
        return 1;
    }

    ifstream inputNumbers(argv[1]);
    if (!inputNumbers) {
        std::cerr << "�� ������� ������� ����: " << argv[1] << endl;
        return 1;
    }

    vector<int> nums;
    int number;

    // ������ ����� �� �����
    while (inputNumbers >> number) {
        nums.push_back(number);
    }

    inputNumbers.close();

    // ��������� ������ ��� ���������� �������
    sort(nums.begin(), nums.end());

    // ������� �������
    int median = nums[nums.size() / 2];

    // ��������� ����������� ���������� �����
    long long moves = 0; // ���������� long long ��� ��������� ������������
    for (int num : nums) {
        moves += abs(num - median);
    }

    cout << moves << endl;

    return 0;
}