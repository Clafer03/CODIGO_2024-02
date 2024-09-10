#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void deleteSpaces(string &t){
    t.erase(remove(t.begin(), t.end(), ' '), t.end());
}


void perfectTriangle(string t){
    int len = t.length();
    deleteSpaces(t);
    for(int i = 0; i < len; i++){
        
    }
}

int main(){
    string texto;
    cout <<"Ingresa el texto: ";
    cin >> texto;
    perfectTriangle(texto);
}