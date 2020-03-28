#ifndef INITSOLUTION_H
#define INITSOLUTION_H
#include <vector>
#include <iostream>
#include <ScanningSolution.h>
#include <Library.h>
#include <set>
#include <map>
//#include <pair>

using namespace std;

class InitSolution
{
    public:
        //InitSolution();
        //InitSolution(int dayScan, vector<int> &bookScoresList, vector<Library> &libs);
        InitSolution(int dayScan, vector<int> &bookScoresList, vector<Library> &libs);
        virtual ~InitSolution();
        void generateSolution(ScanningSolution &scanningSolution);
        void generateSolutionM(ScanningSolution &scanningSolution);
        void setDayScan(const int dayScan) {
            this->dayScan = dayScan;
        }
        void setBookScoresList(vector<int> &bookScoresList) {
            this->bookScoresList = bookScoresList;
        }
        void setLibs(vector<Library> &libs) {
            this->libs = libs;
        }


        //bool compareBooks(int book1, int book2);


    protected:

    private:
        void libQuicksort(vector<int> &values, int left, int right);
        int libPartition(vector<int> &values, int left, int right);
        void sortBooks();
        int dayScan;
        vector<int> &bookScoresList;
        //set<int> bookScannedList;
        vector<Library> &libs;
        int computeLibScore(Library &lib, const int daysLeft, vector<bool> &scannedBooks);
        void printCurrentBookIndex(map<int, int> &currentBookIndex);
        void printLibSequence(vector<int> &libSequence);

};

#endif // INITSOLUTION_H
