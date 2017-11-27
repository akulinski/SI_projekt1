#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "diagnoza.h"

using namespace std;

int main()
{
    string rules="C:\\Users\\Albert\\Desktop\\build-SI_projekt1-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\rules.txt";
    string constraints="\\C:\\Users\\Albert\\Desktop\\build-SI_projekt1-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\constraints.txt";
    string facts="C:\\Users\\Albert\\Desktop\\build-SI_projekt1-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\facts.txt";
    Diagnoza d1(rules,constraints,facts);
    d1.result();
    d1.printAns();
    cout<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------WNIOSKOWANIE W TYl-----------------------------"<<endl;
    cout<<"------------------------------------WPROWADZ NAZWE ZMIENNEJ KTORA CHCESZ WNIOSKOWAC"<<endl;
    string x;
    do{
        getline(cin,x);
        d1.wTyl(x);
    }
    while(x!="q");




    return 0;
}

