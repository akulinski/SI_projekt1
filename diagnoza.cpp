#include "diagnoza.h"
#include <algorithm>

Diagnoza::Diagnoza(string rulesLocation,string constraintsLocation,string factsLocation)
{
    string line;
    ifstream fileRules;
    cout<<"\n------------------------wczytywanie zasad--------------------------------------------- \n";
    try{
        //wczytanie zasad
        int i=0;
        fileRules.open(rulesLocation);
        while(getline(fileRules,line)){
            cout<<line<<endl;
            this->rules.push_back(split(line,','));
            i++;
        }
        cout<<"Rules OK"<<endl;
        fileRules.close();
    }
    catch(...){
        cerr<<"\n sorry someone messed up :( \n";
    }

    cout<<"\n------------------------wczytywanie ogarniczen----------------------------------------- \n";
    ifstream fileConstraints;
    try{
        int i=0;
        fileConstraints.open(constraintsLocation);
        while(getline(fileConstraints,line)){
            //chwilowy wektor zeby rozbić linię
            vector<string> tmp;
            tmp=split(line,',');
            //zapisanie do ogarniczeń sprawdzenei w który miejscu jest iterator
            //i odpowiwednie zapisanie int musi być równy numerowi w wektorze zasad(+1)
            //trzeba napisać funkcje która ustawi zmiennne

            constraints[i].first.first=stoi(tmp[0]);
            constraints[i].first.second=stoi(tmp[1]);
            //ustwaienie zmiennych w ten sposob ze w ogarniczeniach wcześniejszy warunek jest prawda a drugi fałszem
            constraints[i].second.first=true;
            constraints[i].second.second=false;

        }
        cout<<"Constraints OK"<<endl;
        fileConstraints.close();
    }

    catch(...){
        cerr<<"\n someone messed up \n";
    }
    ifstream fileFacts;
    try{
        cout<<"\n------------------------wczytywanie faktow--------------------------------------------- \n";
        fileFacts.open(factsLocation);
        vector<string> tmp;

        while(getline(fileFacts,line)){
            tmp=split(line,',');


            for(unsigned int i=0;i<tmp.size();i++){
                facts[i].first=tmp[i];
                cout<<tmp[i]<<" "<<endl;
                facts[i].second=true;
            }
        }
        cout<<"Facts OK"<<endl;
    }
    catch(...){
        cerr<<"\n someone messed up \n";
    }




    getVariables();
    result();
}



vector<string> Diagnoza::split(string s, char c){

    vector<string> v;
    //ustawienie pozycji na początek napisu i znalezienie litery
    string::size_type i = 0;
    string::size_type j = s.find(c);
    //poki przedni wskaznik nie jest nposem
    while (j != string::npos) {
        v.push_back(s.substr(i, j-i));
        //zamiana miejsca i na miejce j +1
        i = ++j;
        j = s.find(c, j);

        if (j == string::npos)
            v.push_back(s.substr(i, s.length()));
    }

    return v;
}


//wczytywanei danych
void Diagnoza::getVariables(){
    for(unsigned int i=0;i<rules.size();i++){
        pair<string,bool> tmpPair;
        tmpPair.first=rules[i][1];;
        tmpPair.second=false;
        var.push_back(tmpPair);
        //druga zmienna w parze jest sprawdzana pod względem tego czy
        //znajduje sie w ogarniczeniach jeżeli nie to ustawiana jest na true

        bool tmpCons=checkCons(i);
        if(tmpCons==false){
            var[i].second=false;
        }
        //jeżeli dal danego indeksu zmienna jest fałszem znaczy ze jest w ogarniczeniach
        if(var[i].second==false)
            continue;
        string tmpFacts=facts.at(i).first;
        string tmpVar=var.at(i).first;
        if(tmpFacts==tmpVar){
            var[i].second=true;
        }
    }

}

bool Diagnoza::checkCons(int index)
{

    //przeiterowanie przez zmienne sprawdzenie nazwy zmiennej i jeżlei zgadza sie nazwa to ustawienie 2 zmiennej na false

    for(int i=0;constraints.size();i++){
        //podaje index zmiennej któRą chce ustawić na false
        if(index==constraints[i].first.second){
            return false;
        }
    }
    return true;
}

void Diagnoza::result(){
    vector<string> results;
    for(unsigned int i=0;i<rules.size();i++){
        vector<string> tmp;
        tmp=rules[i];//chwilowa zmienna do przeiterowania i zdobycia wartosci logicznej zmiennej
        bool res;//wynik sprawdzania wektora booli
        vector<bool> resultVec;
        for(unsigned int j=2;j<tmp.size();j++){
            resultVec.push_back(get_var(tmp[j]));
        }
        res=checkVec(resultVec);
        if(res==true){
            //ustawic wartos logiczna tej zmiennej na true i wpisac do wektora wynikow
            setVar(true,tmp[1]);
            //wrzucenie nazwy zmiennej ktora okazala sie prawdziwa do wektora odpowiedzi
            this->aswers.push_back(tmp[1]);
        }
        else{
            //jezeli okazalo sie falszem to ustawienie zmiennej ktora jest wynkiem wnioskowania na false
            setVar(false,tmp[1]);
        }
    }
}


bool Diagnoza::get_var(string& str){

    for(unsigned int i=0;i<var.size();i++){
        if(var[i].first==str){
            return true;
        }
    }
    return false;
}

bool Diagnoza::checkVec(vector<bool>& vec){


    for(unsigned int i=0;i<vec.size();i++){
        if(vec[i]==false){
            return false;
        }
    }

    return true;

}

void Diagnoza::setVar(bool b,string& str){

    for(unsigned int i=0;i<var.size();i++){
        if(var[i].first==str){
            var[i].second=b;
        }
    }
}
bool Diagnoza::checkIfAllready(string str,int index){
    for(int i=0;i<index;i++){
        if(str==aswers[i]){
            return true;
        }
    }
    return false;
}

void Diagnoza::printAns(){
    for(unsigned int i=0;i<aswers.size();i++){
        string tmp=aswers[i];
        if(!checkIfAllready(tmp,i)){
        cout<<aswers[i]<<endl;
        }
    }
}

void Diagnoza::wTyl(string str){


    vector<string> tmp;
    for(unsigned int i=0;i<rules.size();i++){
        if(str==rules[i][1]){
            tmp=rules[i];
            vector<pair<string,bool>> pytania;

            for(unsigned int i=2;i<tmp.size();i++){
                bool ask;
                char l;
                cout<<"Czy prawda jest "<<tmp[i]<<" T/N"<<endl;
                cin>>l;
                pair<string,bool> pr;
                if(l=='T'){
                    pr.first=tmp[i];
                    pr.second=true;
                    pytania.push_back(pr);
                }
                if(l=='N'){
                    pr.first=tmp[i];
                    pr.second=false;
                    pytania.push_back(pr);
                }
            }

            bool ans=true;
            for(unsigned int i=0;i<pytania.size();i++){
                if(pytania[i].second==false){
                    ans=false;
                }
            }

            if(ans==true){
                cout<<endl;
                cout<<"To jest prawda"<<endl;
            }
            else{
                cout<<endl;
                cout<<"To nie jest prawda"<<endl;
            }
        }
    }


}
