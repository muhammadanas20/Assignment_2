#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_CART 10

int getIntegerInput(const char* prompt);
struct Product {
    int code;
    int quantity;
    float price;
};

struct Cart {
    int code;
    int quantity;
    float total;
};
struct Product products[MAX_PRODUCTS] = {
    {1, 50, 100 },
    {2, 10, 200 },
    {3, 20, 300 },
    {4, 15, 150 },
    {5, 30, 50  }
};
struct Cart cart[MAX_CART];
int cartCount = 0;
char customerName[50];
char customerCNIC[20];

// Function prototypes
void getCustomerInfo();
void displayInventory();
void addToCart();
void updateInventory(int code, int quantity);
void showInvoice();

int main() {
    int choice;

    do {
        printf("\n=========== Supermarket Management System ===========\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Checkout and Print Invoice\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        int result = scanf("%d", &choice);
        if (result != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); 
            choice = 0; 
        } else {
            while (getchar() != '\n'); 
        }


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
                showInvoice();
                break;
            case 5:
                printf("Exiting the system. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5); 

    return 0;
} 


int getIntegerInput(const char* prompt) {
    int value;
    int result;
    printf("%s", prompt); 
    while (1) { 
        result = scanf("%d", &value);
        if (result == 1) {    
            while (getchar() != '\n'); 
            return value; 
        } else {     
            printf("Invalid input! Please enter a number: ");  
            while (getchar() != '\n'); 
        }
    }
}

// Function to get customer info
void getCustomerInfo() {
    printf("Enter Customer Name: ");
    fgets(customerName, 50, stdin);
    customerName[strcspn(customerName, "\n")] = '\0';

    printf("Enter Customer CNIC: ");
    scanf("%s", customerCNIC);
    
    while (getchar() != '\n'); 
    
    printf("Customer information saved successfully!\n");
}

// Function to display inventory 
void displayInventory(void) {
    printf("\n=========== Inventory ===========\n");
    printf("Code\tQuantity\tPrice\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%03d\t%5d\t\t%5.2f\n",
               products[i].code, products[i].quantity, products[i].price);
    }
}

// Function to add item to cart
void addToCart() {
    if (cartCount >= MAX_CART) {
        printf("Error: Cart is full! Cannot add more items.\n");
        return;
    }
    

    int code, qty, found = 0;
    
   
    code = getIntegerInput("Enter Product Code: ");

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].code == code) {
            found = 1;
            
            
            qty = getIntegerInput("Enter quantity to purchase: ");

            if (qty <= 0) { 
             printf("Error: Quantity must be a positive number.\n");
             return;
            }

            if (qty > products[i].quantity) {
                printf("Error: Only %d units available in stock.\n", products[i].quantity);
                return;
            }

            updateInventory(code, qty);

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

// Function to update inventory 
void updateInventory(int code, int quantity) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (products[i].code == code) {
            products[i].quantity -= quantity;
        }
    }
}


// Function to show invoice (was displayBill + showInvoice)
void showInvoice() {
    float total = 0.0, discount = 0.0, finalAmount;
    char promo[20];

    // --- Added check for empty cart ---
    if (cartCount == 0) {
        printf("\nYour cart is empty! Nothing to check out.\n");
        return;
    }

    printf("\n=========== Customer Invoice ===========\n");
    
    // --- Added check for customer info ---
    if (strlen(customerName) == 0) {
        printf("Customer Name: N/A\n");
        printf("CNIC: N/A\n");
    } else {
        printf("Customer Name: %s\n", customerName);
        printf("CNIC: %s\n", customerCNIC);
    }

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
    while (getchar() != '\n'); 

    if (strcmp(promo, "Eid2025") == 0) {
        discount = total * 0.25;
        printf("Promo code applied! 25%% discount applied.\n");
    } else {
        printf("No discount applied.\n");
    }

    finalAmount = total - discount;
    printf("Discount: %.2f\n", discount);
    printf("Final Amount to Pay: %.2f\n", finalAmount);
    
    printf("\nThank you for shopping! Checkout complete.\n");
    cartCount = 0;
}
