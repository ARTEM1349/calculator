#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

#define BUFFER_SIZE 256

int main(void)
{
    char buffer[BUFFER_SIZE];
    printf("Ведіть приклад:\n");
    fgets(buffer, BUFFER_SIZE, stdin);
    double result = evaluate_expression(buffer);
    printf("Результат: %g\n", result);
    return 0;
}
