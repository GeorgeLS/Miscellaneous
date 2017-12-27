/* Author: George Liontos
   Contact email: cprogrammer98@gmail.com
   
   That's my first excersise from my first semester in NKUA. The asked was to find all
   the perfect, amicable and social numbers within an upper bound of numbers and cycles
*/

#include <stdio.h>

#define MAXNUM 10000000U
#define MAXCYC 28U

typedef unsigned int uint;

__attribute__((always_inline))
inline uint power(uint x, uint y) {
  uint p;
  for (p = 1U; y > 0U; --y, p *= x) {}
  return p;
}

/* There's a more compact way to write this method which takes less lines of code
   but it seems that this way is a little bit faster without compiler optimization */

uint div_sum(uint number) {
  uint sum = 1U;
  uint original = number;             /* Storing original number so we can subtract it in the end */
  uint primeFactors = 0U;

  while ((number % 2U) == 0U) {      /* Factoring by 2 */
    number >>= 1U;
    ++primeFactors;
  }

  if (primeFactors != 0U) {
    sum *= power(2U, primeFactors + 1U) - 1;
  }
  
  primeFactors = 0U;

  while ((number % 3U) == 0U) {            /* Factoring by 3 */
    number /= 3;
    ++primeFactors;
  }

  if (primeFactors != 0U) {
    sum *= ((power(3U, primeFactors + 1U) - 1U) >> 1U);
  }

  uint factor = 5U;
  uint gap = 2U;

  while (factor * factor <= number) {         	/* Factoring by factor */
    primeFactors = 0U;
    while ((number % factor) == 0U) {
      number /= factor;
      ++primeFactors;
    }

    if (primeFactors != 0U) {
      sum *= ((power(factor, primeFactors + 1U) - 1U) /
	      (factor - 1U));
    }

    factor += gap;
    gap = 6U - gap;
  }

  if (number > 1U) {
    sum *= number + 1U;
  }

  sum -= original;
  return sum;
}

int main(void) {
  uint totalCyclesFound = 0U;
  uint amicableNumbers = 0U;
  uint perfectNumbers = 0U;

  for (uint number = 1U; number <= MAXNUM; ++number) {
    uint saveNumber = number;
    uint flag = 0U;
    uint cycle;
    uint sum;
    for (uint currentCycle = 1U; currentCycle <= MAXCYC; ++currentCycle) {
      sum = div_sum(saveNumber);

      if (number < sum && sum <= MAXNUM) {
	saveNumber = sum;
      } else if (number > sum) {
	flag = 1U;
	break;
      } else {
	cycle = currentCycle;
	break;
      }
    }
    
    if (flag != 0U) continue;

    if (number == sum) {
      ++totalCyclesFound;
      if (cycle == 1U) {
	++perfectNumbers;
	printf("Cycle of length %d: %d %d\n", cycle, number, number);
      } else if (cycle == 2U) {
	++amicableNumbers;
	sum = div_sum(number);
	printf("Cycle of length %d: %d %d %d\n", cycle, number, sum, number);
      } else if (cycle >= 3U) {
	printf("Cycle of length %d: %d ", cycle, number);
	saveNumber = number;
	for (uint i = 1U; i <= cycle; ++i) {
	  sum = div_sum(saveNumber);
	  printf("%d ", sum);
	  saveNumber = sum;
	}
	putchar('\n');
      }
    }
  }

  printf("\nFound %d cycles including\n%d perfect cycles and\n"
	 "%d amicable cycles\n\n", totalCyclesFound,
	 perfectNumbers, amicableNumbers);

  return 0;
}
