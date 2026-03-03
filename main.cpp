#include <vector>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

enum Genre { Fiction, NonFiction, Mystery, Science, Biography };
enum BookStatus { Available, CheckedOut };

class Book {
    protected:
        string title;
        string author;
        Genre genre;
        BookStatus status;
    public:
        Book() {};
        // default constructor
        Book(string t, string a, Genre g) {
            title = t;
            author = a;
            genre = g;
            status = Available;
        }
        

        virtual void displayInfo() {};

        // set book status
        void setStatus(BookStatus s) {
            status = s;
        }
        // get status
        BookStatus getStatus() const {
            return status;
        }
        // convert genre to string
        string genreToString(Genre a) {
            if (a == Fiction) {
                return "Fiction";
            }
            if (a == NonFiction) {
                return "NonFiction";
            }
            if (a == Mystery) {
                return "Mystery";
            }
            if (a == Science) {
                return "Science";
            }
            if (a == Biography) {
                return "Biography";
            }
            return "ERROR";
        }
        // equals operator, could have used it quite a lot, didnt
        bool operator==(const Book& other) const {
            if (title == other.title) {
                if (author == other.author) {
                    if (genre == other.genre) {
                        return true;
                    }
                }
            }
            return false;
        }
        // get title of book
        string getTitle() {
            return title;
        }
        // get book type
        virtual string bookType() {
            return "None";
        }
        // output book into stream
        friend ostream& operator<<(ostream& os, Book& b) {
            os << b.genreToString(b.genre) << "," << b.title << "," << b.author << "," << b.bookType() << "," << b.getSpecialData() << endl;
            return os;
        }
        // special book data
        virtual string getSpecialData() {
            return "None";
        }
};

class EBook : public Book {
    double fileSizeMB;
    public:
        // default constructor
        EBook(string t, string a, Genre g, double size) {
            title = t;
            author = a;
            genre = g;
            fileSizeMB = size;
            setStatus(Available);
        }
        // display info about book
        void displayInfo() override {
            cout << "--------------------------------------------------------" << endl;
            cout << title << ", by " << author << ", Genre: " << genreToString(genre) << ",  File Size: " << fileSizeMB << "MB" << endl;
            if (status == CheckedOut) {
                cout << "Status: Checked Out" << endl;
            }
            if (status == Available) {
                cout << "Status: Available" << endl;
            }
        }
        // genre to string, converts it.
        string genreToString(Genre a) {
            if (a == Fiction) {
                return "Fiction";
            }
            if (a == NonFiction) {
                return "NonFiction";
            }
            if (a == Mystery) {
                return "Mystery";
            }
            if (a == Science) {
                return "Science";
            }
            if (a == Biography) {
                return "Biography";
            }
            return "ERROR";
        }
        // gets the file size and rounds it. usually.
        string getSpecialData() {
            int fs = fileSizeMB*10;
            return to_string(fs/10.0);
        }
        // get book type, ebook always.
        string bookType() {
            return "EBook";
        }
    };

class PrintedBook : public Book {
    int pageCount;
    public:
        // default constructor
        PrintedBook(string t, string a, Genre g, int pages) {
            title = t;
            author = a;
            genre = g;
            pageCount = pages;
            setStatus(Available);
        }
        // display info about book
        void displayInfo() override {
            cout << "--------------------------------------------------------" << endl;
            cout << title << ", by " << author << ", Genre: " << genreToString(genre) << ",  Page Count: " << pageCount << endl;
            if (status == CheckedOut) {
                cout << "Status: Checked Out" << endl;
            }
            if (status == Available) {
                cout << "Status: Available" << endl;
            }
        }
        // convert genre to a string
        string genreToString(Genre a) const {
            if (a == Fiction) {
                return "Fiction";
            }
            if (a == NonFiction) {
                return "NonFiction";
            }
            if (a == Mystery) {
                return "Mystery";
            }
            if (a == Science) {
                return "Science";
            }
            if (a == Biography) {
                return "Biography";
            }
            return "ERROR";
        }
        // get special data about book, pagecount
        string getSpecialData() {
            return to_string(pageCount);
        }
        // get book type, always printed
        string bookType() {
            return "Printed";
        }
};

