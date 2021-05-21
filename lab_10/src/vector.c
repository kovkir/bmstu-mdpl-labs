#include "../inc/vector.h"

int randomize_vector(vector_t v)
{
    if (v == NULL)
        return 1;

    srand(time(NULL));

    for (size_t i = 0; i < v->size; i++)
        v->vec[i] = (float)(rand() % RAND_MAX);

    return 0;
}

vector_t new_alligned_vector_float_32(size_t size)
{
    size_t allignment = sizeof(float);
    size_t a_size = (size % allignment) ? (size + (allignment - size % allignment)) : size;

    vector_t vec = calloc(1, sizeof(struct vector_s) + sizeof(vec_val) * a_size);
    
    if (vec)
        vec->size = a_size;

    return vec;
}

vec_val scalar_product_vector(const vector_t v1, const vector_t v2)
{
    assert(v1->size == v2->size);

    vec_val scalar = 0;

    for (size_t i = 0; i < v1->size; i++)
    {
        vec_val cur = 0;
        cur = (v1->vec[i] * v2->vec[i]);

        scalar += cur;
    }

    return scalar;
}

vec_val scalar_product_asm_vector(const vector_t v1, const vector_t v2) 
{
    vec_val result = 0;

    __asm__(
        "xorps %%xmm2, %%xmm2\n\t"
        :
        :
        );

    for (size_t i = 0; i < v1->size; i += 4)
    {
        __asm__(
            "movups (%0),   %%xmm0\n\t"
            "movups (%1),   %%xmm1\n\t"
            "mulps  %%xmm1, %%xmm0\n\t"
            "haddps %%xmm0, %%xmm0\n\t"
            "addps  %%xmm0, %%xmm2\n\t"
            :
            : "r" (v1->vec + i), "r" (v2->vec + i)
        );
    }

    __asm__(
        "haddps %%xmm2, %%xmm2\n\t"
        "movss %%xmm2, %0\n\t"
        : "=m"(result)
    );

    return result;
}
