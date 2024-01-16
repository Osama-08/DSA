#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<fstream>
#include <limits>
#include <ctime>
#include <chrono>


#include <sstream>
using namespace std;

class library
{
public:
	library *next, *previous;
	library *S_next, *S_previous;
	library *B_next, *B_previous;


	string  title, author, edition, publication;
	int isbn;
	string name, section, semester, password;
	int enrollment;
	  string borrowedDateTime; // Add this member
      bool isBorrowed;
      int borrowDays ;
      int borrowedFrequency ;
	

	library() 
	{
		isbn = 0;
		title = "0";
		borrowedDateTime = " ";
		author = "0";
		edition = "0";
		publication = "0";
       
		section = "0";
		semester = "0";
		password = "0";
        borrowDays = 0;
		enrollment = 0;
        isBorrowed = false;
        borrowedFrequency = 0;
	}

	~library()
	{
		
	}

};


library *head = NULL;
library *tail = NULL;

library *S_head = NULL;
library *S_tail = NULL;


library *B_head = NULL;
library *B_tail = NULL;

void addbook() {
    library* addbooks = new library;

    system("cls");
    cout << endl << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\n\n\t\t\t\t\t\t   ADD BOOKS " << endl << endl;

    cin.ignore();

    cout << "\t\t\t\t\tENTER ISBN : ";
    cin >> addbooks->isbn;
    cout << "\t\t\t\t\tENTER TITLE : ";
    cin >> addbooks->title;
    cout << "\t\t\t\t\tENTER AUTHOR : ";
    cin >> addbooks->author;
    cout << "\t\t\t\t\tENTER EDITION : ";
    cin >> addbooks->edition;
    cout << "\t\t\t\t\tENTER PUBLICATION : ";
    cin >> addbooks->publication;
    cout << endl << endl;

    if (head == NULL) {
        head = addbooks;
        addbooks->next = addbooks->previous = NULL;
    } else {
        library* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }

        tail->next = addbooks;
        addbooks->previous = tail;
        addbooks->next = NULL;
    }

    ofstream booksFile("books.txt", ios::trunc);  // Open the file in truncation mode

library* temp = head;
while (temp != NULL) {
    booksFile << temp->isbn << " " << temp->title << " " << temp->author << " " << temp->edition << " " << temp->publication << endl;
    temp = temp->next;
}

booksFile.close();


    cout << "\t\t\t\t\tBOOK ADDED SUCCESSFULLY! \n\n\t\t\t\t\tPress any key to continue..." << endl;
    _getch();
}

void loadStudentsFromFile() {
    ifstream studentsFile("students.txt");
    if (!studentsFile) {
        // File does not exist or cannot be opened, handle accordingly
        return;
    }

    while (!studentsFile.eof()) {
        library* temp = new library;
        studentsFile >> temp->name >> temp->enrollment >> temp->section >> temp->semester >> temp->password;

        if (S_head == NULL) {
            S_head = S_tail = temp;
            temp->S_next = temp->S_previous = NULL;
        } else {
            S_tail->S_next = temp;
            temp->S_previous = S_tail;
            S_tail = temp;
            temp->S_next = NULL;
        }
    }

    studentsFile.close();
}
void loadBorrowData() {
    ifstream inFile("borrowed_books.txt");
    if (!inFile) {
        cerr << "Error: Unable to open borrowed_books.txt for reading." << endl;
        return;
    }

    while (inFile.peek() != EOF) {
        library* borrowedBook = new library;
        inFile >> borrowedBook->isbn >> borrowedBook->enrollment >> borrowedBook->borrowedDateTime
               >> borrowedBook->title >> borrowedBook->author >> borrowedBook->edition >> borrowedBook->publication
               >> borrowedBook->borrowDays>>borrowedBook->isBorrowed;

        // Add borrowed book to the global linked list directly
        if (B_head == NULL) {
            B_head = B_tail = borrowedBook;
            borrowedBook->B_next = borrowedBook->B_previous = NULL;
        } else {
            B_tail->B_next = borrowedBook;
            borrowedBook->B_previous = B_tail;
            B_tail = borrowedBook;
            borrowedBook->B_next = NULL;
        }
    }

    inFile.close();
}


void updateStudentsFile() {
    ofstream studentsFile("students.txt");
    if (!studentsFile) {
        // File cannot be created or opened for writing, handle accordingly
        return;
    }

    library* temp = S_head;
    while (temp != NULL) {
        studentsFile << temp->name << " " << temp->enrollment << " " << temp->section << " " << temp->semester << " " << temp->password << endl;
        temp = temp->S_next;
    }

    studentsFile.close();
}

void addStudentData() {
    system("cls");
    cout << endl << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\t\t\t\t\t   || STUDENT - INTERFACE ||" << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl << endl;
    library* temp = new library;

    cin.ignore();
    cout << "\t\t\t\t\tEnter student Name     :";
    cin >> temp->name;

    cout << "\t\t\t\t\tEnter student Roll#    :";
    cin >> temp->enrollment;

    cout << "\t\t\t\t\tEnter student Section  :";
    cin >> temp->section;

    cout << "\t\t\t\t\tEnter student Semester :";
    cin >> temp->semester;

    cout << "\t\t\t\t\tEnter student Password :";
    cin >> temp->password;
    cout << endl << endl;

    if (S_head == NULL) {
        S_head = S_tail = temp;
        temp->S_next = temp->S_previous = NULL;
    } else {
        S_tail->S_next = temp;
        S_tail = temp;
        temp->S_previous = S_tail;
        temp->S_next = NULL;
    }

    // Update the students.txt file after adding a student
    updateStudentsFile();

    cout << "\t\t\t\t\tStudent ADDED SUCCESSFULLY! \n\n\t\t\t\t\tPress any key to continue..." << endl << endl;
    _getch();
}