class Transaction {
    int patronId;
    string bookTitle;
    Book* book;
    string date;
    string checked;
    public:
        // default constructor
        Transaction(int pid, Book* b) {
            book = b;
            patronId = pid;
            bookTitle = b->getTitle();
            b->setStatus(CheckedOut);
            

        }
        // display the transaction, as patron x checked out book y or patron x returned book y
        void displayTransaction() const {
            cout << "--------------------------------------------------------" << endl;
            if (book->getStatus() == CheckedOut) {
                cout << "Patron " << patronId << " checked out book " << bookTitle <<  endl;
            }
            else if (book->getStatus() == Available) {
                cout << "Patron " << patronId << " returned book " << bookTitle <<  endl;
            }
            cout << endl;
        }
        // get the book in the transaction
        Book* getBook() {
            return book;
        }
        // output transaction to stream
        friend ostream& operator<<(ostream& os, Transaction& t) {
            if (t.getBook()->getStatus() == CheckedOut) { 
                os << "Book: " << t.getBook()->getTitle() << " checked out by PatronID: " << t.patronId << endl;
            }
            if (t.getBook()->getStatus() == Available) { 
                os << "Book: " << t.getBook()->getTitle() << " returned by PatronID: " << t.patronId << endl;
            }
            return os;
        }
};

class Patron {
    string name;
    int id;
    vector<Book*> borrowedBooks;
    public:
        // default constructor
        Patron(string n, int i) {
            name = n;
            id = i;
        }
        // get the patron id
        int getID() {
            return id;
        }
        // borrow the book, so set it to checked out
        void borrowBook(Book* b) {
            // borrow dat thang
            b->setStatus(CheckedOut);
        }
        // return the book, set it to available
        void returnBook(Book* b) {
            b->setStatus(Available);
        }
        // display the patron
        void displayPatron() const {
            cout << "--------------------------------------------------------" << endl;
            cout << name << ": " << id << endl << endl;
        }
        // also could have used this but didn't. checks if the patron is equal to another patron
        bool operator==(const Patron& other) const {
            if (name == other.name) {
                if (id == other.id) {
                    return true;
                }
            }
            return false;
        }
        // output the patron to text file
        friend ostream& operator<<(ostream& os, const Patron& p) {
            os << p.id << "," << p.name << endl;
            return os;
        }
};

class Library {
    vector<Book*> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;
    public:
        // default constructors
        ~ Library() {}
        // load data from library
        void loadData() {
            // loop throguht the inputs.txt an then put all the books in a list
            ifstream inFS("inputs.txt");
            vector<string> rowData;
            string line;
            vector<string> bookData;
            
            // get each line and add it to row data, and then process it into books
            while (getline(inFS, line)) {
                rowData.push_back(line);
                stringstream ss(line);
                string field;
                while (getline(ss, field, ',')) {
                    bookData.push_back(field);
                }
                if (bookData.at(3) == "Printed") {
                    addBook(new PrintedBook(bookData.at(1), bookData.at(2), stringToGenre(bookData.at(0)), stoi(bookData.at(4))));
                }
                if (bookData.at(3) == "EBook") {
                    addBook(new EBook(bookData.at(1), bookData.at(2), stringToGenre(bookData.at(0)), stod(bookData.at(4))));
                }
                bookData.clear();
            }
            // clear for reuse
            rowData.clear();
            inFS.close();
            inFS.open("patrons.txt");

            
            // get each line and process them into patrons. clear after.
            while(getline(inFS, line)) {
                rowData.push_back(line);
                stringstream ss(line);
                string field;
                while (getline(ss, field, ',')) {
                    bookData.push_back(field);
                }
                addPatron(Patron(bookData.at(1), stoi(bookData.at(0))));
                bookData.clear();
            }

        }
        // change string to a genre
        Genre stringToGenre(string a) {
            if (a == "Fiction") {
                return Fiction;
            }
            if (a == "NonFiction") {
                return NonFiction;
            }
            
            if (a == "Mystery") {
                return Mystery;
            }
            
            if (a == "Science") {
                return Science;
            }
            
            if (a == "Biography")  {
                return Biography;
            }
            return Fiction; // Error handling :D
        }
        // save the data to the files
        void saveData() {
            // update the text files !!!
            ofstream outFS("inputs.txt");
            for (Book* b:books) {
                outFS << *b;
            }
            // close  files and open next
            outFS.close();
            outFS.open("patrons.txt");
            for (Patron p:patrons) {
                outFS << p;
            }
            // close files and open next
            outFS.close();
            outFS.open("transactions.txt");
            for (Transaction t:transactions) {
                outFS << t;
            }
        }
        // add book to books
        void addBook(Book* b) {
            books.push_back(b);
        }
        // add patron to patrons
        void addPatron(const Patron& p) {
            patrons.push_back(p);
        }
        // check out a book
        void checkoutBook(int patronId, string title) {
            for (Book* b:books) {
                if (title == b->getTitle()) { // if the title matches
                    cout << "Found Book..." << endl;
                    if (b->getStatus() == CheckedOut) {
                        cout << "Book Checked out Already." << endl; // check to make sure book isn't checked out
                        break;
                    }
                    for (Patron p:patrons) { // loop through patrons
                        if (p.getID() == patronId) { // if the patron id
                            p.borrowBook(b); // borrow that thang
                            Transaction transaction(patronId, b);
                            transactions.push_back(transaction);
                            transaction.displayTransaction();
                            break;
                        }
                    }
                 break;   
                }
            }
        }
        // return book
        void returnBook(int patronId, string title) {
            for (Transaction t:transactions) { // for each transaction
                if (t.getBook()->getTitle() == title) { // if the title matches
                    for (Patron p:patrons) { // for each patron
                        if (p.getID() == patronId) { // if the id matches
                            p.returnBook(t.getBook()); // return book
                            t.displayTransaction();
                            break;
                        }
                    }
                    break;
                }
            }
        }
        void displayBooks() const { // display all books
            for (Book* b:books) {
                b->displayInfo();
            }
        }
        // display all patrons
        void displayPatrons() const {
            for (Patron p:patrons) {
                p.displayPatron();
            }
        }
    };

