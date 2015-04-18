#include <utility>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Varios typedefs
#define SUMA 0
#define MULT 1
#define POTE 2
typedef vector<int> Vec;

struct solucion {

    solucion(int numeros) : valida(false), ops(numeros-1, SUMA) {}

    bool valida;
    Vec ops;
};

// Prototipado de funciones
solucion resolver(Vec& p, int n, float k);
int operar(int a, int b, int op);
void mostrar(Vec& p, Vec& ops, int n, int k);
bool es_sol(Vec& p, int n, Vec& ops, int k);

int operar(int a, int b, int op) {
    if(op == SUMA) {
        return a + b;
    } else if(op == MULT) {
        return a * b;
    } else {
        return a ^ b;
    }
}

bool es_sol(Vec& p, int n, Vec& ops, int k) {
    if (n == 0) {
        return false;
    } else if (n == 1) {
        return k == p[0];
    } else {
        int ac = operar(p[0],p[1],ops[0]);
        for (int i = 2; i < n; i++) {
            ac = operar(ac, p[i],ops[i-1]);
        }
        return k == ac;
    }
}

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

    solucion sol = resolver(p,n,float(k));
    if (sol.valida) {
        mostrar(p, sol.ops, n, k);
    } else {
        cout << "No existe secuencia de operaciones para k=" << k << endl;
    }
	return 0;
}

solucion resolver(Vec& p, int n, float k) {
    if (n == 0) {
        return solucion(1);
    } else if (n == 1) {
        if(p[0] == k) {
            solucion sol(1);
            sol.valida = true;
            return sol;
        } else {
            return solucion(1);
        }
    } else {
        solucion sol(n);
        solucion s1 = resolver(p, n-1, k-p[n-1]);
        if (s1.valida) {
            //cout << "1: " << k-p[n-1] << endl;
            for (int i = 0; i < n-2; i++) {
                sol.ops[i] = s1.ops[i];
            }
            sol.ops[n-2] = SUMA;
            sol.valida = true;
            return sol;
        }
        solucion s2 = resolver(p, n-1, k/p[n-1]);
        if (s2.valida) {
            //cout << "2: " << k/p[n-1]  << endl;
            for (int i = 0; i < n-2; i++) {
                sol.ops[i] = s2.ops[i];
            }
            sol.ops[n-2] = MULT;
            sol.valida = true;
            return sol;
        }
        solucion s3 = resolver(p, n-1, pow(k, float(1)/float(p[n-1])));
        if (s3.valida) {
            //cout << "3: " << pow(k, float(1)/float(p[n-1])) << endl;
            for (int i = 0; i < n-2; i++) {
                sol.ops[i] = s3.ops[i];
            }
            sol.ops[n-2] = POTE;
            sol.valida = true;
            return sol;
        }

        return solucion(n);
    }
}

void mostrar(Vec& p, Vec& ops, int n, int k) {
    cout << k << " = ";
    for (int i = 0; i < n-1; i++) {
        string op = "";
        if (ops[i] == SUMA) {
            op = "+";
        } else if (ops[i] == MULT) {
            op = "*";
        } else {
            op = "^";
        }
        cout << p[i] << op;
    }
    cout << p[n-1] << endl;
}
