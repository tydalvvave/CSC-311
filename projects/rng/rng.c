#include <stdio.h>
#include <stdlib.h>
#include "lcg.c"
#include "getfpn.c"

int previousValue = 291;
int multiplier = 67;
int increment = 103;
int modulus = 1023;

int main (int argc, char** argv)
{
  previousValue = linearCongruentialGenerator(previousValue, multiplier, increment, modulus);

  int limit = 20;
  double set[limit];
  
  for (int i = 0; i < limit; i++)
  {
    double y = getfpn(previousValue, multiplier, increment, modulus);
       printf("%.2f\n", y);
       set[i] = y;
       previousValue = linearCongruentialGenerator(previousValue, multiplier, increment, modulus);
  }
  
}
