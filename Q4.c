#include <stdio.h>

#define MAX 5  // Maximum size of the stack

// Function prototypes
void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {
    int stack[MAX];
    int top = -1;  // Empty stack
    int choice;

    do {
        printf("\n========== Stack Operations ==========\n");
        printf("1. PUSH (Insert Element)\n");
        printf("2. POP (Remove Element)\n");
        printf("3. PEEK (Top Element)\n");
        printf("4. DISPLAY (All Elements)\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top, MAX);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to PUSH element onto stack
void push(int stack[], int *top, int maxSize) {
    if (*top == maxSize - 1) {
        printf("Stack Overflow! Cannot insert element.\n");
        return;
    }

    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);

    (*top)++;
    stack[*top] = value;
    printf("Element %d pushed successfully!\n", value);
}

// Function to POP element from stack
void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow! No element to remove.\n");
        return;
    }

    int value = stack[*top];
    (*top)--;
    printf("Element %d popped from stack.\n", value);
}

// Function to PEEK (display top element)
void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty! Nothing to peek.\n");
        return;
    }
    printf("Top element: %d\n", stack[top]);
}

// Function to DISPLAY all elements in the stack
void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty!\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}