bool isBookBorrowed(int isbn, int regno) {
    std::ifstream inFile("borrowed_books.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open borrowed_books.txt for reading." << std::endl;
        return false;
    }

    int tempIsbn, tempRegno, tempDays, tempIsBorrowed;
    std::string tempTitle, tempAuthor, tempEdition, tempPublication, tempBorrowedDateTime;

    while (inFile >> tempIsbn >> tempRegno >> tempBorrowedDateTime >> tempTitle >> tempAuthor >> tempEdition >> tempPublication >> tempDays >> tempIsBorrowed) {
       

        if (tempIsbn == isbn) {
            inFile.close();
            return true; // Book is currently borrowed
        }

        // Skip the rest of the book information
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inFile.close();
    return false; // Book is not borrowed
}

long long convertToSeconds(const char* dateTime) {
    struct tm tm = {};
    stringstream ss(dateTime);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    time_t t = mktime(&tm);
    return static_cast<long long>(t);
}

// Function to get current date and time
string getCurrentDateTime() {
    time_t now = time(0);
    tm* tstruct = localtime(&now);

    if (tstruct == nullptr) {
        cerr << "Error: Unable to get local time." << endl;
        return "";
    }

    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tstruct);
    return buf;
}

void printLibraryList(library* list) {
    while (list != nullptr) {
        cout << list->isbn << " ";
        list = list->next;
    }
    cout << endl;
}


void saveBorrowedToFile(library* book, int regno) {
    ofstream outFile("borrowed_books.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open borrowed_books.txt for writing." << endl;
        return;
    }

    outFile << book->isbn << " " << regno << " " << book->borrowedDateTime << " "
            << book->title << " " << book->author << " " << book->edition << " " << book->publication
            << " " << book->borrowDays << " " << book->isBorrowed << endl;

    outFile.close();
}

// Function to update borrowed_books.txt file
void updateBorrowedFile() {
    ofstream outFile("borrowed_books.txt");
    if (!outFile) {
        cerr << "Error: Unable to open borrowed_books.txt for writing." << endl;
        return;
    }

    library* current = B_head;
    while (current != nullptr) {
        outFile << current->isbn << " " << current->enrollment << " " << current->borrowedDateTime << " "
                << current->title << " " << current->author << " " << current->edition << " " << current->publication
                << " " << current->borrowDays << " " << current->isBorrowed << endl;

        current = current->B_next;
    }

    outFile.close();
}

void updateBooksFile() {
    ofstream outFile("books.txt");
    if (!outFile) {
        cerr << "Error: Unable to open books.txt for writing." << endl;
        return;
    }

    library* current = head;
    while (current != nullptr) {
        outFile << current->isbn << " " << current->title << " " << current->author
                << " " << current->edition << " " << current->publication << " "
                << current->borrowedFrequency << endl;

        current = current->next;
    }

    outFile.close();
}
void allTimeFavoriteBooks(library* head) {
    system("cls");
    cout << "\n\t\t\t\t\tAll-Time Favorite Books\n";
    cout << "\t\t\t\t\t------------------------\n\n";

    library* current = head;

    if (current == nullptr) {
        cout << "\t\t\t\t\tLibrary is empty.\n";
    } else {
        cout << "\t\t\t\t\tList of All-Time Favorite Books:\n\n";
        while (current != nullptr) {
            if (current->borrowedFrequency > 0) {
                cout << "\t\t\t\t\tISBN: " << current->isbn << "\n";
                cout << "\t\t\t\t\tTitle: " << current->title << "\n";
                cout << "\t\t\t\t\tAuthor: " << current->author << "\n";
                cout << "\t\t\t\t\tEdition: " << current->edition << "\n";
                cout << "\t\t\t\t\tPublication: " << current->publication << "\n";
                cout << "\t\t\t\t\tBorrowed Frequency: " << current->borrowedFrequency << "\n\n";
            }

            current = current->next;
        }
    }

    cout << "\t\t\t\t\tPress any key to continue . . .";
    _getch();
    system("cls");
}


