#include <utility>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Varios typedefs
typedef vector<string> Vec;
typedef vector<Vec> Tabla;

// Prototipado de funciones
void resolver(string x, string y);

int main()
{
	string x;
	string y;
    cin >> x;
    cin >> y;

    resolver(x, y);
	return 0;
}

void resolver(string x, string y) {
    int x_len = x.length();
    int y_len = y.length();

    Tabla matriz(x_len+1, Vec(y_len+1, ""));
    for (int i = 1; i <= x_len; i++) {
        for (int j = 1; j <= y_len; j++) {
            if (x[i-1] == y[j-1]) {
                matriz[i][j] = matriz[i-1][j-1] + x[i-1];
            } else {
                if(matriz[i][j-1].length() >= matriz[i-1][j].length()) {
                    matriz[i][j] = matriz[i][j-1];
                } else {
                    matriz[i][j] = matriz[i-1][j];
                }
            }
        }
    }

    // muestro la solucion por stdout
    cout << matriz[x_len][y_len] << endl;
}
