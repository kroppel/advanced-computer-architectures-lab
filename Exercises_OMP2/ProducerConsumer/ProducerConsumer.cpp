#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

void test_producer_consumer(int Buffer[32], int * count) {
	int i = 0;

	while (i < 35000) {					// number of test
#pragma omp critical
		{
			// PRODUCER
			if ((rand() % 50) == 0) {		// some random computations
				if (*count < 31) {
					++*count;
					std::cout << "Thread:\t" << omp_get_thread_num()
							<< "\tProduce on index: " << *count << std::endl;
					Buffer[*count] = omp_get_thread_num();
				}
			}

			// CONSUMER
			if ((std::rand() % 51) == 0) {		// some random computations
				if (*count >= 1) {
					int var = Buffer[*count];
					std::cout << "Thread:\t" << omp_get_thread_num()
							<< "\tConsume on index: " << *count
							<< "\tvalue: " << var << std::endl;
					--*count;
				}
			}
			i++;
		}
	}
}

int main() {
	int Buffer[32];
	int count = 0;
	std::srand(time(NULL));

	omp_set_num_threads(2);

#pragma omp parallel 
	{
		test_producer_consumer(Buffer, &count);
	}
}