// Function to borrow books
void borrowBooks(library*& S_head) {
    int isbn;
    int choice;
    int maxAttempts = 3;
    int currentAttempt = 0;

    while (currentAttempt < maxAttempts) {
        system("cls");
        cout << "\n\t\t\t\t\tBorrow Books\n";
        cout << "\t\t\t\t\t-----------------\n\n";
        cout << "\t\t\t\t\tPlease enter Book ISBN: ";
        cin >> isbn;

        library* current = head;
        library* per = nullptr;  // Initialize per to nullptr

        // Print linked list during search for debugging
        cout << "Linked List during search: ";
        printLibraryList(head);

        while (current != nullptr && current->isbn != isbn) {
            per = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "\n\t\t\t\t\tBook not found!\n";
        } else {
            // Check if the book is already borrowed
            if (isBookBorrowed(isbn, S_head->enrollment)) {
                cout << "\n\t\t\t\t\tBook is already borrowed.\n";
                break;
            } else {
                cout << "\n\t\t\t\t\tBook Found!\n";
                cout << "\t\t\t\t\tDo you want to borrow this book? (yes[1], no[2]): ";
                cin >> choice;

                if (choice == 1) {
                    // Get user input for how many days they want to borrow the book
                    int borrowdays;
                    cout << "\n\t\t\t\t\tEnter the number of days you want to borrow the book: ";
                    cin >> borrowdays;

                    // Calculate borrowing time in seconds
                    // long long borrowTimeSeconds = convertToSeconds(getCurrentDateTime().c_str());

                    // Set the borrowing time for the book
                    current->borrowDays = borrowdays;
                    current->borrowedDateTime = getCurrentDateTime();
                    current->borrowedFrequency++;
                    


                    // Create a new node for the borrowed book
                    library* boro = new library;
                    boro->isbn = current->isbn;
                    boro->enrollment = S_head->enrollment;
                    boro->title = current->title;
                    boro->author = current->author;
                    boro->edition = current->edition;
                    boro->publication = current->publication;
                    boro->borrowDays = current->borrowDays;
                    boro->borrowedDateTime = current->borrowedDateTime;
                    boro->isBorrowed = 1;
            

                    // Add the borrowed book to the borrowed books linked list
                    if (B_head == nullptr) {
                        B_head = B_tail = boro;
                        boro->B_next = boro->B_previous = nullptr;
                    } else {
                        B_tail->B_next = boro;
                        boro->B_previous = B_tail;
                        B_tail = boro;
                        boro->B_next = nullptr;
                    }

                    // Save the borrowed book information to the file
                    int regno = S_head->enrollment;
                    string borrowDate = getCurrentDateTime();
                    saveBorrowedToFile(boro, regno);

                    // Print statements for debugging
                    cout << "Linked List after borrowing: ";
                    printLibraryList(head);

                    cout << "\n\t\t\t\t\tProcessing...\n";
                    Sleep(2000);
                    cout << "\t\t\t\t\tBook borrowed successfully.\n";
                    break;
                } else {
                    cout << "\n\t\t\t\t\tBook not borrowed.\n";
                    break;
                }
            }
        }

        currentAttempt++;

        if (currentAttempt < maxAttempts) {
            cout << "\n\t\t\t\t\tInvalid ISBN. Remaining attempts: " << maxAttempts - currentAttempt << endl;
            cout << "\t\t\t\t\tPress any key to try again..." << endl;
            _getch();
        }
    }

    // Print statements for debugging
    cout << "\n\t\t\t\t\tPress any key to continue . . .";
    _getch();
    system("cls");
}

// Function to return books
void returnBooks(library*& S_head) {
    int isbn;

    cout << "\n\t\t\t\t\tReturn Books\n";
    cout << "\t\t\t\t\t-----------------\n\n";
    cout << "\t\t\t\t\tPlease enter Book ISBN: ";
    cin >> isbn;

    library* current = B_head;
    library* prev = nullptr;

    while (current != nullptr && current->isbn != isbn) {
        prev = current;
        current = current->B_next;
    }

    if (current == nullptr) {
        cout << "\n\t\t\t\t\tBook not found in the borrowed books list!\n";
    } else {
        cout << "\n\t\t\t\t\tBook Found!\n";

        if (current->enrollment != S_head->enrollment) {
            cout << "\n\t\t\t\t\tThis book was not borrowed by you!\n";
        } else {
            // Calculate late fine
            long long returnTimeSeconds = convertToSeconds(getCurrentDateTime().c_str());
            long long borrowDaysInSeconds = current->borrowDays * 24 * 3600;
            long long borrowTimeSeconds = convertToSeconds(current->borrowedDateTime.c_str());
            long long timeDifferenceSeconds = returnTimeSeconds - (borrowTimeSeconds + borrowDaysInSeconds);

            cout << "Time Difference: " << timeDifferenceSeconds << " seconds" << endl;

            if (timeDifferenceSeconds > 0) {
                // The book is late, apply late fine
                long long lateFineDays = timeDifferenceSeconds / (24 * 3600);
                cout << "The book is " << lateFineDays << " days late. Late fine applies." << endl;

                // You can calculate and display the fine amount here based on your lateFineRate
                // For example: int fineAmount = lateFineRate * lateFineDays;
                // cout << "Fine Amount: " << fineAmount << endl;
            } else {
                cout << "The book is not late." << endl;
            }

            // Remove the book from the borrowed books list
            if (prev == nullptr) {
                // Update head only if the borrowed book is the first node
                B_head = current->B_next;
            } else {
                // Update the next pointer of the previous node
                prev->B_next = current->B_next;
            }

            // Print statements for debugging
            cout << "\n\t\t\t\t\tProcessing...\n";
            Sleep(2000);
            cout << "\t\t\t\t\tBook returned successfully.\n";

            // Update the borrowed_books.txt file
            updateBorrowedFile();
        }
    }

    // Print statements for debugging
    cout << "\n\t\t\t\t\tPress any key to continue . . .";
    _getch();
    system("cls");
}


