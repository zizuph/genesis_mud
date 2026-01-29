#include <macros.h>

/*
 * This function will return probability of succes that
 *   random(x) < random(y)
 */
int
prob_less(int x, int y)
{
  int i, prob;

  prob = y*(y-1)/2;
  if(x<y) prob -= ((y-x)*(y-x-1)/2);

  return (100*prob)/(x*y);
}

/*
 * This function will return probability of succes that
 *   random(x) = random(y)
 */
int
prob_eq(int x, int y)
{
  return (100*MIN(x,y))/(x*y);
}
