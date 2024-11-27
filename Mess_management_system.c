/*
PROJECT NAME : Mess Management system
GROUP NO: 12
BATCH : I1+I2 
GROUP MEMBERS: Sanyogita Chavan - UIT2023815
               Sakshi Chemte - UIT2023818
               Shradha Magar - UIT2023839 
               Aishwarya Marshettiwar - UIT2023842
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define structures
typedef struct User {
    char id[20];             // User ID (alphanumeric allowed)
    char name[50];           // User name
    int balance;             // User balance (whole number)
    int mealCount;           // Number of meals recorded for the user
    char feedback[100];      // Feedback provided by the user
    struct User* next;       // Pointer to the next user (used for linked list)
} User;

typedef struct Feedback {
    char message[100];       // Feedback message
    struct Feedback* next;   // Pointer to the next feedback message (used for linked list)
} Feedback;

// Function prototypes
void menu();                             // Main menu for user interactions
void addUser(User** userList);           // Add a new user to the system
void removeUser(User** userList);        // Remove a user from the system
void recordMeal(User* userList);         // Record a meal for a user and update balance
void displayUsers(User* userList);       // Display all users
void generateReports(User* userList);    // Generate reports on meals and revenue
void addFeedback(Feedback** feedbackList); // Add feedback to the system
void viewFeedback(Feedback* feedbackList); // View all feedback messages

int isValidUserId(const char* id);       // Validate a user ID
int isValidBalance(int balance);         // Validate a user's balance
User* findUserById(User* userList, const char* id); // Find a user by ID
int isUniqueUserId(User* userList, const char* id); // Check if the user ID is unique

// Driver function
int main() {
    menu(); // Start the program by displaying the main menu
    return 0;
}

// Main menu function
void menu() {
    User* userList = NULL;         // Initialize the user linked list
    Feedback* feedbackList = NULL; // Initialize the feedback linked list
    int choice;

    do {
        // Display menu options
        printf("\n--- Mess Management System ---\n");
        printf("1. Add User\n");
        printf("2. Remove User\n");
        printf("3. Record Meal\n");
        printf("4. Display Users\n");
        printf("5. Generate Reports\n");
        printf("6. Add Feedback\n");
        printf("7. View Feedback\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        // Perform actions based on user choice
        switch (choice) {
            case 1: addUser(&userList); break;        // Add a user
            case 2: removeUser(&userList); break;     // Remove a user
            case 3: recordMeal(userList); break;      // Record a meal
            case 4: displayUsers(userList); break;    // Display all users
            case 5: generateReports(userList); break; // Generate reports
            case 6: addFeedback(&feedbackList); break; // Add feedback
            case 7: viewFeedback(feedbackList); break; // View feedback
            case 8: printf("Exiting...\n"); break;    // Exit the program
            default: printf("Invalid choice. Try again.\n"); // Handle invalid choices
        }
    } while (choice != 8);
}

// Function to validate User ID
int isValidUserId(const char* id) {
    if (id == NULL || strlen(id) == 0) {
        return 0; // ID is empty
    }

    // Check if the ID contains only alphanumeric characters
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isalnum(id[i])) {
            return 0; // Invalid character found
        }
    }
    
    // Ensure ID does not start with zero
    if (id[0] == '0') {
        return 0;
    }

    return 1; // Valid ID
}

// Function to check if balance is valid
int isValidBalance(int balance) {
    return balance >= 0; // Balance must be non-negative
}

// Function to check if User ID is unique
int isUniqueUserId(User* userList, const char* id) {
    User* temp = userList;
    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            return 0; // ID already exists
        }
        temp = temp->next;
    }
    return 1; // ID is unique
}

// Function to add a user
void addUser(User** userList) {
    User* newUser = (User*)malloc(sizeof(User)); // Allocate memory for a new user
    char userId[20];

    // Input and validate user ID
    do {
        printf("Enter User ID: ");
        scanf("%s", userId);

        if (!isValidUserId(userId)) {
            printf("Invalid User ID. Try again.\n");
        } else if (!isUniqueUserId(*userList, userId)) {
            printf("User ID already exists. Please choose a different ID.\n");
        } else {
            strcpy(newUser->id, userId);
            break;
        }
    } while (1);

    // Input user name
    getchar(); // Consume newline
    printf("Enter User Name: ");
    fgets(newUser->name, sizeof(newUser->name), stdin);
    newUser->name[strcspn(newUser->name, "\n")] = '\0'; // Remove trailing newline

    // Initialize other fields
    newUser->balance = 0;
    newUser->mealCount = 0;
    newUser->feedback[0] = '\0';
    newUser->next = *userList;
    *userList = newUser;

    printf("User added successfully.\n");
}

// Function to find a user by ID
User* findUserById(User* userList, const char* id) {
    User* temp = userList;
    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            return temp; // Found the user
        }
        temp = temp->next;
    }
    return NULL; // User not found
}

// Function to remove a user
void removeUser(User** userList) {
    char userId[20];
    printf("Enter User ID to remove: ");
    scanf("%s", userId);

    User* temp = *userList;
    User* prev = NULL;

    // Find the user in the linked list
    while (temp && strcmp(temp->id, userId) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("User not found.\n");
        return;
    }

    // Remove the user from the list
    if (prev) {
        prev->next = temp->next;
    } else {
        *userList = temp->next;
    }

    free(temp); // Free the memory
    printf("User removed successfully.\n");
}

// Function to record a meal
void recordMeal(User* userList) {
    char userId[20];
    printf("Enter User ID to record meal: ");
    scanf("%s", userId);

    User* user = findUserById(userList, userId);
    if (!user) {
        printf("User not found.\n");
        return;
    }

    int mealCharge = 70; // Flat charge for each meal
    user->balance += mealCharge; // Update balance
    user->mealCount++; // Increment meal count
    printf("Meal recorded for %s. Charge of ₹70 added to balance.\n", user->name);
}

// Function to display users
void displayUsers(User* userList) {
    if (!userList) {
        printf("No users to display.\n");
        return;
    }

    printf("\n--- User List ---\n");
    User* temp = userList;
    while (temp) {
        printf("ID: %s\t Name: %s\t Balance: ₹%d \t Meals: %d\n",
               temp->id, temp->name, temp->balance, temp->mealCount);
        temp = temp->next;
    }
}

// Function to generate reports
void generateReports(User* userList) {
    if (!userList) {
        printf("No data to generate reports.\n");
        return;
    }

    int totalMeals = 0;
    int totalRevenue = 0;

    printf("\n--- Report ---\n");
    printf("| ID        | Name               | Meals | Revenue |\n");
    printf("|-----------|--------------------|-------|---------|\n");

    User* temp = userList;
    while (temp) {
        totalMeals += temp->mealCount;
        totalRevenue += temp->balance;

        printf("| %-9s | %-18s | %-5d | ₹%-7d |\n", 
               temp->id, temp->name, temp->mealCount, temp->balance);
        temp = temp->next;
    }

    printf("\nTotal Meals: %d\n", totalMeals);
    printf("Total Revenue: ₹%d\n", totalRevenue);
}

// Function to add feedback
void addFeedback(Feedback** feedbackList) {
    Feedback* newFeedback = (Feedback*)malloc(sizeof(Feedback));
    printf("Enter your feedback: ");
    getchar(); // Consume newline left by previous input
    fgets(newFeedback->message, sizeof(newFeedback->message), stdin);
    newFeedback->message[strcspn(newFeedback->message, "\n")] = '\0'; // Remove trailing newline

    newFeedback->next = *feedbackList;
    *feedbackList = newFeedback;

    printf("Thank you for your feedback.\n");
}

// Function to view feedback
void viewFeedback(Feedback* feedbackList) {
    if (!feedbackList) {
        printf("No feedback to display.\n");
        return;
    }

    printf("\n--- Feedback ---\n");
    Feedback* temp = feedbackList;
    while (temp) {
        printf("- %s\n", temp->message);
        temp = temp->next;
    }
}
/*
OUTPUT
--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: uit2023898
Enter User Name: ruhii
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 39
Enter User Name: sonal  
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 90
Enter User Name: minal
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 99
Enter User Name: sumit
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 60
Enter User Name: rahul
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 56
Enter User Name: shreya
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 76
Enter User Name: pranjal
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 1
Enter User ID: 56
User ID already exists. Please choose a different ID.
Enter User ID: 65
Enter User Name: mahesh
User added successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 2
Enter User ID to remove: 56
User removed successfully.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 4

--- User List ---
ID: 65   Name: mahesh    Balance: ₹0     Meals: 0
ID: 76   Name: pranjal   Balance: ₹0     Meals: 0
ID: 60   Name: rahul     Balance: ₹0     Meals: 0
ID: 99   Name: sumit     Balance: ₹0     Meals: 0
ID: 90   Name: minal     Balance: ₹0     Meals: 0
ID: 39   Name: sonal     Balance: ₹0     Meals: 0
ID: uit2023898   Name: ruhii     Balance: ₹0     Meals: 0

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 3
Enter User ID to record meal: 65
Meal recorded for mahesh. Charge of ₹70 added to balance.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 3
Enter User ID to record meal: 76
Meal recorded for pranjal. Charge of ₹70 added to balance.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 3
Enter User ID to record meal: 39
Meal recorded for sonal. Charge of ₹70 added to balance.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 3
Enter User ID to record meal: 90
Meal recorded for minal. Charge of ₹70 added to balance.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 3
Enter User ID to record meal: 99
Meal recorded for sumit. Charge of ₹70 added to balance.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 5

--- Report ---
| ID        | Name               | Meals | Revenue |
|-----------|--------------------|-------|---------|
| 65        | mahesh             | 1     | ₹70      |
| 76        | pranjal            | 1     | ₹70      |
| 60        | rahul              | 0     | ₹0       |
| 99        | sumit              | 1     | ₹70      |
| 90        | minal              | 1     | ₹70      |
| 39        | sonal              | 1     | ₹70      |
| uit2023898 | ruhii              | 0     | ₹0       |

Total Meals: 5
Total Revenue: ₹350

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 6
Enter your feedback: the meal was good & tasty           
Thank you for your feedback.

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 7

--- Feedback ---
- the meal was good & tasty

--- Mess Management System ---
1. Add User
2. Remove User
3. Record Meal
4. Display Users
5. Generate Reports
6. Add Feedback
7. View Feedback
8. Exit
Enter choice: 8
Exiting...
*/