void checkAllBooks(library* head) {
    system("cls"); // Clear the screen before displaying the list
    cout << "\n\t\t\t\t\tCheck All Books in Library\n";
    cout << "\t\t\t\t\t---------------------------\n\n";

    library* current = head;

    if (current == nullptr) {
        cout << "\t\t\t\t\tLibrary is empty.\n";
    } else {
        cout << "\t\t\t\t\tList of Books in Library:\n\n";
        cout << "ISBN          TiTLE           AUTHOR          EDITION        PUBLICATION        Status" << endl;
        while (current != nullptr) {
            cout << current->isbn  ;
            cout << "\t\t" << current->title ;
            cout << "\t\t" << current->author ;
            cout << "\t\t" << current->edition ;
            cout << "\t\t" << current->publication ;

            // Check if the book is borrowed
            bool isBorrowed = isBookBorrowed(current->isbn, 0); // Assuming regno 0 for library check

            if (isBorrowed) {
                cout << "\t\t Borrowed"<<"\n\n";
            } else {
                cout << "\t\t Available"<<"\n\n";
            }

            current = current->next;
        }
    }

    cout << "\t\t\t\t\tPress any key to continue . . .";
    _getch();
    system("cls"); // Clear the screen before returning to the menu
}



void clearScreen() {
    system("cls");
}

void studentMenu(library* S_head)
{
    int choice;
    do
    {
        // Display student menu options
        cout << "\t\t\t\t\t[1] - Borrow Books\n";
        cout << "\t\t\t\t\t[2] - Return Books\n";
        cout << "\t\t\t\t\t[3] - Check All Books in Library\n";
        cout << "\t\t\t\t\t[4] - Check All Time Favourite Borrowed Books\n";
        cout << "\t\t\t\t\t[0] - Return to Main Menu\n";

        cout << "\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            	system("cls");
                borrowBooks(S_head);
                updateBooksFile();
                break;
            case 2:
               returnBooks(S_head);
                break;
            case 3:
               checkAllBooks(head);
                break;
            case 4:
               allTimeFavoriteBooks( head);
                break;
            case 0:
                cout << "\t\t\t\t\tReturning to Main Menu...\n";
                break;
            default:
                cout << "\t\t\t\t\tInvalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void login() {
    int maxAttempts = 3;
    int currentAttempt = 0;

    while (currentAttempt < maxAttempts) {
        library* temp_S = S_head;
        string name, pass;

        clearScreen(); // Clear screen before each attempt
        cout << endl << endl;
        cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
        cout << "\t\t\t\t\t   || STUDENT - INTERFACE ||" << endl;
        cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl << endl;

        cout << "\t\t\t\t\tPlease Enter Your name :";
        cin >> name;

        cout << "\t\t\t\t\tPlease enter your password :";
        cin >> pass;
        cout << endl << endl;

        while (temp_S != NULL) {
            if (temp_S->name == name && temp_S->password == pass) {
                cout << "\t\t\t\t\tYou are successfully logged into your profile!\n";
                cout << "\n\t\t\t\t\tPress any key to continue . . .";
                _getch();

                // Successful login, break out of the outer loop
                clearScreen(); // Clear screen before calling studentMenu
                studentMenu(temp_S);
                return;
            } else {
                temp_S = temp_S->S_next; // Move to the next student
            }
        }

        cout << "\t\t\t\t\tInvalid credentials. Remaining attempts: " << maxAttempts - currentAttempt - 1 << "\n\n";
        currentAttempt++;
        _getch();
    }

    cout << "\t\t\t\t\tExceeded maximum login attempts. Returning to Main Menu...\n";
    _getch();
    clearScreen(); // Clear screen before returning to Main Menu
}


void loadBooksFromFile() {
    ifstream booksFile("books.txt");

    if (!booksFile.is_open()) {
        cout << "Error opening the file 'books.txt'." << endl;
        return;
    }

    while (!booksFile.eof()) {
        library* addbooks = new library;
        booksFile >> addbooks->isbn >> addbooks->title >> addbooks->author >> addbooks->edition >> addbooks->publication;

        if (booksFile.fail()) {
            delete addbooks; // Clean up memory in case of read failure
            break;
        }

        addbooks->next = addbooks->previous = NULL;

        if (head == NULL) {
            head = addbooks;
        } else {
            library* tail = head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = addbooks;
            addbooks->previous = tail;
        }
    }

    booksFile.close();
}

void deleteBooks() {
    int isbn;
    int choice;

    system("cls");
    cout << endl << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\n\n\t\t\t\t\t\t   DELETE BOOKS " << endl << endl;

    if (head == NULL) {
        cout << "\t\t\t\t\tTHERE ARE NO BOOKS TO BE DELETED" << endl;
        cout << "\n\t\t\t\t\tPress any key to continue..." << endl;
        _getch();
        return;
    }

    library* current = head;
    library* prev = NULL;

    cout << "\t\t\t\t\tENTER ISBN : ";
    cin >> isbn;

    // Validate ISBN format
    if (cin.fail() || isbn <= 0) {
        cin.clear(); // Clear the error flag
        while (cin.get() != '\n'); // Discard invalid input
        cout << "\t\t\t\t\tInvalid ISBN. Please enter a positive integer." << endl;
        cout << "\t\t\t\t\tPress any key to continue..." << endl;
        _getch();
        return;
    }

    while (current != NULL && current->isbn != isbn) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "\n\n\t\t\t\t\tBOOK NOT FOUND!\n" << endl;
        cout << "\t\t\t\t\tPress any key to continue..." << endl;
        _getch();
        return;
    }

    cout << "\n\n\t\t\t\t\tBOOK FOUND!\n" << endl;
    cout << "\t\t\t\t\tDo you want to delete this book? Yes[1], No[2]: ";
    cin >> choice;

    if (choice == 1) {
        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;

        // Update the books.txt file
        ofstream booksFile("books.txt");

        library* temp = head;
        while (temp != NULL) {
            booksFile << temp->isbn << " " << temp->title << " " << temp->author << " " << temp->edition << " " << temp->publication << endl;
            temp = temp->next;
        }

        booksFile.close();

        cout << "\t\t\t\t\tBOOK DELETED SUCCESSFULLY!\nPress any key to continue..." << endl;
        _getch();
    } else {
        cout << "\t\t\t\t\tDeletion Canceled. Press any key to continue..." << endl;
        _getch();
    }
}


