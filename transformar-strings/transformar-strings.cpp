#include <utility>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define CAMBIAR 0
#define AGREGAR 1
#define BORRAR 2
#define NOP 3

struct celda {

	celda() : action(-1), parcial("") {}
	celda(int action, string x) : action(action), parcial(x) {}

	int action;
	string parcial;
};

typedef vector<celda> Vec;
typedef vector< vector<string> > Tabla;

// Prototipado de funciones
void resolver(string x, string y);
double coincidencias(string x, string y);
string lcs(string x, string y);
string borrar_c(string x, int pos);
string agregar_c(string x, int pos, char c);

int main()
{
	string x;
	string y;
    cin >> x;
    cin >> y;

    resolver(x, y);
	return 0;
}

double coincidencias(string x, string y) {
	return double(lcs(x, y).length()) / double(max(x.length(), y .length()));
}

string lcs(string x, string y) {
    int x_len = x.length();
    int y_len = y.length();

    Tabla matriz(x_len+1, vector<string>(y_len+1, ""));
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

    return matriz[x_len][y_len];
}

string borrar_c(string x, int pos) {
	string principio = x.substr(0,pos);
	string fin = "";
	if (pos+1 < x.length()) {
		fin = x.substr(pos+1,x.length());
	}
	principio += fin;
	return principio;
}

string agregar_c(string x, int pos, char c) {
	string principio = x.substr(0,pos);
	string fin = "";
	if (pos < x.length()) {
		fin = x.substr(pos,x.length());
	}
	principio += c;
	principio += fin;
	return principio;
}

void resolver(string x, string y) {
    int x_len = x.length();
    int y_len = y.length();

    Vec cambios(y_len+1, celda());
	cambios[0].action = NOP;
	cambios[0].parcial = x;
	cout << "X: " << cambios[0].parcial << endl;

	for (int i = 1; i <= y_len; i++) {
		int len_aux = cambios[i-1].parcial.length();
		if(len_aux == y_len) {
			string str_aux = cambios[i-1].parcial;
			bool difieren = false;
			for (int j = 0; j < len_aux; j++) {
				if (str_aux[j] != y[j]) {
					str_aux[j] = y[j];
					difieren = true;
					break;
				}
			}
			if (difieren) {
				// cambio un caracter
				cambios[i].action = CAMBIAR;
				cambios[i].parcial = str_aux;
			} else {
				// x e y titnen misma longitud y mismos caracteres, o sea que son iguales
				cambios[i].action = NOP;
				cambios[i].parcial = cambios[i-1].parcial;
			}
		} else if (len_aux > y_len) {
			// borro un caracter
			// busco cual es el caracter que al eliminarlo maximiza las coincidencias
			string str_aux = cambios[i-1].parcial;
			double max_matches = coincidencias(str_aux, y);
			string max_str = str_aux;
			for (int j = 0; j < len_aux; j++) {
				if (j >= y_len || str_aux[j] != y[j]) {
					string aux = borrar_c(str_aux, j);
					double nuevo_matches = coincidencias(aux, y);
					if (nuevo_matches > max_matches) {
						max_matches = nuevo_matches;
						max_str = aux;
					}
				}
			}
			cambios[i].action = BORRAR;
			cambios[i].parcial = max_str;
		} else {
			// agrego un caracter
			// busco cual es el caracter que al agregarlo maximiza las coincidencias
			string str_aux = cambios[i-1].parcial;
			double max_matches = coincidencias(str_aux, y);
			string max_str = str_aux;
			for (int j = 0; j < y_len; j++) {
				if (j >= len_aux || str_aux[j] != y[j]) {
					string aux = agregar_c(str_aux, j, y[j]);
					double nuevo_matches = coincidencias(aux, y);
					if (nuevo_matches > max_matches) {
						max_matches = nuevo_matches;
						max_str = aux;
					}
				}
			}
			cambios[i].action = AGREGAR;
			cambios[i].parcial = max_str;
		}
		if (cambios[i].action != NOP) {
			cout << i << ": " << cambios[i].parcial << endl;
		}
	}
	cout << "Y: " << cambios[y_len].parcial << endl;
}