// print function to print at start of program
void printOnStart() {
    cout << endl;
    cout << "1. Display Books" << endl;
    cout << "2. Display Patrons" << endl;
    cout << "3. Checkout Book" << endl;
    cout << "4. Add Books" << endl;
    cout << "5. Add Patrons" << endl;
    cout << "6. Quit" << endl;
}
// get functions to simplify readability.
string getStringInput(string message) {
    cout << message << ": ";
    string temp;
    getline(cin, temp);
    
    cout << endl;
    return temp;
}
int getIntInput(string message) {
    cout << message << ": ";
    int temp;
    cin >> temp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    return temp;
}
double getDoubleInput(string message) {
    cout << message << ": ";
    double temp;
    cin >> temp;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    return temp;
}
// string to genre, again. Don't ask.
Genre stringToGenre(string a) {
    if (a == "Fiction") {
        return Fiction;
    }
    if (a == "NonFiction") {
        return NonFiction;
    }
    
    if (a == "Mystery") {
        return Mystery;
    }
    
    if (a == "Science") {
        return Science;
    }
    
    if (a == "Biography")  {
        return Biography;
    }
    return Fiction; // Error handling :D
}


int main() {
    Library library; // make a library class
    try {
        library.loadData(); // load the data
        printOnStart(); // print actions
        int temp;
        temp = getIntInput("Action"); // get action
        while (temp!=6) { // while not quit
            if (temp==1) {
                library.displayBooks();
            }
            if (temp==2) {
                library.displayPatrons();
            }
            if (temp==3) {
                int PatronID = getIntInput("PatronID");
                string Title = getStringInput("Book Name");
                
                library.checkoutBook(PatronID, Title);

            }
            if (temp==4) {
                string booktype = getStringInput("Book Type (EBook/Printed)");
                string t = getStringInput("Title");
                string g = getStringInput("(Fiction, NonFiction, Mystery, Science, Biography) \n Genre");
                string a = getStringInput("Author");

                if (booktype == "Printed") {
                    int p = getIntInput("Pages");
                    Genre gup = stringToGenre(g);
                    library.addBook(new PrintedBook(t, a, gup, p));
                }
                if (booktype == "EBook") {
                    double p = getDoubleInput("File Size");
                    Genre gup = stringToGenre(g);
                    library.addBook(new EBook(t, a, gup, p));
                }
            }
            if (temp==5) {
                string name = getStringInput("Patron Name");
                int id = getIntInput("Patron ID");
                library.addPatron(Patron(name, id));
            }
            printOnStart();
            temp = getIntInput("Action");
        }
        cout << "Saving Data..." << endl;
        library.saveData();
        cout << "Thanks for Using!" << endl;
    }
    catch (const exception& e) {
        cerr << "Application Error: " << e.what() << endl;
    }
    return 0;
};