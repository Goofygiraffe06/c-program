#include <stdio.h>
#include <ctype.h>

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void infix_to_postfix(char *infix, char *postfix) {
    char stack[1000];
    int top = -1;
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i]))
            postfix[j++] = infix[i];
        else if (infix[i] == '(')
            stack[++top] = infix[i];
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = stack[top--];
            top--;
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[j++] = stack[top--];
            stack[++top] = infix[i];
        }
    }
    while (top != -1)
        postfix[j++] = stack[top--];
    postfix[j] = '\0';
}

int main() {
    char postfix[1000];
    infix_to_postfix("A+B*C", postfix);
    printf("%s\n", postfix);
    return 0;
}
