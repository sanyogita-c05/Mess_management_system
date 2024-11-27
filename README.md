# Mess Management System README  

This project is a **C-based Mess Management System**, designed to streamline the operations of a mess by efficiently managing user details, meal records, and feedback collection. It provides an intuitive interface for mess administrators to handle day-to-day tasks with ease.  

---

## Features  

- **User Management**: Add, remove, and display users.  
- **Meal Tracking**: Record meals for users and update their balances.  
- **Report Generation**: Summarize total meals served and revenue generated.  
- **Feedback Collection**: Allow users to submit feedback about their mess experience.  
- **Customizable Structure**: Modify key components like meal charges easily.  

---

## Technologies Used  

- **C Programming Language**: Core functionality implemented in C.  
- **Standard Libraries**: Used for input/output operations, memory allocation, and string manipulation.  

---

## How It Works  

### Main Functions  

1. **Add User**  
   - Collects user details (ID, name) and initializes their balance and meal count.  
   - Ensures the ID is unique and valid.
   - 

2. **Remove User**  
   - Deletes a user from the system by matching their ID.
   -  

3. **Record Meal**  
   - Updates a user's meal count and balance by adding a flat meal charge (₹70 by default).
   - 

4. **Display Users**  
   - Lists all registered users with their details: ID, name, balance, and meals consumed.
   - 

5. **Generate Reports**  
   - Summarizes total meals served and revenue generated. Displays results in a tabular format.
   -  

6. **Add Feedback**  
   - Allows users to submit feedback messages.
   -   

7. **View Feedback**  
   - Displays all feedback messages collected.
   - 

8. **Exit**  
   - Ends the program.  

---

## Prerequisites  

- **C Compiler**: GCC or any other standard C compiler.  
- **Basic Knowledge of C**: Familiarity with pointers, structures, and linked lists is beneficial.  

---

## Example Workflow  

1. **Add a User**  
   - Input a unique user ID (e.g., `uit2023898`) and their name (`Rahul`).  
   - User gets added successfully.  

2. **Record a Meal**  
   - Select a user by their ID (e.g., `uit2023898`).  
   - The meal count increases, and the balance gets updated by ₹70.  

3. **Generate Reports**  
   - View total meals served and revenue generated in a clean tabular format.  

4. **Feedback Submission**  
   - Submit feedback like "The food quality is excellent."  
   - View all feedback in the system.
  
   - Here is a sample example of mess management system.
   - ![Screenshot 2024-11-27 123018](https://github.com/user-attachments/assets/8bdfb2bd-9f02-4e8d-bf2c-1950b8811cf7)


---

## Customization  

- **Update Meal Charges**  
  Modify the `mealCharge` variable in the `recordMeal` function.  

- **Expand User Details**  
  Add more fields to the `User` structure for additional information like contact number or email.  

- **Feedback Management**  
  Enhance the feedback system to include ratings alongside comments.  

---

## Future Enhancements  

- Introduce **Monthly Statements** for each user.  
- Add **Meal Plans** for pre-defined discounts on bulk meals.  
- Implement **Database Integration** for persistent storage of data.  

---

## Thank You  

We hope the Mess Management System adds efficiency to your operations. 🚀  
Feel free to customize and expand it as per your requirements!  

*Happy Managing! 🌟*
