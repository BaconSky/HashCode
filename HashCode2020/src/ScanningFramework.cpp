#include "ScanningFramework.h"

ScanningFramework::ScanningFramework(string inputName, string outputName) : inputName(inputName), outputName(outputName) {
    //this->inputName = inputName;
    //this->outputName = outputName;
    pInitSolution = nullptr;
    cout << "ScanningFramework ctor read data" << endl;
    int threshold = computeThreshold();
    cout << "ScanningFramework ctor threshold = " << threshold << endl;
    read(numBooks, numLibs, dayScan, bookScoresList, libs, threshold);
    cout << "ScanningFramework ctor new InitSolution dayScan = " << dayScan << endl;

    pInitSolution = new InitSolution(dayScan, bookScoresList, libs);
    //initSolution.setDayScan(dayScan);


    //initSolution.setBookScoresList(bookScoresList)
    //initSolution.setLibs(libs);
    //dumpBookScoreList();
    //cout << "ScanningFramework ctor dumpLibs" << endl;

    //dumpLibs();
    //cout << "ScanningFramework ctor bookScoreList" << endl;
    //dumpBookScoreList();
    cout << "pos1ScanningFramework c-tor generateInitSolution" << endl;
    pScanningSolution = generateInitSolution();
    cout << "ScanningFramework c-tor pos5 solution generated --- going to save data" << endl;
    pScanningSolution->save("dataout.txt", bookScoresList);
    cout << "ScanningFramework c-tor Final Score: " << pScanningSolution->calculateScore(bookScoresList) << endl;
    //pScanningSolution.generateSolution();
}

int ScanningFramework::computeThreshold() {
    ifstream dtin(inputName);
    int numBooks;
    int numLibs;
    int dayScan;
    int dummy;
    dtin >> numBooks >> numLibs >> dayScan;

    cout << "computeThreshold numLibs=" << numLibs << endl;
    for (int i = 0; i < numBooks; i++) {
        int score;
        dtin >> score;
    }
    vector<int> signupTime;
    signupTime.reserve(numLibs);
    for (int i = 0; i < numLibs; i++) {
        int numBooksLib;
        int suTime;
        dtin >> numBooksLib;
        dtin >> suTime;
        signupTime.push_back(suTime);
        dtin >> dummy; //maxBooksPerDay;
        for (int j = 0; j < numBooksLib; j++) {
            dtin >> dummy;
        }
    } // for libs
    dtin.close();
    sort(signupTime.begin(), signupTime.end());

    //cout << "????????????????? sign up time : " << endl;
    //for (vector<int>::iterator it = signupTime.begin(); it != signupTime.end(); it++) cout << *it << " ";
    //cout << endl;
    if (maxNumLibraries > signupTime.size()) return *(signupTime.end());
    return signupTime[maxNumLibraries];

}

void ScanningFramework::read(int &numBooks, int &numLibs, int &dayScan, vector<int> &bookScoresList, vector<Library> &libs, int threshold) {
    ifstream dtin(inputName);
    int numLibsRaw;
    dtin >> numBooks >> numLibsRaw >> dayScan;
    bookScoresList.reserve(numBooks);
    for (int i = 0; i < numBooks; i++) {
        int score;
        dtin >> score;
        bookScoresList.insert(bookScoresList.end(), score);
    }
    //libs.reserve(numLibsRaw);
    numLibs = 0;
    for (int i = 0; i < numLibsRaw; i++) {
        Library lib(i);
        dtin >> lib;
        if (lib.getSignUpTime() <= threshold) {
            libs.insert(libs.end(), lib);
            //cout << "ScanningFramework::read use lib id = " << lib.getId() << endl;
        }
    }
    numLibs = libs.size();
    dtin.close();

}


void ScanningFramework::read(int &numBooks, int &numLibs, int &dayScan, vector<int> &bookScoresList, vector<Library> &libs) {
    ifstream dtin(inputName);
    dtin >> numBooks >> numLibs >> dayScan;
    bookScoresList.reserve(numBooks);
    for (int i = 0; i < numBooks; i++) {
        int score;
        dtin >> score;
        bookScoresList.insert(bookScoresList.end(), score);
    }
    libs.reserve(numLibs);
    for (int i = 0; i < numLibs; i++) {
        Library lib(i);
        dtin >> lib;
        libs.insert(libs.end(), lib);
    }
    dtin.close();

}


void ScanningFramework::dumpBookScoreList() {
    int i = 0;
    for (vector<int>::iterator it = bookScoresList.begin(); it != bookScoresList.end(); it++) {
        cout << i << "->" << *it << " ";
        i++;
    }
    cout << endl;
}

void ScanningFramework::dumpLibs() {
    for (vector<Library>::iterator it = libs.begin(); it != libs.end(); it++) {
            cout << *it;
    }
    cout << endl;
}


ScanningSolution *ScanningFramework::generateInitSolution() {
    ScanningSolution *pScanningSolution = new ScanningSolution();
    ScanningSolution &scanningSolution = *pScanningSolution;
    //pInitSolution->generateSolution(scanningSolution);
    pInitSolution->generateSolutionM(scanningSolution);
    cout << " ScanningFramework::generateInitSolution() finished" << endl;
    return pScanningSolution;
}

ScanningFramework::~ScanningFramework()
{
    delete pScanningSolution;
}
