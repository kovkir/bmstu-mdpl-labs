#include <stdio.h>
#include <stdlib.h>

#include "../inc/vector.h"
#include "../inc/color.h"

#define COUNT 100000
#define OK 0

int main(void)
{
    vector_t v1 = new_alligned_vector_float_32(100);
    vector_t v2 = new_alligned_vector_float_32(100);

    randomize_vector(v1);
    randomize_vector(v2);

    clock_t start = 0, end = 0;
    vec_val res;
    
    for (int i = 0; i < COUNT; i++)
    {
        start += clock();
        res = scalar_product_vector(v1, v2);
        end += clock();
    }

    printf("\n%s%sresult%s%s_%s%sc %s%s= %s%s%.3g\n%s%stime%s%s_%s%sc   %s%s= %s%s%.3g%s%s\n\n",
        SET_COLOR, YELLOW, SET_COLOR, BASE_COLOR, SET_COLOR, BLUE, SET_COLOR, BASE_COLOR, SET_COLOR, 
        GREEN, res, SET_COLOR, YELLOW, 
        SET_COLOR, BASE_COLOR, SET_COLOR, BLUE, SET_COLOR, BASE_COLOR,
        SET_COLOR, GREEN, (double) (end - start) / CLOCKS_PER_SEC / COUNT, SET_COLOR, BASE_COLOR);
    
    start = 0;
    end = 0;
    vec_val res_asm;
    
    for (int i = 0; i < COUNT; i++)
    {
        start += clock();
        res_asm = scalar_product_asm_vector(v1, v2);
        end += clock();
    }

    printf("%s%sresult%s%s_%s%sasm %s%s= %s%s%.3g\n%s%stime%s%s_%s%sasm   %s%s= %s%s%.3g%s%s\n\n",
        SET_COLOR, YELLOW, SET_COLOR, BASE_COLOR, SET_COLOR, PURPURE, SET_COLOR, BASE_COLOR, SET_COLOR, 
        GREEN, res, SET_COLOR, YELLOW, 
        SET_COLOR, BASE_COLOR, SET_COLOR, PURPURE, SET_COLOR, BASE_COLOR,
        SET_COLOR, GREEN, (double) (end - start) / CLOCKS_PER_SEC / COUNT, SET_COLOR, BASE_COLOR);

    free(v1);
    free(v2);

    return OK;
}
