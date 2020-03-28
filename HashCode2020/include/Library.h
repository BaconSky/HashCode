#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <iostream>
#include "Book.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

class Library
{
    public:
        Library(int id);
        virtual ~Library();
        friend istream& operator>> (istream& in, Library& lib);
        friend ostream& operator<< (ostream& out, const Library& lib);
        Library& operator=(const Library& l);
        string toString() const;
        vector<int>& getBooks() {return books;}
        int getId() {return id;}
        int getSignUpTime() {return signUpTime;}
        int getMaxBooksPerDay() {return maxBooksPerDay;}
        int getLibScore() {return libScore;}
        void setLibScore(int libScore) {this->libScore = libScore;}
    protected:

    private:
        int libScore;
        int id;
        int numBooks;
        int signUpTime;
        int maxBooksPerDay;
        //vector<int> &bookScores;
        vector<int> books;
        bool compareBooks(int book1, int book2);
};

#endif // LIBRARY_H
