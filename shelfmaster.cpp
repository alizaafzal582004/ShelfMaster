#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>  // Include for file handling

using namespace std;

// Structure for Book
struct Book {
    int id;
    char title[100];
    char author[100];
    struct Book* next;
};

// Structure for Student
struct Student {
    char name[100];
    char email[100];
    int issuedBookId;
};

vector<Student> students; // To store issued student details

// Function to insert a book into the linked list
void insertBook(struct Book** head, int id, const char* title, const char* author) {
    struct Book* newBook = new Book;
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->next = *head;
    *head = newBook;
}

// Function to display all books
void displayBooks(struct Book* head) {
    if (!head) {
        cout << "No books in the list.\n";
        return;
    }
    cout << "*************** Books Available: ****************\n\n";
    int count = 1;
    while (head) {
        cout << "Book " << count++ << endl;
        cout << "Book Title: " << head->title << endl;
        cout << "Name of Author: " << head->author << endl;
        cout << "Book ID: " << head->id << endl;
        cout << "_________________________________________________\n\n";
        head = head->next;
    }
}

// Function to save student details to a file
void saveStudentToFile(const Student& student) {
    ofstream outFile;
    outFile.open("readme.txt", ios::app); // Open file in append mode
    if (outFile.is_open()) {
        outFile << "Student Name: " << student.name << endl;
        outFile << "Student Email: " << student.email << endl;
        outFile << "Issued Book ID: " << student.issuedBookId << endl;
        outFile << "---------------------------------------\n";
        outFile.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

// Function to issue a book
void issueBook(struct Book* head) {
    if (!head) {
        cout << "No books available to issue.\n";
        return;
    }

    displayBooks(head);

    int bookId;
    cout << "Enter the ID of the book you want to issue: ";
    cin >> bookId;

    struct Book* temp = head;
    while (temp) {
        if (temp->id == bookId) {
            cout << "\nBook found: \n";
            cout << "Book Title: " << temp->title << endl;
            cout << "Name of Author: " << temp->author << endl;
            cout << "Book ID: " << temp->id << endl;

            Student student;
            cout << "\nEnter your name: ";
            cin.ignore();
            cin.getline(student.name, 100);
            cout << "Enter your email: ";
            cin.getline(student.email, 100);
            student.issuedBookId = bookId;
            students.push_back(student);

            // Save student details to file
            saveStudentToFile(student);

            cout << "\nBook issued successfully!\n";
            cout << "Student Details:\n";
            cout << "Name: " << student.name << endl;
            cout << "Email: " << student.email << endl;
            cout << "Issued Book ID: " << student.issuedBookId << endl;

            return;
        }
        temp = temp->next;
    }

    cout << "\nBook ID not found.\n";
}

// Function to return a book
void returnBook(struct Book* head) {
    if (!head) {
        cout << "No books available to return.\n";
        return;
    }

    int bookId;
    cout << "Enter the ID of the book you want to return: ";
    cin >> bookId;

    struct Book* temp = head;
    while (temp) {
        if (temp->id == bookId) {
            cout << "\nBook returned successfully!\n";
            cout << "Book Details:\n";
            cout << "Book Title: " << temp->title << endl;
            cout << "Name of Author: " << temp->author << endl;
            cout << "Book ID: " << temp->id << endl;

            for (auto it = students.begin(); it != students.end(); ++it) {
                if (it->issuedBookId == bookId) {
                    students.erase(it);
                    break;
                }
            }

            return;
        }
        temp = temp->next;
    }

    cout << "\nBook ID not found.\n";
}

// Function to display all students who have issued books
void displayStudents() {
    if (students.empty()) {
        cout << "No students have issued any books.\n";
        return;
    }

    cout << "*************** Students with Issued Books: ****************\n\n";
    int count = 1;
    for (const auto& student : students) {
        cout << "Student " << count++ << endl;
        cout << "Name: " << student.name << endl;
        cout << "Email: " << student.email << endl;
        cout << "Issued Book ID: " << student.issuedBookId << endl;
        cout << "_________________________________________________\n\n";
    }
}

// Function to sort the linked list using Bubble Sort
void bubbleSortBooks(struct Book** head) {
    if (!*head) return;

    bool swapped;
    struct Book* ptr1;
    struct Book* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->id > ptr1->next->id) {
                // Swap the data of the two nodes
                int tempId = ptr1->id;
                char tempTitle[100], tempAuthor[100];
                strcpy(tempTitle, ptr1->title);
                strcpy(tempAuthor, ptr1->author);

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->title, ptr1->next->title);
                strcpy(ptr1->author, ptr1->next->author);

                ptr1->next->id = tempId;
                strcpy(ptr1->next->title, tempTitle);
                strcpy(ptr1->next->author, tempAuthor);

                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    cout << "Books sorted successfully!\n";
}

// Function to display a greeting message
void displayGreeting() {
     cout << "\n\n";
    cout << "\t\t\t     ****************************************\n";
    cout << "\t\t\t     *                                      *\n";
    cout << "\t\t\t     *     ----------------------------     *\n";
    cout << "\t\t\t     *      WELCOME TO STUDENT LIBRARY      *\n";
    cout << "\t\t\t     *     ----------------------------     *\n";
    cout << "\t\t\t     ****************************************\n";
    cout << "\n\n";
}

int main() {
    struct Book* head = nullptr;

    // Insert 5 predefined books
    insertBook(&head, 105, "A Tale Of Two Cities", "Charles Dickens");
    insertBook(&head, 104, "Pride And Prejudice", "Jane Austen");
    insertBook(&head, 103, "The Alchemist", "Paulo Coelho");
    insertBook(&head, 102, "To Kill A Mockingbird", "Harper Lee");
    insertBook(&head, 101, "The Kite Runner", "Khaled Hosseini");

    // Display greeting message
    displayGreeting();

    int choice;

    do {
        cout << "\n\t\t\t*************************************************\n";
        cout << "\n\t\t\t\t      MAIN MENU: \n";
        cout << "\t\t\t\t     1. INSERT A BOOK\n";
        cout << "\t\t\t\t     2. DISPLAY BOOKS \n";
        cout << "\t\t\t\t     3. SORTED BOOKS\n";
        cout << "\t\t\t\t     4. ISSUE A BOOK\n";
        cout << "\t\t\t\t     5. RETURN A BOOK\n";
        cout << "\t\t\t\t     6. DISPLAY STUDENTS WITH ISSUED BOOKS\n";
        cout << "\t\t\t\t     7. EXIT\n";
        cout << "\n\t\t\t*************************************************\n";
        cout << "\n\t\t\t\t      Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                char title[100], author[100];
                do {
                    cout << "Enter Book ID: ";
                    cin >> id;
                    cin.ignore();
                    cout << "Enter Book Title: ";
                    cin.getline(title, 100);
                    cout << "Enter Book Author: ";
                    cin.getline(author, 100);
                    insertBook(&head, id, title, author);
                    cout << "Book inserted successfully!\n";

                    char addMore;
                    cout << "Do you want to add another book? (y/n): ";
                    cin >> addMore;
                    if (addMore == 'n' || addMore == 'N') {
                        break;
                    }
                } while (true);
                break;
            }
            case 2:
                displayBooks(head);
                break;
            case 3:
                bubbleSortBooks(&head);
                break;
            case 4:
                issueBook(head);
                break;
            case 5:
                returnBook(head);
                break;
            case 6:
                displayStudents();
                break;
            case 7:
                cout << "Thanks for visiting!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    // Free allocated memory
    struct Book* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
