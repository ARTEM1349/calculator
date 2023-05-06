#include <check.h>
#include <stdlib.h>
#include "lib.h"

START_TEST(test_evaluate_expression_simple)
{
    double result = evaluate_expression("2+2");
    ck_assert_double_eq_tol(result, 4.0, 0.0001);
}
END_TEST

START_TEST(test_evaluate_expression_with_parentheses)
{
    double result = evaluate_expression("(2+3)*4");
    ck_assert_double_eq_tol(result, 20.0, 0.0001);
}
END_TEST

START_TEST(test_evaluate_expression_with_exponentiation)
{
    double result = evaluate_expression("2^3+4");
    ck_assert_double_eq_tol(result, 12.0, 0.0001);
}
END_TEST

START_TEST(test_evaluate_expression_with_floating_point_numbers)
{
    double result = evaluate_expression("3.14159*2");
    ck_assert_double_eq_tol(result, 6.28318, 0.0001);
}
END_TEST

Suite *lib_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("lib");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_evaluate_expression_simple);
    tcase_add_test(tc_core, test_evaluate_expression_with_parentheses);
    tcase_add_test(tc_core, test_evaluate_expression_with_exponentiation);
    tcase_add_test(tc_core, test_evaluate_expression_with_floating_point_numbers);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = lib_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
