#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "nlohmann/json.hpp" // Нужна для работы с json, в директории лежат nlohmann/json.hpp и nlohmann/json_fwd.hpp

using json = nlohmann::json;
using namespace std;

struct Value {
    int id;
    string title;
    string value;
    vector<Value> values; // Вложенные значения
};

struct Test {
    int id;
    string title;
    string value;
    vector<Value> values; // Вложенные значения
};

// Функция для чтения значений из файла values.json
map<int, string> readValues(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    json j;
    file >> j;

    map<int, string> valuesMap;
    if (j.contains("values")) {
        for (const auto& item : j["values"]) {
            if (item.contains("id") && item.contains("value") && item["value"].is_string()) {
                int id = item["id"];
                string value = item["value"];
                valuesMap[id] = value;
            }
            else {
                cerr << "Ошибка: значение для ключа не является строкой." << endl;
            }
        }
    }
    else {
        cerr << "Ключ 'values' не найден в JSON." << endl;
    }

    return valuesMap;
}

// Функция для чтения тестов из файла tests.json
vector<Test> readTests(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    json j;
    file >> j;

    vector<Test> tests;
    if (j.contains("tests")) {
        for (const auto& item : j["tests"]) {
            Test test;
            if (item.contains("id")) {
                test.id = item["id"];
            }
            else {
                cerr << "Ошибка: 'id' не найден в тесте." << endl;
                continue; // Пропустить этот тест
            }

            if (item.contains("title")) {
                test.title = item["title"];
            }

            // Обработка вложенных значений
            if (item.contains("values")) {
                for (const auto& subItem : item["values"]) {
                    Value subValue;
                    if (subItem.contains("id")) {
                        subValue.id = subItem["id"];
                    }
                    if (subItem.contains("title")) {
                        subValue.title = subItem["title"];
                    }
                    // Добавьте дополнительные проверки и логику по необходимости

                    test.values.push_back(subValue);
                }
            }

            tests.push_back(test);
        }
    }
    else {
        cerr << "Ключ 'tests' не найден в JSON." << endl;
    }

    return tests;
}

// Основная функция
int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"ru");
    if (argc != 4) {
        cerr << "Передать в: " << argv[0] << " пути к <values.json> <tests.json> <report.json>" << endl;
        return 1;
    }

    try {
        auto valuesMap = readValues(argv[1]);
        auto tests = readTests(argv[2]);

        // Заполнение значений в тестах на основе valuesMap
        for (auto& test : tests) {
            if (valuesMap.find(test.id) != valuesMap.end()) {
                test.value = valuesMap[test.id];
            }
            for (auto& value : test.values) {
                if (valuesMap.find(value.id) != valuesMap.end()) {
                    value.value = valuesMap[value.id];
                }
            }
        }

        // Запись результата в report.json
        json reportJson;
        reportJson["tests"] = json::array();
        for (const auto& test : tests) {
            json testJson;
            testJson["id"] = test.id;
            testJson["title"] = test.title;
            testJson["value"] = test.value;

            // Обработка вложенных значений
            for (const auto& value : test.values) {
                json valueJson;
                valueJson["id"] = value.id;
                valueJson["title"] = value.title;
                valueJson["value"] = value.value;

                testJson["values"].push_back(valueJson);
            }

            reportJson["tests"].push_back(testJson);
        }

        std::ofstream outFile(argv[3]);
        outFile << reportJson.dump(4); // Запись с отступами
        outFile.close();

        cout << "Отчет успешно записан в " << argv[3] << endl;

    }
    catch (const std::exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
