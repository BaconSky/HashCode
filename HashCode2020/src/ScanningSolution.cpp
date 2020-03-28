#include "ScanningSolution.h"

ScanningSolution::ScanningSolution()
{
    //ctor
}

string ScanningSolution::toString() {
    string str;
    for (map<int, LibrarySchedule>::iterator it = libSchedules.begin(); it != libSchedules.end(); it++) {
        str += it->second.toString();
    }

    return str;

}

ScanningSolution::~ScanningSolution()
{
    //dtor
}


void ScanningSolution::appendLibrarySchedule(LibrarySchedule librarySchedule) {
    int libId = librarySchedule.getId();
    libSchedules.insert(pair<int, LibrarySchedule>(libId, librarySchedule));
}

void ScanningSolution::save(string filename, vector<int>& bookScoresList) {
    ofstream dataout(filename);
    //int score = 0;
    dataout << libSchedules.size() << endl;
    for (map<int, LibrarySchedule>::iterator it = libSchedules.begin(); it != libSchedules.end(); it++) {
        dataout << it->first << " " << it->second.getBookSequenceSize() << endl;
        for (vector<int>::iterator ir = it->second.getBookSequence().begin(); ir != it->second.getBookSequence().end(); ir++) {
            dataout << *ir << " ";
            //score += bookScoresList[*ir];
        }
        //cout << endl <<" -----score: " << score << endl;
        dataout << endl;
    }

    dataout.close();
}

int ScanningSolution::calculateScore(vector<int>& bookScoresList) {
    int score = 0;
    for (map<int, LibrarySchedule>::iterator it = libSchedules.begin(); it != libSchedules.end(); it++) {
        for (vector<int>::iterator ir = it->second.getBookSequence().begin(); ir != it->second.getBookSequence().end(); ir++) {
            score += bookScoresList[*ir];
        }
    }
    return score;
}

void ScanningSolution::appendBook(int libId, int book) {
    //cout << "appendBook pos1 lib id = " << libId << " book = " << book << endl;
    //cout << "appendBook cur scanning solution = " << toString() << endl;
    //cout << " lib schedules toString " << libSchedules[libId].toString() << endl;
    libSchedules[libId].appendBook(book);
    //cout << "append book pos 3" << endl;
}
