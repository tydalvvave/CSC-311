#include "rng.h"

double getfpn(int previousValue, int multiplier, int increment, int modulus) {
  return ( (double) linearCongruentialGenerator(previousValue, multiplier, increment, modulus) ) / modulus;
};
