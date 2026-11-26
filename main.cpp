#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
    const int vecSize = 8;
    const int newVecSize = vecSize + 2;

    if (argc != 2) {
        cerr << "Введите: " << argv[0] << " <input файл>\n";
        return 1;
    }

    ifstream input(argv[1]);
    int m;
    if (!(input >> m) || !isspace(input.peek()) || m < 0 || m > vecSize) {
        cerr << "M должно быть целым числом от 0 до " << vecSize << ".\n";
        return 1;
    }

    double grn;
    double vec[vecSize];
    input >> grn;
    for (double& value : vec) {
        if (!isspace(input.peek()) || !(input >> value)) {
            cerr << "Не удалось прочитать GRN и все элементы VEC.\n";
            return 1;
        }
    }

    input >> ws;
    if (!input.eof()) {
        cerr << "После элементов VEC обнаружены лишние данные.\n";
        return 1;
    }

    double newVec[newVecSize] = {};
    double suffixSum = 0;
    for (int i = 0; i < vecSize; ++i) {
        suffixSum += vec[vecSize - 1 - i];
        newVec[i] = suffixSum;
    }

    newVec[vecSize] = grn;
    for (int i = 0; i < m; ++i) {
        newVec[vecSize + 1] += abs(vec[i]);
    }

    cout.precision(numeric_limits<double>::digits10);
    cout << "NEWVEC:";

    double total = 0;
    int minIndex = -1;
    for (int i = 0; i < newVecSize; ++i) {
        const double value = newVec[i];
        cout << ' ' << value;
        total += value;
        if (value > 0 && (minIndex < 0 || value < newVec[minIndex])) {
            minIndex = i;
        }
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
