#include <vector>

namespace Pseudorandom_numbers {
    class Rundom {
    public:
        static void set_a(int a);
        static void set_b(int b);
        static void set_m(int m);
        static long long creat_rundom_number(); 
        static long long set_start_number();
        static void print_all_numbers();
        static int print_count_of_numbers();
    private:
        static int a, b;
        static long long m;
        static std::vector<long long> random_row;
        static const int limit_T;

        static long long multiplicative_sensor(long long x);
    };
}