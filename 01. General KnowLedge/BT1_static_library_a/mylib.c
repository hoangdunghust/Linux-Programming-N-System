#include <stdio.h>

void hello_world()
{
    printf("Hello, World from Static Library!\n");
}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    if (b != 0)
    {
        return a / b;
    }
    else
    {
        printf("Error: Division by zero!\n");
        return 0; // or some error value
    }
}

int factorial(int n)
{
    if (n < 0)
    {
        printf("Error: Factorial of negative number!\n");
        return -1; // or some error value
    }
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int fibonacci(int n)
{
    if (n < 0)
    {
        printf("Error: Fibonacci of negative number!\n");
        return -1; // or some error value
    }
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}