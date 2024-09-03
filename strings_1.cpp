#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void segmentar(string p, int len, string &par, string &impar, int &i, int &j){
    for(i=1; i < len; i++){
        impar+=p[i];
        i++;
    }
    for(j = 0; j < len; j++){
        par+=p[j];
        j++;
    }
}

void decoding(string p, int len){
    int i = 0;
    int j = 0;
    string par = "";
    string impar = "";
    if(len % 2 != 0){
        segmentar(p, len, par, impar, i, j);
        reverse(impar.begin(), impar.end());
        cout << "DECODIFICADO :" << impar << par;
    }
    else{
        segmentar(p, len, par, impar, i, j);
        reverse(par.begin(), par.end());
        cout << "DECODIFICADO :" << par << impar;
    }
}

void encoding(string &p, int tam){
    int len = p.length();
    int mid = 0;
    string p_codif = "";
    for(int i = 0; i < tam; i++){
        if(len % 2 != 0){
            mid = len/2;
            p_codif+=p[mid];
            p.erase(mid,1);
            len = p.length();
        }
        else{
            mid = len/2;
            p_codif+=p[mid-1];
            p.erase(mid-1,1);
            len = p.length();
        }
    }
    cout << "CODIFICADO :" << p_codif;
}

int main(){

    string palabrita;
    cout << "Ingrese la palabrita: ";
    cin >> palabrita;

    int len = palabrita.length();
    encoding(palabrita, len);
    decoding(palabrita, len);
    return 0;
}


    // char letra;
    // cout << "> ";
    // cin >> letra;

    // string str = "Un elefante se balanceaba";
    // size_t first = str.find(letra), 
    //     last = str.find_last_of(letra);
    // //string rev(str.begin(), str.end());
    // if(first != string::npos){
    //     cout << "Se encontró " << letra << " en la posición " << first << "\n";
    // }
    // if(last != string::npos){
    //     cout << "La última aparición de " << letra << " esta en la posición " << last << "\n";
    // }
    // //cout << rev << "\n";
