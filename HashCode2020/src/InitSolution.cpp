#include "InitSolution.h"


//----------------------- ctor, dtor
InitSolution::InitSolution(int dayScan, vector<int> &bookScoresList, vector<Library> &libs) : dayScan(dayScan), bookScoresList(bookScoresList), libs(libs) {dayScan = 0;}
/*
bool InitSolution::compareBooks(int book1, int book2) {
    return (bookScoresList[book1] < bookScoresList[book2]);
}
*/




InitSolution::~InitSolution()
{
    //dtor
}


//--------------------- algoritms -----------------------------------------------


//----------------------------sort

int InitSolution::libPartition(vector<int> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = bookScoresList[values[pivotIndex]];
    int i = left, j = right;
    int temp;
    while(i <= j) {
        while(bookScoresList[values[i]] > pivotValue) {
            i++;
        }
        while(bookScoresList[values[j]] < pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }set<int> bookScannedList;
    }
    return i;
}

void InitSolution::libQuicksort(vector<int> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = libPartition(values, left, right);
        libQuicksort(values, left, pivotIndex - 1);
        libQuicksort(values, pivotIndex, right);
    }
}

void InitSolution::sortBooks() {
    //cout << "InitSolution::sortBooks after sorting" << endl;
    for (vector<Library>::iterator it = libs.begin(); it != libs.end(); it++) {
        vector<int> &books = it->getBooks();
        libQuicksort(books, 0, books.size() - 1);
        //cout << *it;

    }
}


//------------------------------- cumpute library sequence


int InitSolution::computeLibScore(Library &lib, const int daysLeft, vector<bool> &scannedBooks) {
    //cout << "   computeLibScore studying lib: " << lib.getId() << " daysLeft = " << daysLeft << " setup Time = " << lib.getSignUpTime() << endl;
    int score = 0;
    //daysLeft -= lib.getSignUpTime();
    vector<int>::iterator it = lib.getBooks().begin();
//    for (int i = daysLeft - lib.getSignUpTime(); i >= 0; i--) { // for each day
    for (int i = daysLeft - lib.getSignUpTime(); i >= 0; i--) { // for each day
        if (it == lib.getBooks().end()) break;
        int numBooksLeftToday = lib.getMaxBooksPerDay();
        while ((numBooksLeftToday != 0) && (it != lib.getBooks().end())) {
            if (scannedBooks[*it] == false) {
                score += bookScoresList[*it];
                //cout << "       computeLibScore: on day (lastDay-i) i = " << i << " adding score for book: " << *it << " new score: " << score << endl;
                numBooksLeftToday--;
            }
            it++;
        }
    }
    //cout << "       computeLibScore res = " << score << endl;
    return score;
}