void editBooks() {
    int editisbn;
    string choice;
    library* current = head;
    int attempts = 3;  // Maximum number of attempts to enter ISBN

    system("cls");
    cout << endl << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\n\n\t\t\t\t\t\t   EDIT BOOKS " << endl << endl;

    if (head == NULL) {
        cout << "\t\t\t\t\tTHERE IS NO BOOKS TO BE EDITED. FIRST ADD THE BOOKS!" << endl;
        cout << "\t\t\t\t\tPress any key to continue... " << endl;
        _getch();
        return;
    }

    cin.ignore();
    while (attempts > 0) {
        cout << "\t\t\t\t\tENTER ISBN (Attempts left: " << attempts << "): ";
        cin >> editisbn;

        while (current != NULL) {
            if (current->isbn == editisbn) {
                cout << "\n\n\t\t\t\t\tBOOK FOUND!" << endl << endl;
                cout << "\t\t\t\t\tDO YOU WANT TO EDIT THE BOOK? Edit [1] or Exit [2]: ";
                cin >> choice;

                if (choice == "1") {
                    cout << "\t\t\t\t\tENTER ISBN : ";
                    cin >> current->isbn;

                    cout << "\t\t\t\t\tENTER TITLE : ";
                    cin >> current->title;

                    cout << "\t\t\t\t\tENTER AUTHOR : ";
                    cin >> current->author;

                    cout << "\t\t\t\t\tENTER EDITION : ";
                    cin >> current->edition;

                    cout << "\t\t\t\t\tENTER PUBLICATION : ";
                    cin >> current->publication;

                    cout << "\t\t\t\t\tBOOK EDITED SUCCESSFULLY! Press any key to continue.." << endl;
                    _getch();

                    // Update the books.txt file after editing
                    ofstream booksFile("books.txt");
                    library* temp = head;
                    while (temp != NULL) {
                        booksFile << temp->isbn << " " << temp->title << " " << temp->author << " " << temp->edition << " " << temp->publication << endl;
                        temp = temp->next;
                    }
                    booksFile.close();
                    return;  // Exit the function after editing the book
                } else if (choice == "2") {
                    cout << "\t\t\t\t\tPRESS ANY KEY TO CONTINUE.." << endl;
                    _getch();
                    return;  // Exit the function without editing the book
                } else {
                    cout << "\t\t\t\t\tINVALID OPTION. PLEASE TRY AGAIN." << endl;
                }
            }

            current = current->next;
        }

        // If the loop completes and the book is not found
        cout << "\n\n\t\t\t\t\tBOOK NOT FOUND!" << endl;
        attempts--;
        if (attempts == 0) {
            cout << "\t\t\t\t\tNo more attempts left. Press any key to continue..." << endl;
            _getch();
            return;
        }
        cout << "\t\t\t\t\tPress any key to try again..." << endl;
        _getch();
        current = head;  // Reset current to head for each attempt
    }
}

void searchBooks() {
    int isbn;
    library* temp = head;
    bool print = false;
    int attempts = 3;  // Maximum number of attempts to enter ISBN
    system("cls");
    cout << endl << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
    cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
    cout << "\n\n\t\t\t\t\t\t   SEARCH BOOKS " << endl << endl;

    if (head == NULL) {
        cout << "\t\t\t\t\tTHERE IS NO BOOK TO SEARCH. PLEASE ADD A BOOK FIRST." << endl;
        cout << "\t\t\t\t\tPress any key to continue..." << endl;
        _getch();
        return;
    }

    while (attempts > 0) {
        temp = head;  // Reset temp to the head for each attempt
        cin.ignore();
        cout << "\t\t\t\t\tENTER ISBN (Attempts left: " << attempts << "): ";
        cin >> isbn;

        while (temp != NULL) {
            if (temp->isbn == isbn) {
                cout << "\n\n\t\t\t\t\tBOOK FOUND " << endl << endl;
                cout << "\t\t\t\t\tISBN : " << temp->isbn << endl;
                cout << "\t\t\t\t\tTITLE : " << temp->title << endl;
                cout << "\t\t\t\t\tAUTHOR : " << temp->author << endl;
                cout << "\t\t\t\t\tEDITION : " << temp->edition << endl;
                cout << "\t\t\t\t\tPUBLICATION : " << temp->publication << endl;
                print = true;
                break;  // Book found, exit the loop
            }
            temp = temp->next;
        }

        if (print) {
            cout << "\t\t\t\t\tPRESS ANY KEY TO CONTINUE..." << endl;
            _getch();
            break;  // Exit the loop if book is found
        } else {
            cout << "\t\t\t\t\tBOOK NOT FOUND. PLEASE TRY AGAIN." << endl;
            attempts--;
        }
    }

    // If after all attempts, book is not found, don't print the message again
    if (!print) {
        cout << "\t\t\t\t\tPRESS ANY KEY TO CONTINUE..." << endl;
        _getch();
    }
}

