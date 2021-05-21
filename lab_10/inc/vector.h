#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <pmmintrin.h>

#define RAND_MAX 10000

typedef float vec_val;

typedef struct vector_s
{
    size_t size;
    vec_val vec[];
} *vector_t;

int randomize_vector(vector_t v);

vector_t new_alligned_vector_float_32(size_t size);

vec_val scalar_product_vector(const vector_t v1, const vector_t v2);

vec_val scalar_product_asm_vector(const vector_t v1, const vector_t v2);