void InitSolution::generateSolutionM(ScanningSolution &scanningSolution) {

    int curStartDay = 0;
    //vector<int> bookSequence;
    vector<bool> bookScannedList(bookScoresList.size(), false);
    sortBooks();
    // compute libScore
    set<int> processedLibs;
    vector<int> libSequence;
    map<int, int> currentBookIndex;
    // currentBookIndex: Explanation
    // first part of map: id of library
    // second part of map: index of books which are already scanned in library.


    bool done = false;
    //int score = 0;

    //set<int> scannedBooks;

cout << "--------------------" << endl;
    int debugCnt = 0;
    int totalScore = 0;
    int numLibsProcessed = 0;
    while (!done) {
        debugCnt++;
        //if (debugCnt > 3) { cout << "del this line!!!" << endl; break; }
        //cout << "-------------------------------- generateSolutionM: while not done pos1 find best lib" << endl;
        //-------------- find best lib
        for (vector<Library>::iterator it = libs.begin(); it != libs.end(); it++) {
            if(processedLibs.find(it->getId()) != processedLibs.end()) {
                //cout << "library " << it->getId() << " already processed++++++++-------" << endl;
                continue;
            }
            //if (debugCnt % 500 == 1) it->setLibScore(computeLibScore(*it, dayScan - curStartDay, bookScannedList));
            it->setLibScore(computeLibScore(*it, dayScan - curStartDay, bookScannedList));
        }
        //vector<Library>::iterator curBestLib = libs.begin();
        vector<Library>::iterator curBestLib;
        int curMax;
        bool first = true;
        //= curBestLib->getLibScore();
        bool foundLibrary = false;
        for (vector<Library>::iterator it = libs.begin(); it != libs.end(); it++) {
            if(processedLibs.find(it->getId()) != processedLibs.end()) {
                //cout << "library " << it->getId() << " already processed--------------" << endl;
                continue;

            }
            foundLibrary = true;
            if (first) {
                curMax = it->getLibScore();
                curBestLib = it;
            } else {
                if (curMax < it->getLibScore()) {
                    curBestLib = it;
                    curMax = it->getLibScore();
                }
            }
            first = false;
        }
        if (!foundLibrary) {
            cout << "no Library anymore" << endl;
            done = true;
            break;
        }
        numLibsProcessed++;
        cout << "numLibsProcessed = " << numLibsProcessed << " found best lib id = " << curBestLib->getId() << " with score " << curMax << endl;
        /*
        if (numLibsProcessed > 3000) {
            done = true;
            break;
        }
        */
        //vector<int> bookSequence;
        int id = curBestLib->getId();
        curStartDay += curBestLib->getSignUpTime();
//        cout << "curStartDay = " << curStartDay << endl;
        //cout << "updating libSequence - going to insert id = "<<id<<" before : "; for (vector<int>::iterator it = libSequence.begin(); it != libSequence.end(); it++) cout << *it << " "; cout << endl;
        libSequence.insert(libSequence.end(), id);
        //cout << "updated libSequence - after inserting id = " << id << " --- "; for (vector<int>::iterator it = libSequence.begin(); it != libSequence.end(); it++) cout << *it << " "; cout << endl;
        //cout << "initializing currentBookIndex and librarySchedule" << endl;
        currentBookIndex.insert(pair<int,int>(id,0));
        //LibrarySchedule librarySchedule(id, bookSequence);
        LibrarySchedule librarySchedule(id);
        librarySchedule.setStartDay(curStartDay);
        if (curStartDay > dayScan) { done = true; break;
            cout << "curStartDay = " << curStartDay << " > dayScan = " << dayScan << " -> done" << endl;
        }
        //cout<< "generateSolutionM going to append librarySchedule : " << librarySchedule.toString() << endl;
        scanningSolution.appendLibrarySchedule(librarySchedule);
        processedLibs.insert(curBestLib->getId());




 // to be replace -------------start

        int daysLeft = dayScan - curStartDay;
        // scan best books
        //Library lib = libs[curBestLib];
 //       for (int i = daysLeft - lib.getSignUpTime(); i >= 0; i--) { // for each day
        //cout << "--------- start scanning books for lib id = " << curBestLib->getId() << " daysLeft = " << daysLeft << endl;
        vector<int>::iterator it = curBestLib->getBooks().begin();
        //int scoreForCurLib = 0;
        int scoreAdded = 0;

        for (int i = daysLeft; i >= 0; i--) { // for each day
            //cout << "   morning of day  (last day - i) i = " << i << " start processing" << endl;

            if (it == curBestLib->getBooks().end()) {
                //cout << "   +++--+ finished all books in this lib => break" << endl;
                break;

            }
            int numBooksLeftToday = curBestLib->getMaxBooksPerDay();

            while ((numBooksLeftToday != 0) && (it != curBestLib->getBooks().end())) {
                //cout << "while pos 2" << endl;
                if (!bookScannedList[*it]) {
                    //cout << "while pos 3" << endl;
                    bookScannedList[*it] = true;
                    //cout << "while pos 4" << endl;
                    //scoreForCurLib += bookScoresList[*it];
                    scanningSolution.appendBook(curBestLib->getId(), *it);
                    scoreAdded += bookScoresList[*it];
                    //cout << "while pos 5" << endl;
                    numBooksLeftToday--;
                    //cout << "while pos 6" << endl;
                    //cout << "      scanning book = " << *it << " numBooksLeftToday = " << numBooksLeftToday << endl;
                    //cout << "while pos 7" << endl;
                }
                it++;
                //cout << "while pos 8" << endl;
                if (it == curBestLib->getBooks().end()) {
                    //cout << "   +++ finished all books in this lib => break" << endl;
                    break;
                }
                //cout << "while pos 9" << endl;
            }

            //cout << "   end of day i = " << i << " - processed bookScannedList = "; for (set<int>::iterator it = bookScannedList.begin(); it != bookScannedList.end(); it++) cout << *it << " "; cout << endl;

        } // for i
        totalScore += scoreAdded;
        cout << "library: " << curBestLib->getId() << " added score: " << scoreAdded << " totalScore = " << totalScore << endl;
        //cout << "scanningSolution: " << scanningSolution.toString() << endl;


/*
        // compute books for each library
        for (int day = 0; day < dayScan; day++) {
            for (vector<int>::iterator it = libSequence.begin(); it != libSequence.end(); it++) {
                int curLibId = *it;
                curStartDay = scanningSolution.getLibSchedule(curLibId).getStartDay();
                map<int, int>::iterator pCurBookIdx = currentBookIndex.find(curLibId);
                int curBookIdx = pCurBookIdx->second;
                const vector<int> &booksInLib = libs[curLibId].getBooks();
                int numBooksInLib = booksInLib.size();
                int maxBooksPerDay = libs[curLibId].getMaxBooksPerDay();
                int i = 0;
                //cout << "compute books, day = " << day << " (morning) curLibId = " << curLibId << " curBookIdx = " << curBookIdx << " curStartDay = " << curStartDay;
                //cout << " numBooksInLib = " << numBooksInLib  << " maxBooksPerDay = " << maxBooksPerDay << endl;
                if (day < curStartDay) continue;
                while(i < maxBooksPerDay) {
                    if (curBookIdx >= numBooksInLib) break;
                    int curBook = booksInLib[curBookIdx];
                    if (scannedBooks.find(curBook) != scannedBooks.end()) {
                        //cout << "        curBook:" << curBook << " already scanned-> ignore" << endl;
                        curBookIdx++; continue;
                    }
                    scannedBooks.insert(curBook);
                    scanningSolution.appendBook(curLibId, curBook);
                    //cout << "    day:" << day << " lib:" << curLibId << " scanBook:" << curBook << " score:" << bookScoresList[curBook] << endl;
                    curBookIdx++;
                    i++;
                }
                currentBookIndex[curLibId] = curBookIdx;
            }
        }
*/


    } // while


}

