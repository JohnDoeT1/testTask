#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "nlohmann/json.hpp" // ����� ��� ������ � json, � ���������� ����� nlohmann/json.hpp � nlohmann/json_fwd.hpp

using json = nlohmann::json;
using namespace std;

struct Value {
    int id;
    string title;
    string value;
    vector<Value> values; // ��������� ��������
};

struct Test {
    int id;
    string title;
    string value;
    vector<Value> values; // ��������� ��������
};

// ������� ��� ������ �������� �� ����� values.json
map<int, string> readValues(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("�� ������� ������� ����: " + filename);
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
                cerr << "������: �������� ��� ����� �� �������� �������." << endl;
            }
        }
    }
    else {
        cerr << "���� 'values' �� ������ � JSON." << endl;
    }

    return valuesMap;
}

// ������� ��� ������ ������ �� ����� tests.json
vector<Test> readTests(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("�� ������� ������� ����: " + filename);
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
                cerr << "������: 'id' �� ������ � �����." << endl;
                continue; // ���������� ���� ����
            }

            if (item.contains("title")) {
                test.title = item["title"];
            }

            // ��������� ��������� ��������
            if (item.contains("values")) {
                for (const auto& subItem : item["values"]) {
                    Value subValue;
                    if (subItem.contains("id")) {
                        subValue.id = subItem["id"];
                    }
                    if (subItem.contains("title")) {
                        subValue.title = subItem["title"];
                    }
                    // �������� �������������� �������� � ������ �� �������������

                    test.values.push_back(subValue);
                }
            }

            tests.push_back(test);
        }
    }
    else {
        cerr << "���� 'tests' �� ������ � JSON." << endl;
    }

    return tests;
}

// �������� �������
int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"ru");
    if (argc != 4) {
        cerr << "�������� �: " << argv[0] << " ���� � <values.json> <tests.json> <report.json>" << endl;
        return 1;
    }

    try {
        auto valuesMap = readValues(argv[1]);
        auto tests = readTests(argv[2]);

        // ���������� �������� � ������ �� ������ valuesMap
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

        // ������ ���������� � report.json
        json reportJson;
        reportJson["tests"] = json::array();
        for (const auto& test : tests) {
            json testJson;
            testJson["id"] = test.id;
            testJson["title"] = test.title;
            testJson["value"] = test.value;

            // ��������� ��������� ��������
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
        outFile << reportJson.dump(4); // ������ � ���������
        outFile.close();

        cout << "����� ������� ������� � " << argv[3] << endl;

    }
    catch (const std::exception& e) {
        cerr << "������: " << e.what() << endl;
        return 1;
    }

    return 0;
}
