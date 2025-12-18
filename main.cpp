#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

struct Bank {
    string name;
    double buy;
    double sell;
    string address;
};

void printBelarusbank(const vector<Bank>& banks) {
    for (size_t i = 0; i < banks.size(); i++) {
        if (banks[i].name == "Беларусбанк") {
            cout << banks[i].name << " | Покупка: " << banks[i].buy
                 << " | Продажа: " << banks[i].sell
                 << " | Адрес: " << banks[i].address << endl;
        }
    }
}

void printLowSell(const vector<Bank>& banks) {
    for (size_t i = 0; i < banks.size(); i++) {
        if (banks[i].sell < 2.5) {
            cout << banks[i].name << " | Покупка: " << banks[i].buy
                 << " | Продажа: " << banks[i].sell
                 << " | Адрес: " << banks[i].address << endl;
        }
    }
}

void bubbleSort(vector<Bank>& banks) {
    for (size_t i = 0; i < banks.size(); i++) {
        for (size_t j = 0; j < banks.size() - i - 1; j++) {
            double diff1 = banks[j].sell - banks[j].buy;
            double diff2 = banks[j+1].sell - banks[j+1].buy;
            if (diff1 < diff2) {
                swap(banks[j], banks[j+1]);
            }
        }
    }
}

bool cmpBank(const Bank& a, const Bank& b) {
    if (a.name == b.name) return a.address < b.address;
    return a.name < b.name;
}

void mergeSort(vector<Bank>& banks) {
    sort(banks.begin(), banks.end(), cmpBank);
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Bank> banks;
    ifstream fin("input.txt");

    while (!fin.eof()) {
        Bank b;
        fin >> b.name >> b.buy >> b.sell;
        getline(fin, b.address);
        if (!b.name.empty()) {
            banks.push_back(b);
        }
    }
    fin.close();

    cout << "Отделения Беларусбанка:\n";
    printBelarusbank(banks);

    cout << "\nБанки с продажей < 2.5:\n";
    printLowSell(banks);

    cout << "\nСортировка пузырьком по разнице (продажа - покупка):\n";
    bubbleSort(banks);
    for (size_t i = 0; i < banks.size(); i++) {
        cout << banks[i].name << " | Разница: " << banks[i].sell - banks[i].buy << endl;
    }

    cout << "\nСортировка слиянием по названию и адресу:\n";
    mergeSort(banks);
    for (size_t i = 0; i < banks.size(); i++) {
        cout << banks[i].name << " | " << banks[i].address << endl;
    }

    return 0;
}

