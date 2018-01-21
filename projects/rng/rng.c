#include <stdio.h>
#include <stdlib.h>
#include "rng.h"

// lcg.c and getfpn.c parameters
int previousValue = 291;
int multiplier = 67;
int increment = 103;
int modulus = 4096;

int main (int argc, char** argv)
{
  // Set initial value
  previousValue = linearCongruentialGenerator(previousValue,
					      multiplier,
					      increment,
					      modulus);

  int limit = 10000; // Number of data points
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
    // printf("%.2f\n", y);
    set[i] = y;
    previousValue = linearCongruentialGenerator(previousValue,
						   multiplier,
						   increment,
						   modulus);
  }

  // Print and check values in array
  for (int j = 0; j < limit; j++)
  {
    //printf("%.2f\n", set[j]);
  }

  // Get and print group number
  for (int k = 0; k < limit; k++)
  {
    int group = set[k] * 10; // Group number for each threshold in set
    // printf("%u\n", group);
    histogram[group]++;
    
  }

  printf("\nRandom Number Generator\n");
  printf("\nGenerating values between 0.0 and 1.0 ...\n");
  printf("\nCreating histogram ...\n\n");
  
  // Show the results in the histogram
  for (int l = 0; l < 10; l++)
  {
    double threshLO = ((double) l) / 10;
    double threshHI = (((double) l) + 1) / 10;

    if (l != 9)
    {
      printf("At threshold [%.1f, %.1f), there are %u entries.\n",
	     threshLO, threshHI, histogram[l]);
    }
    else
    {
       printf("At threshold [%.1f, %.1f], there are %u entries.\n",
	      threshLO, threshHI, histogram[l]);
    }
  }

  printf("\n");
}