//--------------------------------main ---------------------
/*
void InitSolution::generateSolution(ScanningSolution &scanningSolution) {
    // select libraries and compute start day for each library
    vector<int> libSequence;
    map<int, int> currentBookIndex;
    // currentBookIndex: Explanation
    // first part of map: id of library
    // second part of map: index of books which are already scanned in library.
    sortBooks();

    for (vector<Library>::iterator it = libs.begin(); it != libs.end(); it++) computeLibScore(*it, 7);

    // construct scanningSolution
    int curStartDay = 0;
    for (vector<Library>::iterator it = libs.begin(); it != libs.end(); it++) {
        vector<int> bookSequence;
        int id = it->getId();
        curStartDay += it->getSignUpTime();
        libSequence.insert(libSequence.end(), id);
        currentBookIndex.insert(pair<int,int>(id,0));
        LibrarySchedule librarySchedule(id, bookSequence);
        librarySchedule.setStartDay(curStartDay);
        scanningSolution.appendLibrarySchedule(librarySchedule);
        if (curStartDay > dayScan) break;

    }

    //cout << "generateSolution pos4: Sequence of libs is initialized. Current scanning solution is: " << endl;
    //cout << scanningSolution.toString();
    printCurrentBookIndex(currentBookIndex);
    printLibSequence(libSequence);

    // compute books for each library
    set<int> scannedBooks;
    for (int day = 0; day < dayScan; day++) {
        for (vector<int>::iterator it = libSequence.begin(); it != libSequence.end(); it++) {
            int curLibId = *it;
            curStartDay = scanningSolution.getLibSchedule(curLibId).getStartDay();
            map<int, int>::iterator pCurBookIdx = currentBookIndex.find(curLibId);
            int curBookIdx = pCurBookIdx->second;
            const vector<int> &booksInLib = libs[curLibId].getBooks();
            int numBooksInLib = booksInLib.size();
            int maxBooksPerDay = libs[curLibId].getMaxBooksPerDay();
            int i = 0;
            //cout << "compute books, day = " << day << " (morning) curLibId = " << curLibId << " curBookIdx = " << curBookIdx << " curStartDay = " << curStartDay;
            //cout << " numBooksInLib = " << numBooksInLib  << " maxBooksPerDay = " << maxBooksPerDay << endl;
            if (day < curStartDay) continue;
            while(i < maxBooksPerDay) {
                if (curBookIdx >= numBooksInLib) break;
                int curBook = booksInLib[curBookIdx];
                if (scannedBooks.find(curBook) != scannedBooks.end()) {
                    //cout << "        curBook:" << curBook << " already scanned-> ignore" << endl;
                    curBookIdx++; continue;
                }
                scannedBooks.insert(curBook);
                scanningSolution.appendBook(curLibId, curBook);
                //cout << "    day:" << day << " lib:" << curLibId << " scanBook:" << curBook << " score:" << bookScoresList[curBook] << endl;
                curBookIdx++;
                i++;
            }
            currentBookIndex[curLibId] = curBookIdx;
        }
    }
}

*/
//----------------------------- debug output

void InitSolution::printCurrentBookIndex(map<int, int> &currentBookIndex) {
    cout << "currentBookIndex: " << endl;
    for (map<int, int>::iterator it = currentBookIndex.begin(); it != currentBookIndex.end(); it++) {
        cout << "libId = " << it->first << " curIndex = " << it->second << endl;
    }
}


void InitSolution::printLibSequence(vector<int> &libSequence) {
    cout << "lib sequence: " << endl;
    for (vector<int>::iterator it = libSequence.begin(); it != libSequence.end(); it++) {
        cout << *it << " " << endl;
    }
}


