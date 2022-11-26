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

long long int fibonacci_mt_tasks(long long int value, int level) {
    if (value <= 1)
        return 1;
        
    long long int fib_left, fib_right;

    if (value < 40) {
        fib_left  = fibonacci_st(value - 1, level + 1);
        fib_right = fibonacci_st(value - 2, level + 1);
    }

    else {
        #pragma omp parallel num_threads(24)
        {
            #pragma omp single 
            {
                #pragma omp task
                    fib_left  = fibonacci_mt_tasks(value - 1, level + 1);

                #pragma omp task
                    fib_right = fibonacci_mt_tasks(value - 2, level + 1);
            }
        }
    }

    return fib_left + fib_right;
}

long long int fibonacci_mt_nested(long long int value, int level, int max_level) {
    omp_set_nested(1);

    if (value <= 1)
        return 1;
        
    long long int fib_left, fib_right;

    if (level == max_level or value < 20) {
        fib_left  = fibonacci_st(value - 1, level + 1);
        fib_right = fibonacci_st(value - 2, level + 1);
    }

    else {

        #pragma omp parallel num_threads(2)
        {
            #pragma omp sections 
            {
                #pragma omp section
                    fib_left  = fibonacci_mt_nested(value - 1, level + 1, max_level);

                #pragma omp section
                    fib_right = fibonacci_mt_nested(value - 2, level + 1, max_level);
            }
        }
    }

    return fib_left + fib_right;
}

int main() {
    omp_set_dynamic(1);
    //  -------------------------- Benchmarks --------------------------

    int N = 44;
    std::cout << "N: " << N << "\n";
    timer::Timer<timer::HOST> TM;
    TM.start();
    long long int f1 = fibonacci_st(N, 1);
    TM.stop();
    double t1 = TM.duration();

    std::cout << "Result ST: " << f1 << "\n";
    std::cout << "Time ST: " << t1 << " ms\n\n";


    TM.start();
    long long int f2 = fibonacci_mt_tasks(N, 1);
    TM.stop();
    double t2 = TM.duration();

    std::cout << "Result MT Tasks: " << f2 << "\n";
    std::cout << "Time MT Tasks: " << t2 << " ms\n";

    std::cout << "Speedup: " << t1/t2 << "\n\n";


    int max_level = 6; // 2^^(max_level) threads will be created 
    TM.start();
    long long int f3 = fibonacci_mt_nested(N, 1, max_level);
    TM.stop();
    double t3 = TM.duration();

    std::cout << "Result MT Nested: " << f3 << "\n";
    std::cout << "Time MT Nested: " << t3 << " ms\n";
    std::cout << "With " << (1<<(max_level-1)) << " threads (Nesting depth: " << (max_level-1) << ")\n"; 

    std::cout << "Speedup: " << t1/t3 << "\n\n";
}
