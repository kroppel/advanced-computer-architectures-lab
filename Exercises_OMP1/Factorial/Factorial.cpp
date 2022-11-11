#include <iostream>
#include <omp.h>
#include "Timer.hpp"
#include <atomic>

int main() {
    using namespace timer;
    int N = (1 << 30);
    double factorial = 1;
    
    /* Sequential implementation of factorial:*/
    
    Timer<HOST> TM;
    TM.start();
    
    for (int i = 1; i <= N; ++i)
        factorial *= i;
    
    TM.stop();
    double t_seq = TM.duration();
    TM.print("Sequential Factorial");
    std::cout << factorial << std::endl;
    
    //--------------------------------------------------------------------------
    
    /* Parallel implementation of Factorial: */
    
    double parallelResult = 1;
    
    TM.start();


#pragma omp parallel for reduction(* : parallelResult) num_threads(24)
    for (int i = 1; i <= N; ++i) {
        parallelResult *= i;
    }


    TM.stop();
    double t_par = TM.duration();

    TM.print("Parallel Factorial");
    std::cout << parallelResult << std::endl;

    std::cout << "Speedup: " << t_seq/t_par << std::endl;
}
