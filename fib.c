#include <stdio.h>
#include <stdlib.h>

unsigned long long recursive_fib(int position) {
  if (position == 0)
    return 0;
  if (position == 1 || position == 2)
    return 1;
  return recursive_fib(position - 1) + recursive_fib(position - 2);
}

unsigned long long iterative_fib(int position) {
  if (position == 0)
    return 0;
  if (position == 1 || position == 2)
    return 1;
  unsigned long long previous = 1;
  unsigned long long current = 1;
  unsigned long long next_fib;
  for (int index = 3; index <= position; index++) {
    next_fib = previous + current;
    previous = current;
    current = next_fib;
  }
  return current;
}

unsigned long long *fib_cache;

unsigned long long memoized_recursive_fib(int position) {
  if (fib_cache[position] != -1) {
    return fib_cache[position];
  }

  if (position == 0) {
    fib_cache[position] = 0;
  } else if (position == 1 || position == 2) {
    fib_cache[position] = 1;
  } else {
    fib_cache[position] = memoized_recursive_fib(position - 1) +
                          memoized_recursive_fib(position - 2);
  }
  return fib_cache[position];
}

unsigned long long fib_wrapper(int position, char method) {
  if (method == 'r') {
    return recursive_fib(position);
  } else if (method == 'i') {
    return iterative_fib(position);
  }
  return 0;
}

unsigned long long memoized_fib_wrapper(int position, char method) {
  if (method == 'r') {
    return memoized_recursive_fib(position);
  } else if (method == 'i') {
    return iterative_fib(position);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <integer> <r|i>\n", argv[0]);
    return 1;
  }

  int position = atoi(argv[1]);
  char method = argv[2][0];
  unsigned long long result;

  if (method == 'r') {
    fib_cache = (unsigned long long *)malloc((position + 1) *
                                             sizeof(unsigned long long));
    for (int i = 0; i <= position; i++) {
      fib_cache[i] = -1;
    }
    result = memoized_fib_wrapper(position - 1, method);
    free(fib_cache);
  } else {
    result = fib_wrapper(position - 1, method);
  }

  printf("%llu\n", result);

  return 0;
}
