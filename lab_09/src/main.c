#include <stdio.h>
#include <math.h>

#include "common.h"

#include "32_bit.h"
#include "64_bit.h"
#include "80_bit.h"

void sin_cmp()
{
  double res = 0.0;

  printf("\n    sin(pi)\n\n");
  printf("3.14     : %g\n", sin(3.14));
  printf("3.141596 : %g\n", sin(3.141596));

  asm("fldpi\n"
      "fsin\n"
      "fstpl %0\n"
      :
      :"m"(res));

  printf("fpu      : %-10.3g\n", res);
  printf("\n");

  printf("    sin(pi / 2)\n\n");
  printf("3.14 / 2     : %g\n", sin(3.14 / 2));
  printf("3.141596 / 2 : %g\n", sin(3.141596 / 2));

  res = 0.0;
  double del = 2.0;
  
  asm("fldl %1\n"
      "fldpi\n"
      "fdivp %%ST(0), %%ST(1)\n"
      "fsin\n"
      "fstpl %0\n"
      : "=m"(res)
      : "m"(del));

  printf("fpu          : %-10.3g\n", res);
  printf("\n");
}

int main()
{
  sin_cmp();

  print_32_bit_measures();
  print_64_bit_measures();
  print_80_bit_measures();

  return 0;
}
