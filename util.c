#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

long generateRandomSeed() {
  struct timeval tv;

  gettimeofday(&tv, NULL);

  return tv.tv_usec;
}

void seedRand() {
  srand(generateRandomSeed());
}

float rand1() {
  return (float)rand() / RAND_MAX;
}
