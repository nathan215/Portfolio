# A Fast Interger Factorization
## Project Overview
The objective of this program is to find a fast algorithm to do factorization.
The program implements the Pollard-Rho prime factorization algorithm. 
The purpose of the algorithm is to factor a number into the product of several prime numbers.

## Functionality
To factorize the range of number, run the following code.  
`factorize [range_start] [range_end]`


## Tech use 
The code starts by defining a function factorize, which takes as input a number n to be factorized and returns a vector of prime factors of n.  
The function first checks if n is a prime number and returns n itself as the only factor if that's the case.   
If n is not prime, the function starts the Pollard-Rho algorithm.  

The algorithm is based on the idea of generating a sequence of numbers and checking if any of them is divisible by n,  
in which case that number is a factor of n. To generate this sequence, the function uses the following formula:  
`x = (x * x + c) % n`
where x is a number in the sequence, c is a constant, and % is the modulo operator.   
In this implementation, c is chosen randomly from the range [1, n - 1] for each iteration.  
The function then repeatedly applies the above formula and calculates the greatest common divisor (GCD) of n and x - y  
(where y is another number in the sequence), until the GCD is greater than 1 and less than n. 
If the GCD is greater than 1 and less than n, it means that it is a factor of n.  
The function repeats this process until n is completely factorized into prime factors.  
The prime factors are stored in a vector and returned as the result of the factorize function.  




