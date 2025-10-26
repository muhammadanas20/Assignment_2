#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function Prototypes
void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
char toggleBits(char ch);

int main() {
    char message[200];
    int choice;

    while (1) {
        printf("\n=============================\n");
        printf("   TCS Secure Message Tool\n");
        printf("=============================\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice) {
            case 1:
                printf("\nEnter message to ENCODE: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0'; // remove newline
                encodeMessage(message);
                break;

            case 2:
                printf("\nEnter message to DECODE: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                decodeMessage(message);
                break;

            case 3:
                printf("\nExiting... Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

//---------------------------------------------
// Function to reverse a string
//---------------------------------------------
void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

//---------------------------------------------
// Function to toggle 2nd and 5th bits of a character
//---------------------------------------------
char toggleBits(char ch) {
    // Bit positions (counting from 0)
    int bit2 = 1 << 1; // 2nd bit
    int bit5 = 1 << 4; // 5th bit
    ch = ch ^ bit2;    // Toggle 2nd bit
    ch = ch ^ bit5;    // Toggle 5th bit
    return ch;
}

//---------------------------------------------
// Encoding: Reverse string + Toggle bits
//---------------------------------------------
void encodeMessage(char message[]) {
    reverseString(message);

    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = toggleBits(message[i]);
    }

    printf("\nEncoded Message:\n%s\n", message);
}

//---------------------------------------------
// Decoding: Toggle bits + Reverse string
//---------------------------------------------
void decodeMessage(char message[]) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = toggleBits(message[i]); // untoggle
    }

    reverseString(message);

    printf("\nDecoded Message:\n%s\n", message);
}
