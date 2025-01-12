#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100

typedef struct {
    char category[30];
    float amount;
    char type[10]; // "Income" or "Expense"
    char description[100];
} Transaction;

Transaction transactions[MAX_ENTRIES];
int transactionCount = 0;
float monthlyBudget = 0.0f;

// Function prototypes
void addTransaction();
void viewTransactions();
void calculateSavings();
void setMonthlyBudget();
void generateReport();

int main() {
    int choice;
    while (1) {
        printf("\n=== Personal Finance Manager ===\n");
        printf("1. Add Transaction\n");
        printf("2. View Transactions\n");
        printf("3. Calculate Savings\n");
        printf("4. Set Monthly Budget\n");
        printf("5. Generate Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                viewTransactions();
                break;
            case 3:
                calculateSavings();
                break;
            case 4:
                setMonthlyBudget();
                break;
            case 5:
                generateReport();
                break;
            case 6:
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void addTransaction() {
    if (transactionCount >= MAX_ENTRIES) {
        printf("Transaction limit reached!\n");
        return;
    }

    Transaction t;
    printf("Enter transaction type (Income/Expense): ");
    scanf("%s", t.type);
    printf("Enter category: ");
    scanf("%s", t.category);
    printf("Enter amount: ");
    scanf("%f", &t.amount);
    printf("Enter description: ");
    getchar(); // to clear the newline from buffer
    fgets(t.description, 100, stdin);
    t.description[strcspn(t.description, "\n")] = 0; // Remove trailing newline

    transactions[transactionCount++] = t;
    printf("Transaction added successfully!\n");
}

void viewTransactions() {
    if (transactionCount == 0) {
        printf("No transactions found!\n");
        return;
    }

    printf("\n--- Transactions ---\n");
    for (int i = 0; i < transactionCount; i++) {
        printf("%d. Type: %s, Category: %s, Amount: %.2f, Description: %s\n",
               i + 1, transactions[i].type, transactions[i].category, transactions[i].amount, transactions[i].description);
    }
}

void calculateSavings() {
    float totalIncome = 0.0f, totalExpense = 0.0f;

    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].type, "Income") == 0) {
            totalIncome += transactions[i].amount;
        } else if (strcmp(transactions[i].type, "Expense") == 0) {
            totalExpense += transactions[i].amount;
        }
    }

    printf("\n--- Savings Summary ---\n");
    printf("Total Income: %.2f\n", totalIncome);
    printf("Total Expense: %.2f\n", totalExpense);
    printf("Savings: %.2f\n", totalIncome - totalExpense);

    if (monthlyBudget > 0.0f) {
        printf("Monthly Budget: %.2f\n", monthlyBudget);
        printf("Remaining Budget: %.2f\n", monthlyBudget - totalExpense);
    }
}

void setMonthlyBudget() {
    printf("Enter your monthly budget: ");
    scanf("%f", &monthlyBudget);
    printf("Monthly budget set to %.2f\n", monthlyBudget);
}

void generateReport() {
    FILE *file = fopen("finance_report.txt", "w");
    if (!file) {
        printf("Error: Unable to create report file!\n");
        return;
    }

    fprintf(file, "--- Personal Finance Report ---\n");
    for (int i = 0; i < transactionCount; i++) {
        fprintf(file, "%d. Type: %s, Category: %s, Amount: %.2f, Description: %s\n",
                i + 1, transactions[i].type, transactions[i].category, transactions[i].amount, transactions[i].description);
    }

    fprintf(file, "\n--- Summary ---\n");
    float totalIncome = 0.0f, totalExpense = 0.0f;

    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].type, "Income") == 0) {
            totalIncome += transactions[i].amount;
        } else if (strcmp(transactions[i].type, "Expense") == 0) {
            totalExpense += transactions[i].amount;
        }
    }

    fprintf(file, "Total Income: %.2f\n", totalIncome);
    fprintf(file, "Total Expense: %.2f\n", totalExpense);
    fprintf(file, "Savings: %.2f\n", totalIncome - totalExpense);

    fclose(file);
    printf("Report generated successfully as 'finance_report.txt'.\n");
}
