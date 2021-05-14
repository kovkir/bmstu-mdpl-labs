#include "common.h"

#include "80_bit.h"

void get_sum_80_bit(long double a, long double b, size_t count)
{
    long double c;
    for (size_t i = 0; i < count; ++i)
        c = a + b;
}

void get_sum_80_bit_asm(long double a, long double b, size_t count)
{
    long double c;

    for (size_t i = 0; i < count; ++i)
        asm("fldt %1\n"
            "fldt %2\n"
            "faddp %%ST(0), %%ST(1)\n"
            "fstpt %0\n"
            : "=m"(c)
            : "m"(a), "m"(b));
}

void get_mul_80_bit(long double a, long double b, size_t count)
{
    long double c;
    for (size_t i = 0; i < count; ++i)
        c = a * b;
}

void get_mul_80_bit_asm(long double a, long double b, size_t count)
{
    long double c;

    for (size_t i = 0; i < count; ++i)
        asm("fldt %1\n"
            "fldt %2\n"
            "fmulp %%ST(0), %%ST(1)\n"
            "fstpt %0\n"
            : "=m"(c)
            : "m"(a), "m"(b));
}


void print_80_bit_measures()
{
    printf("    Long double\n\n");

    long double a = 1e23, b = 22e34;

    clock_t begin = clock();
    get_sum_80_bit(a, b, repeats);
    clock_t end = clock();

    printf(SUM_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_sum_80_bit_asm(a, b, repeats);
    end = clock();

    printf(ASM_SUM_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_mul_80_bit(a, b, repeats);
    end = clock();

    printf(MUL_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_mul_80_bit_asm(a, b, repeats);
    end = clock();

    printf(ASM_MUL_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    printf("\n");
}
