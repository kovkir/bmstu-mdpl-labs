#include "common.h"

#include "32_bit.h"

void get_sum_32_bit(float a, float b, size_t count)
{
    float c;
    for (size_t i = 0; i < count; ++i)
        c = a + b;
}

void get_sum_32_bit_asm(float a, float b, size_t count)
{
    float c;

    for (size_t i = 0; i < count; ++i)
        asm("flds %1\n"
            "flds %2\n"
            "faddp %%ST(0), %%ST(1)\n"
            "fstps %0\n"
            : "=m"(c)
            : "m"(a), "m"(b));
}

void get_mul_32_bit(float a, float b, size_t count)
{
    float c;
    for (size_t i = 0; i < count; ++i)
        c = a * b;
}

void get_mul_32_bit_asm(float a, float b, size_t count)
{
    float c;

    for (size_t i = 0; i < count; ++i)
        asm("flds %1\n" //загрузка данных в вершину стека сопроцессора
            "flds %2\n"
            "fmulp %%ST(0), %%ST(1)\n"
            "fstps %0\n" //сохранение вершины стека сопроцессора в память
            : "=m"(c)
            : "m"(a), "m"(b));
}

void print_32_bit_measures()
{
    printf("    Float\n\n");

    float a = 1e23, b = 22e34;

    clock_t begin = clock();
    get_sum_32_bit(a, b, repeats);
    clock_t end = clock();

    printf(SUM_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_sum_32_bit_asm(a, b, repeats);
    end = clock();

    printf(ASM_SUM_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_mul_32_bit(a, b, repeats);
    end = clock();

    printf(MUL_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    begin = clock();
    get_mul_32_bit_asm(a, b, repeats);
    end = clock();

    printf(ASM_MUL_FORMAT, (double)(end - begin) / CLOCKS_PER_SEC / repeats);

    printf("\n");
}
