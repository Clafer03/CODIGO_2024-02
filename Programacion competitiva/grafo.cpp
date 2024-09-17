#include<iostream>
#include<vector>
using namespace std;

struct Nodo{
    int valor; //valor del nodo
    vector<Nodo*> vecinos; //punteros a los vecinos

    Nodo(int v) : valor(v) {} 
};

struct grafo{
    vector<Nodo*> nodos; //lista de nodos en el grafo

    void addNodo(int valor){
        Nodo* nuevoNodo = new Nodo(valor);
        nodos.push_back(nuevoNodo);
    }

    Nodo* buscarNodo(int valor){
        for(Nodo* nodo : nodos){
            if(nodo->valor == valor){
                return nodo;
            }
        }
        return nullptr;
    }

    void addArista(int valor1, int valor2){
        Nodo* nodo1 = buscarNodo(valor1);
        Nodo* nodo2 = buscarNodo(valor2);

        if(nodo1 && nodo2){
            nodo1->vecinos.push_back(nodo2);
            nodo2->vecinos.push_back(nodo1);
        }

    }

    void mostrarGrafo() {
        for (Nodo* nodo : nodos) {
            cout << "Nodo " << nodo->valor << ":";
            for (Nodo* vecino : nodo->vecinos) {
                cout << " -> " << vecino->valor;
            }
            cout << endl;
        }
    }

};

void buildGrafo(grafo& g){
    int n = 0;
    int flag = 0;
    int n1;
    int n2;
    cout << "Tam grafo: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        g.addNodo(i+1);
        cout << "Nodo : "<<  i+1 << endl;
    }

    cout << "Conecta nodos\n";
    do
    {   
        cin >> n1 >> n2;
        g.addArista(n1,n2);
        cout << "continuar? [0][1]";
        cin >> flag;
    } while (flag != 0);
}


int main(){
    grafo grafo;

    buildGrafo(grafo);

    // Agregar nodos al grafo
    // grafo.addNodo(0);
    // grafo.addNodo(1);
    // grafo.addNodo(2);
    // grafo.addNodo(3);
    // grafo.addNodo(4);

    // Agregar aristas entre los nodos
    // grafo.addArista(0, 1);
    // grafo.addArista(0, 4);
    // grafo.addArista(1, 2);
    // grafo.addArista(1, 3);
    // grafo.addArista(1, 4);
    // grafo.addArista(2, 3);
    // grafo.addArista(3, 4);

    // Mostrar el grafo
    grafo.mostrarGrafo();

    return 0;
}