void viewAllBooks()
{
	system("cls");
	library *temp = head;
	cout << endl << endl;
	cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
	cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
	cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
	cout << "\n\n\t\t\t\t\t\t   VIEW ALL THE BOOKS " << endl << endl;

	if (head==NULL)
	{
		cout << "\t\t\t\t\tTHERE IS NO BOOK TO VIEW FIRST ADD THE BOOK! \n\n\t\t\t\t\tpresss any key to continue..." << endl;
		_getch();
	}
	else
	{
		system("cls");

		cout << setw(90) << setfill('~') << "~" << endl;
		cout << "\t\t\t    BOOK DETAILS " << endl;
		cout << setw(90) << setfill('~') << "~" << endl;

		cout << "ISBN          TiTLE           AUTHOR          EDITION        PUBLICATION " << endl;

		while (temp!=NULL)
		{

			
				cout << temp->isbn << "\t\t"
				<<temp->title << "\t\t"
				<<temp->author<< "\t\t"
				<<temp->edition<< "\t\t"
				<<temp->publication<< endl
				<< endl;
			temp = temp->next;
		}
		

		cout << "\t\t\t\t\tPress any key to continue . . .";
		_getch();
	}
}

void viewAllBooks_isbn(){
	system("cls");
	library *temp = head;
	library *temp1 = head;
	string titlts,authors,editions,publications;
	int isbns;
	cout << endl << endl;
	cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
	cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
	cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
	cout << "\n\n\t\t\t\t\t\t   VIEW ALL THE BOOKS " << endl << endl;

	if (head == NULL)
	{
		cout << "\t\t\t\t\tTHERE IS NO BOOK TO VIEW FIRST ADD THE BOOK! \n\n\t\t\t\t\tpresss any key to continue..." << endl;
		_getch();
	}

	else
	{
		system("cls");

		cout << setw(90) << setfill('~') << "~" << endl;
		cout << "\t\t\t    BOOK DETAILS " << endl;
		cout << setw(90) << setfill('~') << "~" << endl;

		cout << "ISBN          TiTLE           AUTHOR          EDITION        PUBLICATION " << endl;

		while (temp != NULL)
		{
			temp1 = temp;
			while (temp1!=NULL)
			{
				if (temp->isbn>temp1->isbn)
				{
					isbns =        temp->isbn;
					titlts =       temp->title;
					authors =      temp->author;
					editions =     temp->edition;
					publications = temp->publication;

					temp->isbn=       temp1->isbn;
					temp->title=      temp1->title;
					temp->author=     temp1->author;
					temp->edition=    temp1->edition;
					temp->publication=temp1->publication;


					temp1->isbn=isbns;
					temp1->title=titlts;
					temp1->author=authors;
					temp1->edition=editions;
					temp1->publication=publications;

				}
				temp1 = temp1->next;
			}

			cout << temp->isbn << "\t\t"
				<< temp->title << "\t\t"
				<< temp->author << "\t\t"
				<< temp->edition << "\t\t"
				<< temp->publication << endl
				<< endl;
			temp = temp->next;
		}


		cout << "\t\t\t\t\tPress any key to continue . . .";
		_getch();
	}

}

void viewstudentprofile() {
    system("cls");
    library* temp = S_head;

    cout << setw(90) << setfill('~') << "~" << endl;
    cout << "\t\t\t    Students  DETAILS " << endl;
    cout << setw(90) << setfill('~') << "~" << endl;

    cout << "Name          Enrollment           Section          Semester        Password " << endl;

    while (temp != nullptr) {

            cout << temp->name << "\t\t"
                 << temp->enrollment << "\t\t"
                 << temp->section << "\t\t"
                 << temp->semester << "\t\t"
                 << temp->password << endl
                 << endl;
        
        temp = temp->S_next;
    
    }
    cout << "\t\t\t\t\tPress any key to continue . . .";
    _getch();
}

