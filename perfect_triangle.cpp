#include <iostream>
#include <string>
using namespace std;

void trianguloPerfecto(const string& cadena) {
    int longitud = cadena.length();
    int nivel = 1;

    int pos = 0;
    while (pos + nivel <= longitud) {
        for (int i = 0; i < nivel; ++i) {
            cout << cadena[pos];
            ++pos;
        }
        cout << endl;
        ++nivel;
    }
}

int main() {
    string cadena;
    cout << "Introduce una cadena: ";
    cin >> cadena;

    trianguloPerfecto(cadena);

    return 0;
}
