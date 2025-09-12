#include <algorithm>
#include <iostream>
using namespace std;

#include "../Headers/Rundom.h"
using namespace Pseudorandom_numbers;

int Rundom::a = 0;
int Rundom::b = 0;
long long Rundom::m = 0;
const int Rundom::limit_T = 10000;
vector<long long> Rundom::random_row {};

long long Rundom::multiplicative_sensor(long long x) {
    return (a * x + b) % m;
}

void Rundom::set_a(int a_outer) {
    Rundom::a = a_outer;
    return;
}

void Rundom::set_b(int b_outer) {
    Rundom::b = b_outer;
    return;
}

void Rundom::set_m(int m_outer) {
    Rundom::m = m_outer;
    return;
}

long long Rundom::set_start_number() {
    cout << "Write nomber-zatravku: ";
    long long x = 0;
    cin >> x;
    random_row.push_back(x);
    return x;
}

long long Rundom::creat_rundom_number() {
    if (random_row.size() == 0) {
        return set_start_number();
    }
    long long new_rand_nom = multiplicative_sensor(random_row.back());
    if (find(random_row.end() - min(limit_T, int(random_row.size())), random_row.end(), new_rand_nom) == random_row.end()) {
        random_row.push_back(new_rand_nom);
    } else {
        //print_all_numbers();
        return set_start_number();
    }
    return new_rand_nom;
}

void Rundom::print_all_numbers(){
    for (int i = 0; i < random_row.size(); i++){
		cout << random_row[i] << ' ';
	}
	cout << endl;
	return;
}

int Rundom::print_count_of_numbers(){
    return random_row.size();
}