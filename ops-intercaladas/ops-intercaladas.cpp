#include <utility>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//juez online http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=930

// Varios typedefs
typedef vector<int> Vec;
struct Celda {
    bool exists;
    bool belongs;
    int op; // 0: +, 1: x, 2: ^
};
typedef vector< vector<Celda> > Tablero;

// Prototipado de funciones
void resolver(Vec& p, int n, int k);
void mostrar(Vec& p, int n, int k);

/**
 * La función main toma el tablero por std input:
 * recibe primero el tamaño de bloque (si se le pasa n se
 * asume un bloque de n*n, con lo cual la matriz final será
 * de (n*n)*(n*n)). Luego recibe un numero por cada casillero
 * del tablero. Un cero indica casilla vacia.
 * Finalmente, llama al método resolver(...) y al finalizar éste
 * se muestra el resultado (de haberlo).
 */
int main()
{
	int n;
	int k;

    cin >> k >> n;
    if(cin.eof()){
        return 0;
    }
    
    Vec p = Vec(n, 0);
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        p[i] = num; 
    }

    resolver(p,n,k);

	return 0;
}

void resolver(Vec& p, int n, int k) {
    // inicializo
    Tablero q = Tablero(n, vector<Celda>(k+1, Celda()));
    q[0][0].exists = true;
    q[0][0].op = -1;
    for (int j = 1; j < k+1; j++) {
        q[0][j].exists = false;
        q[0][j].op = -1;
    }

    // resuelvo
    for (int j = 0; j < k+1; j++) {
        if (p[0] == j) {
            q[0][j].exists = true;
            q[0][j].belongs = true;
            q[0][j].op = -1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < k+1; j++) {
            q[i][j].exists = false;
            if (q[i-1][j].exists) {
                q[i][j].exists = true;
                q[i][j].belongs = false;
            } else if (j - p[i] >= 0 && q[i-1][j-p[i]].exists) {
                q[i][j].exists = true;
                q[i][j].belongs = true;
            }
        }
    }    
    
    // imprimo tabla
    cout << "k   ";
    for (int j = 0; j < k+1; j++) {
        printf("%2d  ", j);
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        printf("%2d: ", p[i]);
        for (int j = 0; j < k+1; j++) {
            if (q[i][j].exists) {
                if (q[i][j].belongs) {
                    cout << " I  ";
                } else {
                    cout << " O  ";
                }
            } else {
                cout << " -  ";
            }
        }
        cout << endl;
    }

    // hay solucion ?
    bool sol = false;
    for (int i = 0; i < n; i++) {
        if (q[i][k].belongs) {
            sol = true;
            break;
        }
    }

    if (!sol) {
        cout << "No hay solucion para k=" << k << endl;
        return;
    }

    // imprimo solucion
    cout << "Solucion: \n" << k << "=";
    while (k > 0) {
        for (int i = 0; i < n; i++) {
            if (q[i][k].belongs) {
                cout << p[i];
                k = k - p[i];
                if (k != 0) {
                    cout << "+";
                }
                break;
            }
        }
    }
    cout << endl;
}

void mostrar(Vec& p, int n, int k) {
    for (int i = 0; i < n; i++) {
        cout << p[i];
    }
    cout << endl;
}
