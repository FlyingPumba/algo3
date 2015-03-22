#include <utility>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

//juez online http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=930

// Varios typedefs
typedef pair<int, int> Coord;
// Celda: <peso, <previous_x, previous_y>>
typedef pair<int, Coord> Celda;
typedef vector<Celda> Vec;
typedef vector<Vec> Tablero;

// Prototipado de funciones
void resolver(Tablero& p, int n, int m);
void mostrar(Tablero& p, int n, int m);

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
	int m;

    cin >> m >> n;
    if(cin.eof()){
        return 0;
    }
    
    Tablero p(m, Vec(n, Celda(-1, Coord(-1,-1))));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int peso;
            cin >> peso;
            //cout << i << "," << j << ": " << peso <<"\n";
            p[i][j] = Celda(peso, Coord(-1,-1));
        }
    }
    p[0][0].second = Coord(0,0);

    resolver(p,n,m);

	return 0;
}

void resolver(Tablero& p, int n, int m)
{
    // calculo las sumas parciales de la primer fila y la primer columna
    for (int i = 1; i < n; i++) {
        p[i][0].second = Coord(i-1,0);
        p[i][0].first = p[i][0].first + p[i-1][0].first;
    }
    for (int i = 1; i < m; i++) {
        p[0][i].second = Coord(0,i-1);
        p[0][i].first = p[0][i].first + p[0][i-1].first;
    }

    // calculo las sumas parciales para el resto de la tabla, mientras voy armando el camino
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            // me fijo si es mejor llegar a la celda (i,j) desde arriba o desde la izquierda
            // TODO que pasa si hay empate ?
            if (p[i-1][j].first <= p[i][j-1].first) {
                // vengo desde arriba
                p[i][j].second = Coord(i-1,j);
                p[i][j].first = p[i][j].first + p[i-1][j].first;
            } else {
                // vengo desde la izquierda
                p[i][j].second = Coord(i,j-1);
                p[i][j].first = p[i][j].first + p[i][j-1].first;
            }
        }
    }

    // armo el camino de vuelta
    vector<Coord> camino(n+m-1, Coord(-1,-1));
    int n_aux = n-1;
    int m_aux = m-1;
    int contador = 0;
    while (!(n_aux == 0 && m_aux == 0)) {
        camino[n+m - contador - 2] = Coord(n_aux,m_aux);
        int a = p[n_aux][m_aux].second.first;
        int b = p[n_aux][m_aux].second.second;
        n_aux = a;
        m_aux = b;
        contador = contador + 1;
    }
    camino[0] = Coord(0,0);

    // imprimo el camino
    cout << "Camino:\n";
    for (int i = 0; i < n+m-1; i++) {
        cout << "(" << camino[i].first << "," << camino[i].second << ")\n";
    }
    cout << "Costo total: " << p[n-1][m-1].first << endl;
}

void mostrar(Tablero& p, int n, int m){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << p[i][j].first << "(" << p[i][j].second.first << "," << p[i][j].second.second << ") ";
        }
        cout << endl;
    }
}
