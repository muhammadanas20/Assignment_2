#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_CART 10

// Structure to store product info
struct Product {
    int code;
    int quantity;
    float price;
    char name[20];
};

// Structure to store cart items
struct Cart {
    int code;
    int quantity;
    float total;
};

// Global arrays
struct Product products[MAX_PRODUCTS] = {
    {1, 50, 100, "Milk"},
    {2, 10, 200, "Rice"},
    {3, 20, 300, "Sugar"},
    {4, 15, 150, "Oil"},
    {5, 30, 50, "Tea"}
};

struct Cart cart[MAX_CART];
int cartCount = 0;

// Customer info
char customerName[50];
char customerCNIC[20];

// Function prototypes
void getCustomerInfo();
void displayInventory();
void addToCart();
void updateInventory(int code, int quantity);
void displayBill();
void showInvoice();

int main() {
    int choice;

    do {
        printf("\n=========== Supermarket Management System ===========\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getCustomerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                addToCart();
                break;
            case 4:
                displayBill();
                break;
            case 5:
                showInvoice();
                break;
            case 6:
                printf("Exiting the system. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}

// Function to get customer info
void getCustomerInfo() {
    printf("Enter Customer Name: ");
    getchar(); // clear buffer
    fgets(customerName, 50, stdin);
    customerName[strcspn(customerName, "\n")] = '\0';

    printf("Enter Customer CNIC: ");
    scanf("%s", customerCNIC);
    printf("Customer information saved successfully!\n");
}

// Function to display inventory
void displayInventory() {
    printf("\n=========== Inventory ===========\n");
    printf("Code\tProduct\t\tQuantity\tPrice\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%03d\t%-10s\t%5d\t\t%.2f\n",
               products[i].code, products[i].name, products[i].quantity, products[i].price);
    }
}

// Function to add item to cart
void addToCart() {
    int code, qty, found = 0;
    printf("Enter Product Code: ");
    scanf("%d", &code);

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].code == code) {
            found = 1;
            printf("Enter quantity to purchase: ");
            scanf("%d", &qty);

            if (qty > products[i].quantity) {
                printf("Error: Only %d units available in stock.\n", products[i].quantity);
                return;
            }

            // Update inventory
            updateInventory(code, qty);

            // Add to cart
            cart[cartCount].code = code;
            cart[cartCount].quantity = qty;
            cart[cartCount].total = qty * products[i].price;
            cartCount++;

            printf("Item added to cart successfully!\n");
            return;
        }
    }

    if (!found) {
        printf("Error: Product not found.\n");
    }
}

// Function to update inventory after purchase
void updateInventory(int code, int quantity) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].code == code) {
            products[i].quantity -= quantity;
        }
    }
}

// Function to display total bill
void displayBill() {
    float total = 0.0, discount = 0.0, finalAmount;
    char promo[20];

    printf("\n=========== Bill Summary ===========\n");
    printf("Code\tQuantity\tTotal\n");

    for (int i = 0; i < cartCount; i++) {
        printf("%03d\t%5d\t\t%.2f\n", cart[i].code, cart[i].quantity, cart[i].total);
        total += cart[i].total;
    }

    printf("------------------------------------\n");
    printf("Total Bill: %.2f\n", total);

    printf("Do you have a promo code? (Enter code or 'no'): ");
    scanf("%s", promo);

    if (strcmp(promo, "Eid2025") == 0) {
        discount = total * 0.25;
        printf("Promo code applied! You got a 25%% discount.\n");
    } else {
        printf("No discount applied.\n");
    }

    finalAmount = total - discount;
    printf("Discount: %.2f\n", discount);
    printf("Final Bill: %.2f\n", finalAmount);
}

// Function to show invoice
void showInvoice() {
    float total = 0.0, discount = 0.0, finalAmount;
    char promo[20];

    printf("\n=========== Customer Invoice ===========\n");
    printf("Customer Name: %s\n", customerName);
    printf("CNIC: %s\n", customerCNIC);

    printf("\nPurchased Items:\n");
    printf("Code\tQuantity\tTotal\n");
    for (int i = 0; i < cartCount; i++) {
        printf("%03d\t%5d\t\t%.2f\n", cart[i].code, cart[i].quantity, cart[i].total);
        total += cart[i].total;
    }

    printf("------------------------------------\n");
    printf("Total Bill: %.2f\n", total);

    printf("Do you have a promo code? (Enter code or 'no'): ");
    scanf("%s", promo);

    if (strcmp(promo, "Eid2025") == 0) {
        discount = total * 0.25;
        printf("Promo code applied! 25%% discount applied.\n");
    }

    finalAmount = total - discount;
    printf("Discount: %.2f\n", discount);
    printf("Final Amount to Pay: %.2f\n", finalAmount);
}
