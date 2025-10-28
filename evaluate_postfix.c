#include <stdio.h>
#include <ctype.h>

int eval_postfix(char *postfix) {
    int stack[1000];
    int top = -1;
    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i]))
            stack[++top] = postfix[i] - '0';
        else {
            int b = stack[top--];
            int a = stack[top--];
            switch(postfix[i]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        }
    }
    return stack[top];
}

int main() {
    printf("%d\n", eval_postfix("53+82-*"));
    return 0;
}
