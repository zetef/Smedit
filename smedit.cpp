#include <fstream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <streambuf>

using namespace std;

std::fstream parolein("parole.in");
std::ofstream paroleout("parole.out");
std::fstream parola("parole.txt");
std::fstream editor1("stef.in");
std::fstream conturi;
std::fstream logare("logare.io");
std::fstream conturi_temp;

string n, nume, extensie, username, pass;
vector<string> loc;
int acces = 0, i1, b, n1, alegere, contor = 0, pozitie;
bool logat = 0;

int main()
{
    int editor();
    void cont();
    void logsignsys();
    void verificare_parola();
    cout << "(1)Sign-up & (2)Login" << endl;
    cin >> alegere;
    if(alegere == 1){
        conturi.open("conturi.io", std::fstream::in | std::fstream::out | std::fstream::ate);
        cout << "(o data logat cand alegi pe login alegi contul)" << endl;
        cout << "username: "; cin >> username;
        cout << "password: "; cin >> pass;
        conturi << username << " " << pass << endl;
        loc.push_back(username);
        logat = 1;
        logare << logat;
        main();
        conturi.close();
    }
    if(alegere == 2){
        if(logat){
            logsignsys();
        }
        if(!logat){
            logsignsys();
            }else{
                conturi.open("conturi.io", std::fstream::in | std::fstream::out);
                verificare_parola();
            }
        }else{
            cout << "Faceti-va mai intai cont!" << endl;
            main();
        }
        conturi.close();
}

int editor(){
    editor1 >> nume >> extensie;
    nume += extensie;
    ofstream out(nume.c_str());
    while(getline(editor1, n)){
        if(n == "$stop")
            editor();
        if(n == "$stopf")
            return 0;
        while(n.length() == 0)
            getline(editor1, n);
        if(!editor1.eof())
            out << n << " ";
        out << endl;
    }
    editor1.close();
    logat = 1;
    return 0;
}

void cont(){
    cout << "Bun venit, " << loc[pozitie] << "!" << endl;
    cout << "0.Delogare" << endl << "1.Editor" << endl << "2.Sterge cont" << endl; cin >> alegere;
    if(alegere == 0){
        logat = 1; contor = 1; main();
    }else if(alegere == 1)
        editor();
    else if(alegere == 2){
        cout << "Esti sigur? Toate datele ti se vor sterge! 1(da)/0(nu)" << endl; cin >> alegere;
        if(alegere == 1){
            int pozitie1 = pozitie + 1;
            cout << "merge";
            loc.erase(loc.begin()+pozitie, loc.begin()+pozitie1 + 1);
            cout << endl << "inca mai merge" << endl;
            cout << loc[pozitie] << " " << loc[pozitie1] << endl;
            main();
        }
        if(alegere == 0)
            cont();
    }
}

void verificare_parola(){
    cout << "Trebuie sa introduceti parola: "; cin >> pass;
    if(pass == loc[pozitie + 1]){
        cont();
    }else{
        cout << "Gresit! Vreti sa mai incercati? 1(da)/0(nu)"; cin >> alegere;
        if(alegere == 0){
            contor = 1;
            main();
        }
        if(alegere == 1){
            verificare_parola();
        }
    }
}

void logsignsys(){
    conturi.open("conturi.io", std::fstream::in | std::fstream::out);
    cout << "alege cont: " << endl;
    if(contor == 0)
        while(conturi >> username)
            loc.push_back(username);
    for(unsigned int i = 0; i < loc.size(); i += 2){
        if(i == 0)
            cout << i + 1 << " " << loc[i] << endl;
        else
            cout << i / 2 + 1 << " " << loc[i] << endl;
    }
    conturi.close();
    cin >> alegere;
    if(alegere == 1){
        pozitie = alegere - 1;
        verificare_parola();
    }
    if(alegere == 2){
        pozitie = alegere;
        verificare_parola();
    }
    for(int j = 3; j <= loc.size()/2; j++){
        if(alegere == j){
            pozitie = alegere + (alegere - 2);
            verificare_parola();
        }
    }
}
