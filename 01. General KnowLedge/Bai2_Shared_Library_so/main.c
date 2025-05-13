#include <stdio.h>
#include "mylib.h"

int main()
{
    int a = 5, b = 3;
    hello();
    printf("add(%d, %d) = %d\n", a, b, add(a, b));
    printf("subtract(%d, %d) = %d\n", a, b, subtract(a, b));
    printf("multiply(%d, %d) = %d\n", a, b, multiply(a, b));
    printf("divide(%d, %d) = %d\n", a, b, divide(a, b));
    printf("factorial(%d) = %d\n", add(a, b), factorial(add(a, b)));
    printf("fibonacci(%d) = %d\n", multiply(a, b), fibonacci(multiply(a, b)));
    return 0;
}
