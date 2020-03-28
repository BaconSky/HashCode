#include "LibrarySchedule.h"

LibrarySchedule::LibrarySchedule()
{
    cout << "LibrarySchedule cons0 ---" << endl;
}
string LibrarySchedule::toString() {
    stringstream sstr;
    sstr << "libId = " << libId << " startDay = " << startDay << endl;
    if (!bookSequence.empty()) {
        copy(bookSequence.begin(), bookSequence.end(), ostream_iterator<int>(sstr, " "));
        sstr << endl;
    }

    //for (vector<int>::iterator it = bookSequence.begin(); it != bookSequence.end(); it++) sstr << to_string(*it) << endl;

    return sstr.str();
}

LibrarySchedule::~LibrarySchedule()
{
    //dtor
}

void LibrarySchedule::appendBook(int book){
    //bookSequence.insert(bookSequence.end(), book);
    bookSequence.push_back(book);
}

