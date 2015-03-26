#include <functional>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

typedef pair<int, int> Coord;

int main() {
    // Cantidad de puntos
    int n;
    cin >> n;
    vector<Coord> puntos(n);

    // Tomo los datos del input para generar el MinHeap
    for(int i = 0; i < n; i++) {
        int f, c;
        cin >> f;
        cin >> c;
        puntos[i] = Coord(f,c);
    }

    // Ordeno los puntos de acuerdo a su coordenada x. Si todos los puntos tienen la misma coordenada x, ordeno los puntos de acuerdo a su coordenada y, y para el resto del algoritmos pienso las coordenadas intercambiadas.

    // Trazo una recta vertical que divida al conjunto en dos partes R1 y R2 de manera tal que la cantidad de puntos en cada parte sea lo mas cercano posible a la mitad del total.

    // Calculo la distancia minima en la union de los dos conjuntos. d = min(d1, d2)
    // Elimino los puntos que estan a distancia mayor a d de la recta vertical que separa a R1 y R2
    // Ordeno los puntos en cada Ri de acuerdo al valor de la coordenada y
    // Calculo la distancia de cada uno de los puntos a sus vecinos (son a lo sumo 5). Si cualquiera de estas distancias es menor que d, actualizar el valor de d.
}
