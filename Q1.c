#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Function Prototypes
int getIntegerInput(const char* prompt);
float getFloatInput(const char* prompt);
void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count);
void processSale(int isbns[], int quantities[], int count);
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int count);
int findBookByISBN(int isbns[], int count, int isbn);

int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][50];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int count = 0;
    int choice;

    do {
        printf("\n===== Liberty Books Inventory System =====\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");


        choice = getIntegerInput("Enter your choice: ");

        switch (choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &count);
                break;
            case 2:
                processSale(isbns, quantities, count);
                break;
            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, count);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}


int getIntegerInput(const char* prompt) {
    int value;
    int result;
    printf("%s", prompt); 
    while (1) { 
        result = scanf("%d", &value);
        if (result == 1) {    
            while (getchar() != '\n'); // Clear buffer on success
            return value; 
        } else {     
            printf("Invalid input! Please enter a number: ");  
            while (getchar() != '\n'); // Clear buffer on failure
        }
    }
}

float getFloatInput(const char* prompt) {
    float value;
    int result;
    printf("%s", prompt); 
    while (1) { 
        result = scanf("%f", &value);
        if (result == 1) {    
            while (getchar() != '\n'); // Clear buffer on success
            return value; 
        } else {     
            printf("Invalid input! Please enter a number: ");  
            while (getchar() != '\n'); // Clear buffer on failure
        }
    }
}


// Function to find a book by ISBN 
int findBookByISBN(int isbns[], int count, int isbn) {
    int i;
    for (i = 0; i < count; i++) {
        if (isbns[i] == isbn) {
            return i;
        }
    }
    return -1;  // Not found
}

// Function to add a new book
void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("Inventory is full! Cannot add more books.\n");
        return;
    }

    int isbn = getIntegerInput("Enter ISBN: ");

    // Check for duplicate ISBN
    if (findBookByISBN(isbns, *count, isbn) != -1) {
        printf("Error: A book with this ISBN already exists.\n");
        return;
    }

    isbns[*count] = isbn;
    printf("Enter title: ");
    fgets(titles[*count], 50, stdin);
    titles[*count][strcspn(titles[*count], "\n")] = '\0'; // Remove newline

   
    while (1) {
        prices[*count] = getFloatInput("Enter price: ");
        if (prices[*count] >= 0) {
            break; 
        }
        printf("Error: Price cannot be negative.\n");
    }

    
    while (1) {
        quantities[*count] = getIntegerInput("Enter quantity: ");
        if (quantities[*count] >= 0) {
            break; 
        }
        printf("Error: Quantity cannot be negative.\n");
    }

    (*count)++;
    printf("Book added successfully!\n");
}

// Function to process a sale
void processSale(int isbns[], int quantities[], int count) {
    int isbn, qtySold;
    
  
    isbn = getIntegerInput("Enter ISBN of the book sold: ");

    int index = findBookByISBN(isbns, count, isbn);
    if (index == -1) {
        printf("Error: Book not found.\n");
        return;
    }

    while (1) {
        qtySold = getIntegerInput("Enter quantity sold: ");
        if (qtySold > 0) {
            break; 
        }
        printf("Error: Quantity sold must be a positive number.\n");
    }

    if (qtySold > quantities[index]) {
        printf("Error: Not enough stock available. Only %d left.\n", quantities[index]);
    } else {
        quantities[index] -= qtySold;
        printf("Sale processed successfully! Remaining stock: %d\n", quantities[index]);
    }
}

// Function to generate a low-stock report 
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int count) {
    int found = 0;
    printf("\n===== Low Stock Report (Quantity < 5) =====\n");
    printf("ISBN\t| Title\t\t\t| Price\t| Qty\n");
    printf("------------------------------------------------------\n");

    int i ;
    for (i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            printf("%d\t| %-20s\t| %.2f\t| %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("All books have sufficient stock.\n");
    }
}