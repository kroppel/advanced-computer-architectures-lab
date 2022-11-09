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
    TM.print("Sequential Factorial");
    std::cout << factorial << std::endl;
    
    //--------------------------------------------------------------------------
    
    /* Parallel implementation of Factorial: */
    
    double parallelResult = 1;
    
    TM.start();


#pragma omp parallel for reduction(* : parallelResult) num_threads(2)
    for (int i = 1; i <= N; ++i) {
        parallelResult *= i;
    }


    TM.stop();
    TM.print("Parallel Factorial");
    std::cout << parallelResult << std::endl;
}
