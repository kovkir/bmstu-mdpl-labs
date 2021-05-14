#include "common.h"

#include "64_bit.h"

void get_sum_64_bit(double a, double b, size_t count)
{
    double c;
    for (size_t i = 0; i < repeats; ++i)
        c = a + b;
}

void get_sum_64_bit_asm(double a, double b, size_t count)
{
    double c;

    for (size_t i = 0; i < count; ++i)
        asm("fldl %1\n"
            "fldl %2\n"
            "faddp %%ST(0), %%ST(1)\n"
            "fstpl %0\n"
            : "=m"(c)
            : "m"(a), "m"(b));
}

void get_mul_64_bit(double a, double b, size_t count)
{
    double c;
    for (size_t i = 0; i < repeats; ++i)
        c = a * b;
}

void get_mul_64_bit_asm(double a, double b, size_t count)
{
    double c;

    for (size_t i = 0; i < count; ++i)
        asm("fldl %1\n"
            "fldl %2\n"
            "fmulp %%ST(0), %%ST(1)\n"
            "fstpl %0\n"
            : "=m"(c)
            : "m"(a), "m"(b)
            :);
}

void print_64_bit_measures()
{
    printf("    Double\n\n");

    double a = 1e23, b = 22e34;

    clock_t begin = clock();
    get_sum_64_bit(a, b, repeats);
    clock_t end = clock();

    printf(SUM_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_sum_64_bit_asm(a, b, repeats);
    end = clock();

    printf(ASM_SUM_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC  / repeats);

    begin = clock();
    get_mul_64_bit(a, b, repeats);
    end = clock();

    printf(MUL_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_mul_64_bit_asm(a, b, repeats);
    end = clock();

    printf(ASM_MUL_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    printf("\n");
}
