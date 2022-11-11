# Exercises OMP1

Warmup exercises for OpenMP. As my machine featured 24 CPU cores,
I set num_threads = 24

## Factorial

Compute the factorial in a sequential/parallel for-loop.

Easy and effective parallelization possible as all
loop-iterations are independent of each other and OpenMP
provides Reduction-funtionality to collect the results of
each thread efficiently and compute the final result.

!["factorial"](https://github.com/kroppel/advanced-computer-architectures-lab/blob/main/images/factorial.PNG)

## Find

Find a sequence of numbers in a randomly initialized array.

Searching through an array is another operation that can be well parallelized
in general. In this case the break statement and the random array initialization
causes some runs to show a higher speedup (in the case where the sequence is
found towards the end of the array or not found at all, meaning that the whole
array was traversed) while there can be runs where the speedup is much smaller
(in case the sequence is located towards the start of the array).

!["find1"](https://github.com/kroppel/advanced-computer-architectures-lab/blob/main/images/find1.PNG)

!["find2"](https://github.com/kroppel/advanced-computer-architectures-lab/blob/main/images/find2.PNG)

## MatrixMul

Compute the product of two matrices.

My obtained speedup remained almost constant even for different matrix sizes.

!["find2"](https://github.com/kroppel/advanced-computer-architectures-lab/blob/main/images/matmul.PNG)

## RC4

Not solved completely.