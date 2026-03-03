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
        Book(string t, string a, Genre g) {
            title = t;
            author = a;
            genre = g;
            status = Available;
        }
        

        virtual void displayInfo() {};

        void setStatus(BookStatus s) {
            status = s;
        }
        BookStatus getStatus() const {
            return status;
        }
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
        string getTitle() {
            return title;
        }
        virtual string bookType() {
            return "None";
        }

        friend ostream& operator<<(ostream& os, Book& b) {
            os << b.genreToString(b.genre) << "," << b.title << "," << b.author << "," << b.bookType() << "," << b.getSpecialData() << endl;
            return os;
        }
        virtual string getSpecialData() {
            return "None";
        }
};

class EBook : public Book {
    double fileSizeMB;
    public:
        EBook(string t, string a, Genre g, double size) {
            title = t;
            author = a;
            genre = g;
            fileSizeMB = size;
            setStatus(Available);
        }
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
        string getSpecialData() {
            int fs = fileSizeMB*10;
            return to_string(fs/10.0);
        }
        string bookType() {
            return "EBook";
        }
    };

class PrintedBook : public Book {
    int pageCount;
    public:

        PrintedBook(string t, string a, Genre g, int pages) {
            title = t;
            author = a;
            genre = g;
            pageCount = pages;
            setStatus(Available);
        }
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
        string getSpecialData() {
            return to_string(pageCount);
        }
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
        Transaction(int pid, Book* b) {
            book = b;
            patronId = pid;
            bookTitle = b->getTitle();
            b->setStatus(CheckedOut);
            

        }
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
        Book* getBook() {
            return book;
        }
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
        Patron(string n, int i) {
            name = n;
            id = i;
        }
        int getID() {
            return id;
        }
        void borrowBook(Book* b) {
            // borrow dat thang
            b->setStatus(CheckedOut);
        }
        void returnBook(Book* b) {
            b->setStatus(Available);
        }
        void displayPatron() const {
            cout << "--------------------------------------------------------" << endl;
            cout << name << ": " << id << endl << endl;
        }
        bool operator==(const Patron& other) const {
            if (name == other.name) {
                if (id == other.id) {
                    return true;
                }
            }
            return false;
        }
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
        ~ Library() {}
        void loadData() {
            // loop throguht the inputs.txt an then put all the books in a list
            ifstream inFS("inputs.txt");
            vector<string> rowData;
            string line;
            vector<string> bookData;
            
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

            rowData.clear();
            inFS.close();
            inFS.open("patrons.txt");

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

        void saveData() {
            // update the text files !!!
            ofstream outFS("inputs.txt");
            for (Book* b:books) {
                outFS << *b;
            }
            outFS.close();
            outFS.open("patrons.txt");
            for (Patron p:patrons) {
                outFS << p;
            }
            outFS.close();
            outFS.open("transactions.txt");
            for (Transaction t:transactions) {
                outFS << t;
            }
        }
        void addBook(Book* b) {
            books.push_back(b);
        }
        void addPatron(const Patron& p) {
            patrons.push_back(p);
        }
        void checkoutBook(int patronId, string title) {
            for (Book* b:books) {
                if (title == b->getTitle()) { // if the title matches
                    cout << "Found Book..." << endl;
                    if (b->getStatus() == CheckedOut) {
                        cout << "Book Checked out Already." << endl;
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
        void returnBook(int patronId, string title) {
            for (Transaction t:transactions) {
                if (t.getBook()->getTitle() == title) {
                    for (Patron p:patrons) {
                        if (p.getID() == patronId) {
                            p.returnBook(t.getBook());
                            t.displayTransaction();
                            break;
                        }
                    }
                    break;
                }
            }
        }
        void displayBooks() const {
            for (Book* b:books) {
                b->displayInfo();
            }
        }
        void displayPatrons() const {
            for (Patron p:patrons) {
                p.displayPatron();
            }
        }
    };


void printOnStart() {
    cout << endl;
    cout << "1. Display Books" << endl;
    cout << "2. Display Patrons" << endl;
    cout << "3. Checkout Book" << endl;
    cout << "4. Add Books" << endl;
    cout << "5. Add Patrons" << endl;
    cout << "6. Quit" << endl;
}

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
    Library library;
    try {
        library.loadData();
        printOnStart();
        int temp;
        temp = getIntInput("Action");
        while (temp!=6) {
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