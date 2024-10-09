#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib> // для abs

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru");
    //Проверяем количество передаваемых аргументов (имя программы + путь к файлу)
    if (argc != 2) {
        cerr << "Необходимо передать в: " << argv[0] << " путь к файлу numbers.txt" << "\n";
        return 1;
    }

    ifstream inputNumbers(argv[1]);
    if (!inputNumbers) {
        std::cerr << "Не удалось открыть файл: " << argv[1] << endl;
        return 1;
    }

    vector<int> nums;
    int number;

    // Чтение чисел из файла
    while (inputNumbers >> number) {
        nums.push_back(number);
    }

    inputNumbers.close();

    // Сортируем массив для нахождения медианы
    sort(nums.begin(), nums.end());

    // Находим медиану
    int median = nums[nums.size() / 2];

    // Вычисляем минимальное количество ходов
    long long moves = 0; // Используем long long для избежания переполнения
    for (int num : nums) {
        moves += abs(num - median);
    }

    cout << moves << endl;

    return 0;
}