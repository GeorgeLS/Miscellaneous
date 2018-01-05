#include <stdio.h>

typedef unsigned long long ull;
typedef unsigned int uint;

static inline ull countTrailingZeros(ull value) {
  if (value & 0x1) return 0ULL;
  else {
    ull zeros = 1ULL;
    if (!(value & 0xFFFFFFFF)) { value >>= 32ULL; zeros += 32ULL; }
    if (!(value & 0xFFFF)) { value >>= 16ULL; zeros += 16ULL; }
    if (!(value & 0xFF)) { value >>= 8ULL; zeros += 8ULL; }
    if (!(value & 0xF)) { value >>= 4ULL; zeros += 4ULL; }
    if (!(value & 0x3)) { value >>= 2ULL; zeros += 2ULL; }
    zeros -= value & 0x1;
    return zeros;
  }
}

ull power(ull x, ull y) {
  ull power;
  for (power = 1ULL; y != 0ULL; --y, power *= x) {}
  return power;
}

int main(void) {
  printf("Enter number of disks: ");
  ull disks;
  scanf("%llu", &disks);
  register ull moves = 1ULL << disks;
  for (register ull i = 1; i != moves; ++i) {
    register uint moveFrom = (i & (i - 1U)) % 3 + 1U;
    register uint moveTo = ((i | (i - 1U)) + 1U) % 3 + 1U;
    ull zeros = countTrailingZeros(i);
    printf("Move disk %llu from peg %c to peg %c\n",
	         zeros, 64U + moveFrom, 64U + moveTo);
  }
  printf("Number of moves: %llu\n",  (1ULL << disks) - 1ULL);
  return 0;
}
