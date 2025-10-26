#include <stdio.h>

#define ROWS 3
#define COLS 3

// Bit flag positions
#define POWER_ON        1 << 0  // Bit 0
#define OVERLOAD        1 << 1  // Bit 1
#define MAINTENANCE     1 << 2  // Bit 2

// Function Prototypes
void updateSectorStatus(int grid[ROWS][COLS]);
void querySectorStatus(int grid[ROWS][COLS]);
void runSystemDiagnostic(int grid[ROWS][COLS]);
void displayMenu();

int main() {
    int grid[ROWS][COLS] = {0}; // Initialize all sectors to 0 (all bits off)
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runSystemDiagnostic(grid);
                break;
            case 4:
                printf("Exiting system... Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}

// Display menu
void displayMenu() {
    printf("\n========== IESCO Power Grid Monitoring ==========\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
}

// Function to update a sector's status using bitwise operations
void updateSectorStatus(int grid[ROWS][COLS]) {
    int row, col, flagChoice, action;

    printf("Enter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("Select Status Flag to Modify:\n");
    printf("1. Power ON/OFF\n");
    printf("2. Overload Warning\n");
    printf("3. Maintenance Required\n");
    printf("Enter choice: ");
    scanf("%d", &flagChoice);

    printf("1. Set Flag (Turn ON)\n");
    printf("2. Clear Flag (Turn OFF)\n");
    printf("Enter action: ");
    scanf("%d", &action);

    int flag = 0;
    switch (flagChoice) {
        case 1: flag = POWER_ON; break;
        case 2: flag = OVERLOAD; break;
        case 3: flag = MAINTENANCE; break;
        default: 
            printf("Invalid flag choice!\n");
            return;
    }

    if (action == 1)
        grid[row][col] |= flag;  // Set bit
    else if (action == 2)
        grid[row][col] &= ~flag; // Clear bit
    else {
        printf("Invalid action!\n");
        return;
    }

    printf("Sector (%d, %d) updated successfully!\n", row, col);
}

// Function to query a sector and display human-readable status
void querySectorStatus(int grid[ROWS][COLS]) {
    int row, col;
    printf("Enter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    int status = grid[row][col];

    printf("\n========== Sector (%d, %d) Status ==========\n", row, col);
    printf("Power Status: %s\n", (status & POWER_ON) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (status & OVERLOAD) ? "YES" : "NO");
    printf("Maintenance Required: %s\n", (status & MAINTENANCE) ? "YES" : "NO");
    printf("Binary Code: %03d (decimal %d)\n", status, status);
}

// Function to scan the entire grid and count overloaded and maintenance sectors
void runSystemDiagnostic(int grid[ROWS][COLS]) {
    int overloadCount = 0, maintenanceCount = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] & OVERLOAD)
                overloadCount++;
            if (grid[i][j] & MAINTENANCE)
                maintenanceCount++;
        }
    }

    printf("\n========== System Diagnostic Report ==========\n");
    printf("Total Sectors: %d\n", ROWS * COLS);
    printf("Overloaded Sectors: %d\n", overloadCount);
    printf("Maintenance Required: %d\n", maintenanceCount);
}
