#ifndef SCANNINGFRAMEWORK_H
#define SCANNINGFRAMEWORK_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Library.h>
#include <InitSolution.h>
#include <ScanningSolution.h>


using namespace std;

class ScanningFramework
{
    public:
        ScanningFramework(string inputName, string outputName);
        virtual ~ScanningFramework();
        void dumpBookScoreList();
        void dumpLibs();
    protected:

    private:
        //const int maxNumLibraries = 10;
        const int maxNumLibraries = 50;
        string inputName;
        string outputName;
        int numBooks;
        int numLibs;
        int dayScan;
        vector<int> bookScoresList;
        vector<Library> libs;
        InitSolution *pInitSolution;
        ScanningSolution *pScanningSolution;
        int computeThreshold();
        void read(int &numBooks, int &numLibs, int &dayScan, vector<int> &bookScoresList, vector<Library> &libs, int threshold);
        void read(int &numBooks, int &numLibs, int &dayScan, vector<int> &bookScoresList, vector<Library> &libs);
        ScanningSolution *generateInitSolution();

};

#endif // SCANNINGFRAMEWORK_H
