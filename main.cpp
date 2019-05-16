#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream fin("PDA.in");
ifstream in("Words.in");

int nrq, nrAlf, nrAlfSt, nrTrans;
char q[25];
char alf[25], alfSt[25];
char Q1[50], Q2[50];
char lit[50], inSt[50];
char simbInitSt;
char start;
string addSt[50];

void read(){
///reading the number of states and the states
    fin >> nrq;
    for (int i = 0; i < nrq; i++)
        fin >> q[i];

///reading the number of letters and the letters
    fin >> nrAlf;
    for (int i = 0; i < nrAlf; i++)
        fin >> alf[i];

///reading the number of the stack's letters and the stack
    fin >> nrAlfSt;
    for (int i = 0; i < nrAlfSt; i++)
        fin >> alfSt[i];

    fin >> start;       ///start
    fin >> simbInitSt;  ///first element in the stack
    fin >> nrTrans;     ///number of transitions

///reading the transitions (q1, letter, what is put in the stack, q2, top of the stack)
    for (int i = 0; i < nrTrans; i++)
        fin >> Q1[i] >> lit[i] >> inSt[i] >> Q2[i] >> addSt[i];
}


bool wordChecking(char state, string word, string stackk){
    string stackk2, s;
    ///if the word was read and if the stack is empty, is OK
    if((word == "") && (stackk == ""))
        return true;
    else{
        ///reading the transitions
        for(int j = 0; j < nrTrans; j++){
            if (lit[j] == '-'){
                ///if the word and stack are empty
                if ((state == Q1[j]) && (inSt[j] == '-')){
                    s = stackk;
                    if (addSt[j] != "-")
                        stackk2 = addSt[j];
                        else
                            stackk2 = "";
                    stackk2 = stackk + s;
                    if (wordChecking(Q2[j], word, stackk2))
                        return true;
                }
                ///if the word is empty but the stack has elements, continue without stackk[0]
                if((state == Q1[j]) && (stackk[0] == inSt[j])){
                    s = stackk.substr(1);
                    if(addSt[j] != "-")
                        stackk2 = addSt[j];
                        else
                            stackk2 = "";
                    stackk2 += s;
                    if (wordChecking(Q2[j], word, stackk2))
                        return true;
                }
            }
            ///if the stack is empty
            if((state == Q1[j])&& (word[0] == lit[j]) && (inSt[j]=='-')){
                s = stackk;
                if (addSt[j] != "-")
                    stackk2 = addSt[j];
                    else
                        stackk2 = "";
                stackk2 += s;
                if (wordChecking(Q2[j], word.substr(1), stackk2))
                    return true;
            }
            ///if the stack has elements
            if((state == Q1[j]) && (word[0] == lit[j]) && (stackk[0] == inSt[j])){
                s = stackk.substr(1);
                if (addSt[j] != "-")
                    stackk2 = addSt[j];
                    else
                        stackk2 = "";
                stackk2 += s;
                if(wordChecking(Q2[j], word.substr(1), stackk2))
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    int nrCuv;
    in >> nrCuv;
    read();
    string word, stackk;
    for (int i = 0; i < nrCuv; i++){
        in >> word;
        cout << word;
        stackk = simbInitSt;
        if(wordChecking(start, word, stackk) == true)
            cout <<"\nAccepted!\n";
        else
            cout <<"\nRejected!\n";
    }
    return 0;
}
