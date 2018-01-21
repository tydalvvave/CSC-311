#include "rng.h"

int linearCongruentialGenerator(int previousValue, int multiplier, int increment, int modulus) {
  previousValue = (multiplier * previousValue + increment) % modulus;
  return previousValue;
};
