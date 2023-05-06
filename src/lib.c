#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static double evaluate_term(const char**);
static double evaluate_factor(const char**);
static double evaluate_exponentiation(const char**);
static double evaluate_multiplication(const char**);
static double evaluate_addition(const char**);
static double evaluate_number(const char**);
//Головна функція, яка приймає рядок, який містить арифметичний вираз та повертає його результат.
double evaluate_expression(const char* expression)
{
    const char* ptr = expression;
    return evaluate_addition(&ptr);
}
//Функція для обчислення множення та ділення у виразі. Вона отримує вказівник на покажчик на рядок та повертає результат обчислення.
static double evaluate_term(const char** ptr)
{
    double left = evaluate_factor(ptr);
    while (**ptr == '*' || **ptr == '/') {
        if (*((*ptr)++) == '*') {
            left *= evaluate_factor(ptr);
        } else {
            left /= evaluate_factor(ptr);
        }
    }
    return left;
}
// Функція для обчислення піднесення до степеня у виразі. Вона отримує вказівник на покажчик на рядок та повертає результат обчислення.
static double evaluate_factor(const char** ptr)
{
    double left = evaluate_exponentiation(ptr);
    while (**ptr == '^') {
        ++(*ptr);
        left = pow(left, evaluate_factor(ptr));
    }
    return left;
}
// Функція для обчислення виразу, який знаходиться в дужках у виразі. Вона отримує вказівник на покажчик на рядок та повертає результат обчислення.
static double evaluate_exponentiation(const char** ptr)
{
    if (**ptr == '(') {
        ++(*ptr); // '('
        double value = evaluate_addition(ptr);
        ++(*ptr); // ')'
        return value;
    }
    return evaluate_number(ptr);
}
//Функція для обчислення додавання та віднімання у виразі. Вона отримує вказівник на покажчик на рядок та повертає результат обчислення.
static double evaluate_multiplication(const char** ptr)
{
    double left = evaluate_term(ptr);
    while (**ptr == '+' || **ptr == '-') {
        if (*((*ptr)++) == '+') {
            left += evaluate_term(ptr);
        } else {
            left -= evaluate_term(ptr);
        }
    }
    return left;
}
// Функція для обчислення множення та ділення у виразі. Вона отримує вказівник на покажчик на рядок та повертає результат обчислення.
static double evaluate_addition(const char** ptr)
{
    double left = evaluate_multiplication(ptr);
    while (**ptr == '*' || **ptr == '/') {
        if (*((*ptr)++) == '*') {
            left *= evaluate_multiplication(ptr);
        } else {
            left /= evaluate_multiplication(ptr);
        }
    }
    return left;
}
// Функція для обчислення числа виразу. Вона отримує вказівник на покажчик на рядок та повертає результат обчислення
static double evaluate_number(const char** ptr)
{
    double value = 0;
    while (isdigit(**ptr)) {
        value = 10 * value + (*((*ptr)++) - '0');
    }
    if (**ptr == '.') {
        ++(*ptr);
        double factor = 1;
        while (isdigit(**ptr)) {
            factor *= 0.1;
            value += factor * ((*((*ptr)++) - '0'));
        }
    }
    return value;
}
