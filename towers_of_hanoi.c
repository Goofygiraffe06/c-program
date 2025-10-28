#include <stdio.h>

void hanoi(int n, char src, char dest, char aux) {
  if (n == 1) {
    printf("Move disk 1 from %c to %c\n", src, dest);
    return;
  }
  hanoi(n-1, src, aux, dest);
  printf("Move disk %d from %c to %c\n", n, src, dest);
  hanoi(n-1, aux, dest, src);
}

int main() {
  hanoi(3, 'A', 'B', 'C');
  return 0;
}
