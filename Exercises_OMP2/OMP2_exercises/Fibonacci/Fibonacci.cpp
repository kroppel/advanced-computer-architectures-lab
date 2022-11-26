#include <iostream>
#include <omp.h>
#include "Timer.hpp"

long long int fibonacci_st(long long int value, int level) {
    if (value <= 1)
        return 1;

    long long int fib_left, fib_right;

    fib_left  = fibonacci_st(value - 1, level + 1);
    fib_right = fibonacci_st(value - 2, level + 1);

    return fib_left + fib_right;
}

long long int fibonacci_mt(long long int value, int level) {
    if (value <= 1)
        return 1;

    long long int fib_left, fib_right;
    #pragma omp parallel num_threads(24)
    {
        #pragma omp single 
        {
            #pragma omp task
            if (value > 30) 
                fib_left  = fibonacci_mt(value - 1, level + 1);
            else
                fib_left  = fibonacci_st(value - 1, level + 1);

            #pragma omp task
            if (value > 35) 
                fib_right = fibonacci_mt(value - 2, level + 1);
            else
                fib_right = fibonacci_st(value - 2, level + 1);
        }
    }

    return fib_left + fib_right;
}

int main() {
    omp_set_dynamic(1);
    //  -------------------------- Benchmarks --------------------------

    int N = 40;
    std::cout << "N: " << N << "\n";
    timer::Timer<timer::HOST> TM;
    TM.start();
    long long int f1 = fibonacci_st(N, 1);
    TM.stop();
    double t1 = TM.duration();

    std::cout << "Result ST: " << f1 << "\n";
    std::cout << "Time ST: " << t1 << "\n";


    TM.start();
    long long int f2 = fibonacci_mt(N, 1);
    TM.stop();
    double t2 = TM.duration();

    std::cout << "Result MT: " << f2 << "\n";
    std::cout << "Time MT: " << t2 << "\n";

    std::cout << "Speedup: " << t1/t2 << "\n";
}
