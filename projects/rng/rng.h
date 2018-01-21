#ifndef RNG_H
#define RNG_H

/**
   linearCongruentialGenerator
   ---------------------------
   Parameters: previousValue, multiplier, increment, modulus

   Description: Uses a linear congruential formula to simulate
   a random number generator

   Returns an integer.
 **/
int linearCongruentialGenerator(int previousValue,
				int multiplier,
				int increment,
				int modulus);

/**
   getfpn
   ------
   Parameters: previousValue, multiplier, increment, modulus

   Description: Gets a floating point number

   Returns an double.
 **/
double getfpn(int previousValue,
	      int multiplier,
	      int increment,
	      int modulus);

#endif // RNG_H