void viewstudentprofile_enrollment()
{
	system("cls");
	library *temp = S_head;
	library *temp1 = S_head;
	int enrollment;
	string names, sections, semesters, passwords;
	cout << setw(90) << setfill('~') << "~" << endl;
	cout << "\t\t\t    Students  DETAILS " << endl;
	cout << setw(90) << setfill('~') << "~" << endl;

	cout << "Name          Enrollment           Section          Semester        Password " << endl;

	while (temp != NULL)
	{
		temp1 = temp;
		while (temp1!=NULL)
		{
			if (temp->enrollment>temp1->enrollment)
			{
				names =    temp->name;
				sections = temp->section;
				semesters = temp->semester;
				passwords = temp->password;
				enrollment = temp->enrollment;


				temp->name=   temp1->name;
				temp->section=temp1->section;
				temp->semester=temp1->semester;
				temp->password=temp1->password;
				temp->enrollment=temp1->enrollment;


				temp1->name=names;
				temp1->section=sections;
				temp1->semester=semesters;
				temp1->password=passwords;
				temp1->enrollment=enrollment;

			}
			temp1 = temp1->S_next;
		}

		cout << temp->name << "\t\t"
			<< temp->enrollment << "\t\t"
			<< temp->section << "\t\t"
			<< temp->semester << "\t\t"
			<< temp->password << endl
			<< endl;
		temp = temp->S_next;
	}


	cout << "\t\t\t\t\tPress any key to continue . . .";
	_getch();
}


int quit(void)
{
	system("cls");

	cout << "\n\n\n\n\t\t\t\t\t WAIT FOR A MOMENT , PROGRAM IS GOING TO CLOSE ! ";
	Sleep(3000);
	cout << "\n\n\n\n\t\t\t\t\t@@@@@@@@@@@@     @@         @@     @@@@@@@@@@@@            \n";
	cout << "\t\t\t\t\t@@        @@      @@       @@      @@                         \n";
	cout << "\t\t\t\t\t@@        @@       @@     @@       @@                         \n";
	cout << "\t\t\t\t\t@@@@@@@@@@@@        @@   @@        @@                         \n";
	cout << "\t\t\t\t\t@@          @@       @@ @@         @@@@@@@@@               \n";
	cout << "\t\t\t\t\t@@          @@        @@@          @@                         \n";
	cout << "\t\t\t\t\t@@          @@        @@@          @@                         \n";
	cout << "\t\t\t\t\t@@@@@@@@@@@@          @@@          @@@@@@@@@@@@            \n";

	cout << endl;

	cout << "\n\n\t\t\t\t\t" << setw(58) << setfill('~') << "~" << endl;
	cout << "\t\t\t\t\t||           COPY RIGHT -   Atta UR Rehman         ||\n";
	cout << "\t\t\t\t\t||                      -   Zohaib Nasir         ||\n";
	cout << "\t\t\t\t\t||                      -   Rehan Ul Hassan          ||\n";
	cout << "\t\t\t\t\t" << setw(58) << setfill('~') << "~" << endl;
	cout << "\n\n\t\t\t\t\tPress any key to continue . . .";
	_getch();
	exit(1);
}



// Function to save student data to a file
void saveStudentToFile() {
    ofstream outFile("student_data.txt");

    if (!outFile) {
        cerr << "Error: Unable to open student_data.txt for writing." << endl;
        return;
    }

    library* temp = S_head;

    while (temp != NULL) {
        outFile << temp->name << " "
                << temp->enrollment << " "
                << temp->section << " "
                << temp->semester << " "
                << temp->password << endl;
        temp = temp->S_next;
    }

    outFile.close();
}

void loadStudentFromFile() {
    ifstream studentFile("student_data.txt");

    if (!studentFile.is_open()) {
        cerr << "Error opening the file 'student_data.txt'." << endl;
        return;
    }

    while (!studentFile.eof()) {
        library* addStudent = new library;
        studentFile >> addStudent->name >> addStudent->enrollment >> addStudent->section >> addStudent->semester >> addStudent->password;

        if (studentFile.fail()) {
            delete addStudent; // Clean up memory in case of read failure
            break;
        }

        addStudent->S_next = addStudent->S_previous = NULL;

        if (S_head == NULL) {
            S_head = addStudent;
        } else {
            library* S_tail = S_head;
            while (S_tail->S_next != NULL) {
                S_tail = S_tail->S_next;
            }
            S_tail->S_next = addStudent;
            addStudent->S_previous = S_tail;
        }
    }

    studentFile.close();
}



