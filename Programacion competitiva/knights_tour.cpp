#include<iostream>
#include<vector>
#define N 8
using namespace std;

int movX[N] = {2, 1, -1, -2, -2, -1, 1, 2};
int movY[N] = {1, 2, 2, 1, -1, -2, -2, -1};

bool esSeguro(int x, int y, vector<vector<int>> &tablero){
    return (0 <= x && x < N && 0 <= y && y < N && tablero[x][y] == -1);
}

bool resolverKT(int x, int y, int mov, vector<vector<int>> &tablero){
    if(mov == N*N){
        return true;
    }
    for(int i = 0; i < N; i++){  //  N para revisar todos los movimientos
        int nextX = x + movX[i];
        int nextY = y + movY[i];  
        if(esSeguro(nextX, nextY, tablero)){
            tablero[nextX][nextY] = mov;
            if(resolverKT(nextX, nextY, mov + 1, tablero)){
                return true;
            }
            tablero[nextX][nextY] = -1; // backtracking
        }
    }
    return false;
}

void knightsTour(){
    vector<vector<int>> tablero(N, vector<int>(N, -1));
    tablero[0][0] = 0;
    if(resolverKT(0, 0, 1, tablero)){
        for(auto &fila : tablero){
            for(auto &x : fila){
                cout << x << " "; 
            }
            cout << endl;
        }
    }
    else{
        cout << "no hay solución :c\n";
    }
}

int main(){
    knightsTour();
    return 0;
}