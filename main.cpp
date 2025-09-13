#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cstdio>
using namespace std;

#include "Headers/Rundom.h"
using namespace Pseudorandom_numbers;

int main() {
    const int n = 20000;        // Кол-во случайных чисел
    const int m = 31;           // Кол-во разбиений (20-50)
    vector <int> split (m, 0);  // Сумма чисел по секторам

    //! Начальное условие
    Rundom::set_a(2503);
    Rundom::set_b(2509);
    Rundom::set_m(10000000);
    
    //> Генерация ряда случайных чисел
    FILE* file_nombers = fopen("Output/numbers.scv", "w");
    if (!file_nombers) {
        cout << "File opening error!" << endl;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        long long rund = Rundom::creat_rundom_number(); //? start: 798451
        double u = double(rund / pow(10, int(log10(rund) + 1)));
        split[int((u - 0.1) / 0.9 * m)]++;
        fprintf(file_nombers, "%8d    ", rund);
        if ((i + 1) % 7 == 0) fprintf(file_nombers, "\n");
    }

    //> Распределение чисел
    int const w = n/m;
    FILE* file_sectors = fopen("Output/sectors.scv", "w");
    if (!file_sectors) {
        cout << "File opening error!" << endl;
        return 0;
    }

    cout << endl << "Sums in segments: " << endl;
    fprintf(file_sectors, "Промежуток; Экспериментальные значения; Теоретические значения\n");
    for (int i = 0; i < m; i++) {
        printf("%3d: %d;    ", i+1, split[i]);
        fprintf(file_sectors, "%1.4f; %d; %d\n", double(i)/m, split[i], w);
        if ((i+1) % 4 == 0) cout << endl;
    }

    //> Оценка качества последовательности
    double pearson = 0;
    cout << endl <<"Reference value: " << w << endl << endl << "Summand of the Pearson criterion:" << endl;
    for (int i = 0; i < m; i++) {
        double mini_pearson = pow(split[i] - w, 2) / w;
        pearson += mini_pearson;

        printf("%3d: %2.4f;    ", i+1, mini_pearson);
        if ((i+1) % 4 == 0) cout << endl;
    }

    cout << endl << "Pearson criterion: " << pearson << endl << "Probability: ";
    system(("py Scripts/get_probability.py " + to_string(pearson) + " " + to_string(m-1)).c_str());

    fclose(file_sectors);
    fclose(file_nombers);
    return 0;
}