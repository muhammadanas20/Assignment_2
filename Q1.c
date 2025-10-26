#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Function Prototypes
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
        printf("Enter your choice: ");
        scanf("%d", &choice);

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

    int isbn;
    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    // Check for duplicate ISBN
    if (findBookByISBN(isbns, *count, isbn) != -1) {
        printf("Error: A book with this ISBN already exists.\n");
        return;
    }

    isbns[*count] = isbn;
    printf("Enter title: ");
    getchar(); // Clear newline
    fgets(titles[*count], 50, stdin);
    titles[*count][strcspn(titles[*count], "\n")] = '\0'; // Remove newline

    printf("Enter price: ");
    scanf("%f", &prices[*count]);

    printf("Enter quantity: ");
    scanf("%d", &quantities[*count]);

    (*count)++;
    printf("Book added successfully!\n");
}

// Function to process a sale
void processSale(int isbns[], int quantities[], int count) {
    int isbn, qtySold;
    printf("Enter ISBN of the book sold: ");
    scanf("%d", &isbn);

    int index = findBookByISBN(isbns, count, isbn);
    if (index == -1) {
        printf("Error: Book not found.\n");
        return;
    }

    printf("Enter quantity sold: ");
    scanf("%d", &qtySold);

    if (qtySold > quantities[index]) {
        printf("Error: Not enough stock available.\n");
    } else {
        quantities[index] -= qtySold;
        printf("Sale processed successfully! Remaining stock: %d\n", quantities[index]);
    }
}

// Function to generate a low-stock report
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int count) {
    int found = 0;
    printf("\n===== Low Stock Report (Quantity < 5) =====\n");
int i ;
    for (i = 0; i < count; i++) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("All books have sufficient stock.\n");
    }
}
