#include <stdio.h>

int check_parenthesis(char *s) {
  char stack[1000];
  int top = -1;
  for (int i = 0; s[i]; i++) {
    if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
      stack[++top] = s[i];
    }
    else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
      if (top == -1) return 0;
      char ch = stack[top--];
      if ((s[i] == ')' && ch != '(') ||
          (s[i] == ']' && ch != '[') ||
          (s[i] == '}' && ch != '{')) return 0;
    }
  }
  return top == -1;
}

int main() {
  printf("%d\n", check_parenthesis("{({})}"));
  return 0;
}