int main()
{
	loadBooksFromFile();
	loadStudentsFromFile();
    loadBorrowData();
	system("color 02");

	string c, choice;
	int q;

	 

	system("CLS");
	do
	{
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t\t\t" << setw(32) << setfill('~') << "~" << endl;
		cout << "\t\t\t\t\t|| LIBRARY MANAGMENT SOFTWARE ||" << endl;
		cout << "\t\t\t\t\t" << setw(32) << setfill('~') << "~" << endl;
		cout << "\t\t\t\t\t       Discover Knowledge " << endl;
		cout << endl << endl << endl;
		cout << "\t\t\t\t\t     PROGRAM IS LOADING . . . \n\n\t\t\t\t\t\t JUST A MOMENT !\n ";
		//Sleep(3000);

		system("cls");
		cout << endl << endl;
		cout << "\t\t\t\t\t" << setw(32) << setfill('~') << "~" << endl;
		cout << "\t\t\t\t\t|| LIBRARY MANAGMENT SOFTWARE ||" << endl;
		cout << "\t\t\t\t\t" << setw(32) << setfill('~') << "~" << endl;
		cout << "\t\t\t\t\t       Discover Knowledge " << endl;

		cout << "\n\n\t\t\t\t\t[1] - For Librarian Interface \n";
		cout << "\t\t\t\t\t[2] - For Student Interface \n";
		cout << "\t\t\t\t\t[3] - About  \n";
		cout << "\t\t\t\t\t[4] - Quit \n\n";
		cout << "\n\t\t\t\t\tEnter your choice here : ";
		cin >> q;

		if (q == 1)
		{
		a:
			system("cls");
			cout << endl << endl;
			cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
			cout << "\t\t\t\t\t  || LIBRARIAN - INTERFACE ||" << endl;
			cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;


			cout << "\n\n\n\t\t\t\t\t[1] - ADD A BOOK " << endl;
			cout << "\t\t\t\t\t[2] - DELETE A BOOK " << endl;
			cout << "\t\t\t\t\t[3] - EDIT A BOOK " << endl;
			cout << "\t\t\t\t\t[4] - SEARCH A BOOK " << endl;
			cout << "\t\t\t\t\t[5] - VIEW ALL THE BOOKS " << endl;
			cout << "\t\t\t\t\t[6] - VIEW ALL THE BOOKS ASCENDING TO DESCENDING ORDER " << endl;
			cout << "\t\t\t\t\t[7] - VIEW ALL STUDENT PROFILE " << endl;
			cout << "\t\t\t\t\t[8] - VIEW ALL STUDENT PROFILE ASCENDING TO DESCENDING ORDER " << endl;
			cout << "\t\t\t\t\t[9] - QUIT " << endl;
			cout << "\t\t\t\t\t[10] - MAIN " << endl;

			cout << "\n\t\t\t\t\tEnter your choice here : ";
			cin >> c;

			if (c == "1")
			{
			    addbook();
				goto a;
			}
			else if (c == "2")
			{
				deleteBooks();
			}

			else if (c == "3")
			{
				editBooks();
			}

			else if (c == "4")
			{
				searchBooks();
			}

			else if (c == "5")
			{

				viewAllBooks();
			
			}

			else if (c == "6")
			{

				viewAllBooks_isbn();
			}

			else if (c == "7")
			{
		    viewstudentprofile();
			}


			else if (c == "8")
			{
				viewstudentprofile_enrollment();
			}


			else if (c == "9")
			{
				quit();
			}
			else
			{
				main();
			}
		}

		else if (q == 2)
		{
		b:
			system("cls");
			cout << endl << endl;
			cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;
			cout << "\t\t\t\t\t   || STUDENT - INTERFACE ||" << endl;
			cout << "\t\t\t\t\t" << setw(31) << setfill('~') << "~" << endl;


			cout << "\n\t\t\t\t\t[1] - FOR ADD STUDENT " << endl;
			cout << "\t\t\t\t\t[2] - FOR login STUDENT " << endl;
			cout << "\t\t\t\t\t[3] - FOR Quit " << endl;
			cout << "\t\t\t\t\t[4] - FOR MAIN " << endl;

			cout << "\n\t\t\t\t\tEnter your choice here : ";
			cin >> choice;

			if (choice == "1")
			{
				addStudentData();
				goto b;
			}

			else if (choice == "2")
			{
				login();

			   
			}
			else if (choice == "3")
			{
				quit();
			}
			else
			{
				main();
			}
		}

		else if (q == 3)
		{
			system("cls");
			cout << endl << endl;
			cout << "\t\t\t\t\t\t\t" << setw(21) << setfill('~') << "~" << endl;
			cout << "\t\t\t\t\t\t\t|| ABOUT - PROGRAM ||\n";
			cout << "\t\t\t\t\t\t\t" << setw(21) << setfill('~') << "~" << endl;
			cout << endl << endl << endl;
			cout << "\t\t\t\t\t[1] - IF YOU PRESS 1 A LIBRARIAN POP-UP MAIN MENU APPEAR \n\t\t\t\t\tIN WHICH YOU CAN ADD A BOOK \n\t\t\t\t\tDELETE A BOOK EDIT A BOOK SEARCH A BOOK AND YOU CAN \n\t\t\t\t\tVIEW ALL BOOKS IN LIBRARY  \n\t\t\t\t\tAND ALSO VIEW ALL STUDENTS PROFILE\n\n";

			cout << "\t\t\t\t\t[2] - IF YOU PRESS 2 A STUDENT POP - UP MAIN MENU APPEAR \n\t\t\t\t\tIN WHICH YOU CAN CREATE YOUR STUDENT PROFILE\n\t\t\t\t\tOR USE THIS PROFILE TO LOGIN YOUR ACCOUNT \n\t\t\t\t\tTHEN YOU CAN BORROW A BOOK RETURN A BOOK\n\n";

			cout << "\t\t\t\t\t[3] - IF YOU PRESS 3 THE ABOUT MENU IS SHOWN\n\n";

			cout << "\t\t\t\t\t[4] - IF YOU PRESS 4 THE PROGRAM IS CLOSED\n\n";
			cout << "\n\n\t\t\t\t\tPress any key to continue . . .";
			_getch();
		}

		else if (q == 4)
		{

			quit();
		}

	} while (q != 10);
	_getch();
	system("pause");

    saveStudentToFile();
	return 0;
}
