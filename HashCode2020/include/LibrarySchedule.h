#ifndef LIBRARYSCHEDULE_H
#define LIBRARYSCHEDULE_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>

using namespace std;

class LibrarySchedule
{
    public:
        LibrarySchedule();
        LibrarySchedule(int libId, vector<int> bookSequence) : libId(libId), bookSequence(bookSequence) {}
        LibrarySchedule(int libId) : libId(libId) {}
        virtual ~LibrarySchedule();
        void setStartDay(int startDay) {this->startDay = startDay;}
        void appendBook(int book);
        int getStartDay() {return startDay;}
        string toString();
        int getId() {return libId;}
        int getBookSequenceSize() {return bookSequence.size();}
        vector<int>& getBookSequence() {return bookSequence;}
    protected:

    private:
        int libId;
        int startDay;
        vector<int> bookSequence;
};

#endif // LIBRARYSCHEDULE_H
