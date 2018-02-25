#include <stdio.h>

int fact_broken(int X) {
  int T = 1;
  int J = 1;
  while (X <= J) {
    T = T * J;
    J = J + 1;
  }
  return T;
}

int fact(int X) {
  int T = 1;
  int J = 1;
  while (J <= X) {
    T = T * J;
    J = J + 1;
  }
  return T;
}

int main() {
  for (int n = 0; n <= 10; n++) {
    printf("Fact %d is %d\n", n, fact(n));
  }
}


