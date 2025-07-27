using ulll = __uint128_t;

const ulll mod = (ulll(1) << 89) - 1;

// return x % mod
//     or x % mod + mod (unlikely)
__attribute__((always_inline))
ulll remainder(ulll x) {
  return (x & mod) + (x >> 89);
}

ulll remainder_repeat(ulll x) {
  x = (x & mod) + (x >> 89);
  return (x & mod) + (x >> 89);
}

ulll remainder_cmov(ulll x) {
  x = (x & mod) + (x >> 89);
  if (x >= mod)
    x -= mod;
  return x;
}