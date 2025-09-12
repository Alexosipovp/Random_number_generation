#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cstdio>
using namespace std;

#include "Headers/Rundom.h"
using namespace Pseudorandom_numbers;

int main() {
    const int n = 20000;        // Кол-во случайных чисел
    const int m = 30;           // Кол-во разбиений (20-50)
    vector <int> split (m, 0);  // Сумма чисел по секторам

    //! Начальное условие
    Rundom::set_a(2503);
    Rundom::set_b(2509);
    Rundom::set_m(10000000);
    
    //> Генерация ряда случайных чисел
    for (int i = 0; i < n; i++) {
        long long rund = Rundom::creat_rundom_number(); //? start: 798451
        double u = double(rund / pow(10, int(log10(rund) + 1)));
        split[int((u - 0.1) / 0.9 * m)]++;
    }

    //> Распределение чисел
    int const w = n/m;
    FILE* file = fopen("sectors.scv", "w");
    if (!file) {
        cout << "File opening error!" << endl;
        return 0;
    }

    cout << endl << "Sums in segments: " << endl;
    fprintf(file, "Промежуток; Экспериментальные значения; Теоретические значения\n");
    for (int i = 0; i < m; i++) {
        printf("%3d: %d;    ", i+1, split[i]);
        fprintf(file, "%1.4f; %d; %d\n", double(i)/m, split[i], w);
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

    fclose(file);
    cout << endl << "Pearson criterion: " << pearson << endl;
    return 0;
}