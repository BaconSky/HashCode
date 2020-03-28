#ifndef SCANNINGSOLUTION_H
#define SCANNINGSOLUTION_H
#include <LibrarySchedule.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class ScanningSolution
{
    public:
        ScanningSolution();
        virtual ~ScanningSolution();
        //ScanningSolution::ScanningSolution(LibrarySchedule libSchedules)
        void appendLibrarySchedule(LibrarySchedule librarySchedule);
        map<int, LibrarySchedule> &getLibSchedules() {return libSchedules;}
        void appendBook(int libId, int book);
        LibrarySchedule& getLibSchedule(int libId) {return libSchedules[libId];}
        string toString();
        void save(string filename, vector<int>& bookScoresList);
        int calculateScore(vector<int>& bookScoresList);
    protected:

    private:
        map<int, LibrarySchedule> libSchedules;


};

#endif // SCANNINGSOLUTION_H
