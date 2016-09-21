#include "Random.h"
using CSC2110::Random;

#include <time.h>
#include <stdlib.h>

Random::Random()
{
   randomInit();
}

Random::~Random()
{
}

Random* Random::getRandom()
{
   static Random random;  //initialized when method is called the first time
   return &random;  
}

void Random::randomInit()
{
   srand (time(NULL));

   //try to get a more random starting number
   rand();
   rand();
   rand();
   rand();
}

int Random::getRandomInt(int lower, int upper)
{
   int diff = upper - lower + 1;
   int random_num = rand()%diff;  
   random_num = random_num + lower;  //gives a number between lower and upper, inclusive
   return random_num;
}

float Random::getRandomFloat(float lower, float upper)
{
   float r_float_1 = (float) rand();
   float r_float_2 = (float) RAND_MAX;

   float random_normalized = r_float_1/r_float_2;  //between 0.0 and 1.0
   float random_float = lower + random_normalized*(upper - lower);
   return random_float;
}
