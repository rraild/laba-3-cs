#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    constexpr int vecSize = 8;
    constexpr int newVecSize = vecSize + 2;

    if (argc != 2) {
        cerr << "Введите: " << argv[0] << " <input файл>\n";
        return 1;
    }

    ifstream input(argv[1]);
    int m;
    double grn;
    if (!(input >> m) || m < 0 || m > vecSize ||
        !isspace(input.peek()) || !(input >> grn)) {
        cerr << "Не удалось прочитать M и GRN. M должно быть целым от 0 до "
             << vecSize << ".\n";
        return 1;
    }

    double vec[vecSize];
    for (double& value : vec) {
        if (!isspace(input.peek()) || !(input >> value)) {
            cerr << "Не удалось прочитать все элементы VEC.\n";
            return 1;
        }
    }

    input >> ws;
    if (!input.eof()) {
        cerr << "После элементов VEC обнаружены лишние данные.\n";
        return 1;
    }

    double newVec[newVecSize];
    double suffixSum = 0;
    for (int i = 0; i < vecSize; ++i) {
        suffixSum += vec[vecSize - 1 - i];
        newVec[i] = suffixSum;
    }

    newVec[vecSize] = grn;
    newVec[vecSize + 1] = 0;
    for (int i = 0; i < m; ++i) {
        newVec[vecSize + 1] += abs(vec[i]);
    }

    double total = 0;
    int minIndex = -1;
    for (int i = 0; i < newVecSize; ++i) {
        const double value = newVec[i];
        total += value;
        if (value > 0 && (minIndex < 0 || value < newVec[minIndex])) {
            minIndex = i;
        }
    }

    cout.precision(numeric_limits<double>::digits10);
    cout << "NEWVEC:";
    for (double value : newVec) {
        cout << ' ' << value;
    }
    cout << "\nСумма: " << total << '\n';

    if (minIndex >= 0) {
        cout << "Наименьший положительный элемент: NEWVEC["
             << minIndex << "] = " << newVec[minIndex] << '\n';
    } else {
        cout << "Положительных элементов нет.\n";
    }

    return 0;
}
