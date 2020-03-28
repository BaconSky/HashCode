#include "Library.h"

Library::Library(int id) : id(id) {}

ostream& operator<< (ostream& out, const Library& lib) {
    out << lib.toString();
    return out;
}

istream& operator>> (istream& in, Library& lib) {
    in >> lib.numBooks;
    in >> lib.signUpTime;
    in >> lib.maxBooksPerDay;
    lib.books.reserve(lib.numBooks);
    for (int i = 0; i < lib.numBooks; i++) {
        int id;
        in >> id;
        lib.books.insert(lib.books.end(), id);
    }
    // -------------- QSORT!!!

    //sort(lib.books.begin(), lib.books.end(), compareBooks);

    return in;
}

Library& Library::operator=(const Library& lib) {
    if (this !=& lib) {
        id = lib.id;
        numBooks = lib.numBooks;
        signUpTime = lib.signUpTime;
        maxBooksPerDay = lib.maxBooksPerDay;
        vector<int> books;
        books.clear();
        books = lib.books;
        //books.clear();
    }

    return *this;
}

string Library::toString() const {
    stringstream  sstr;
    sstr << "Library toString() id: " <<  id << " numBooks: " <<
    numBooks << " signUpTime: " << signUpTime << " maxBooksPerDay: " << maxBooksPerDay << endl << "books: ";
    if (!books.empty()) {
        copy(books.begin(), books.end(), ostream_iterator<int>(sstr, " "));
        sstr << endl;
    }
    //string str = sstr.str();
    return sstr.str();
}

Library::~Library() {}
