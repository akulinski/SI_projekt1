#ifndef DIAGNOZA_H
#define DIAGNOZA_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>


using namespace std;
class Diagnoza
{
public:
    Diagnoza(string,string,string);
    void result();
    void printAns();
    void wTyl(string str);
private:
    vector<vector<string>> rules;
    vector<pair<string,bool>> facts;
    vector<string> aswers;
    //pierwszy int odpowaida pierwszemu boolowi 2 int 2 boolowi
    vector<pair<pair<int,int>,pair<bool,bool>>> constraints;
    //pomysl dodatkowa para do okreselenia czy bylo wczytwyana juz dana zmienna
    vector<pair<string,bool>> var;
    vector<string> split(string s,char c);
    void getVariables();
    bool checkCons(int index);
    bool get_var(string& str);
    bool checkVec(vector<bool>& vec);
    void setVar(bool b,string& str);
    bool checkIfAllready(string str,int index);
    //funkcja do sprawdzenia constraintow i ustawaienia zmiennych

};

#endif // DIAGNOZA_H
