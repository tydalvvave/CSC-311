#include <stdio.h>
#include <stdlib.h>
#include "lcg.c"
#include "getfpn.c"

// lcg.c and getfpn.c parameters
int previousValue = 291;
int multiplier = 67;
int increment = 103;
int modulus = 1023;

int main (int argc, char** argv)
{
  previousValue = linearCongruentialGenerator(previousValue, multiplier, increment, modulus);

  int limit = 20; // Number of data points
  double set[limit]; // Array for data points
  int histogram[10]; // Histogram for data points

  // Clear the space in the array
  for (int h = 0; h < 10; h++)
  {
    histogram[h] = 0;
  }
  
  // Get and print values
  for (int i = 0; i < limit; i++)
  {
    double y = getfpn(previousValue, multiplier, increment, modulus);
       printf("%.2f\n", y);
       set[i] = y;
       previousValue = linearCongruentialGenerator(previousValue, multiplier, increment, modulus);
  }

  printf("\n");

  // Print and check values in array
  for (int j = 0; j < limit; j++)
  {
    printf("%.2f\n", set[j]);
  }

  printf("\n");

  // Get and print group number
  for (int k = 0; k < limit; k++)
  {
    int group = set[k] * 10; // Group number for each value in set
    printf("%u\n", group);
    histogram[group]++;
    
  }

  printf("\n");

  // Show the results in the histogram
  for (int l = 0; l < 10; l++)
  {
    printf("In group %u, there are %u entries.\n", l, histogram[l]);
  }
}
