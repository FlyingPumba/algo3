#include <utility>
#include <vector>
#include <iostream>
using namespace std;

//juez online http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=930

// Varios typedefs
typedef vector<int> Vec;
typedef vector<Vec> Tablero;
typedef pair<int, int> Coord;

// Prototipado de funciones
bool resolver(Tablero& p, int nsubs);
bool resolverAux(Tablero& p, int nsubs, Coord& c);
void mostrar(const Tablero& m);
int check(const Tablero& c, int n);
bool algunRepetido(const Vec &v);

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

	while(true) {
		cin >> n;
		if(cin.eof()){
			break;
		}
		int n2 = n*n;
		Tablero p(n2, Vec(n2, 0));
		for(int i = 0; i < n2; ++i)
			for(int j = 0; j < n2; ++j)
				cin >> p[i][j];

		bool sol = resolver(p,n);
		if(!sol){
			cout << "El tablero no tene solucion...";
		} else {
			mostrar(p);
		}
		cout << endl;
	}

	return 0;
}

/**
 * Recibe el tablero inicial y el tamaño de bloque.
 * Sugerencia: preparar los datos que sean necesarios
 * para la resolución y luego llamar a un método que se
 * encargue de realizar el algoritmo de backtracking.
 * La sugerencia es para poder elegir los parámetros
 * adecuados sobre los cuales se hará la recurrencia.
 */
bool resolver(Tablero& p, int n)
{
    Coord vacia(-1,-1);
    for (int i = 0; i < n*n; i++) {
        for (int j = 0; j < n*n; j++) {
            if (p[i][j] == 0) {
                vacia = Coord(i,j);
            }
        }
    }

    return resolverAux(p, n, vacia);
}

bool resolverAux(Tablero& p, int n, Coord& c)
{
    // busco la siguient/e celda vacia
    Coord vacia(-1,-1);
    for (int i = c.first; i < n*n; i++) {
        for (int j = c.second; j < n*n; j++) {
            if (p[i][j] == 0) {
                vacia = Coord(i,j);
            }
        }
    }
    // si no hay ninguna celda vacia, el tablero es una solucion
    if (vacia.first == -1 && vacia.second == -1) {
        return true;
    }

    // llamo a resolver poniendo valores en dicha celda desde el 1 al n
    // antes de llamar a resolver con el nuevo valor, me fijo que sea valida
    for (int i = 1; i <= n*n; i++) {
        p[vacia.first][vacia.second] = i;
        
        // block
        int block_y = vacia.second % n;
        int block_x = vacia.first % n;
        bool repetido = false;
        for (int bx = block_x * n; bx < n; bx++) {
            for (int by = block_y * n; by < n; by++ ) {
                if (p[bx][by] == i && bx != vacia.first && by != vacia.second) {
                    repetido = true;
                }
                    
            }
        }

        // row
        for (int j = 0; j < n*n; j++) {
            if (p[j][vacia.second] == i && j != vacia.first) {
                repetido = true;
            }
        }
        // colum
        for (int j = 0; j < n*n; j++) {
            if (p[vacia.first][j] == i && j != vacia.second) {
                repetido = true;
            }
        }

        if (repetido) {
            continue;
        }

        if (resolverAux(p, n, vacia)) {
            return true;
        }
    }
    return false;
}

/**
 * Recibe un tablero y lo muestra por pantalla
 */
void mostrar(const Tablero& m)
{
	cout << endl;
	int n = m.size();
	for(int i = 0; i < n; ++i)
	{
		cout << m[i][0];
		for (int j = 1; j < n; j++)
		{
			cout << " " << m[i][j];
		}
		cout << endl;
	}
}


/**
 * La siguiente función devuelve:
 *    2 --> Si el tablero tiene repetidos en alguna fila, columna o cuadrante
 *    1 --> Si no tiene repetidos y es una solucion de Sudoku
 *    0 --> Si no tiene repetidos pero le faltan casillas por llenar
 */
int check(const Tablero& p, int n)
{
	int n2 = p.size();
	bool ceros = false;
	for (int i = 0; i < n2; i++)
	{
		// verifico la fila i
		Vec flag_fila (n2, 0);
		for (int j = 0; j < n2; j++)
		{
			if (p[i][j] == 0)
				ceros = true;
			else
				flag_fila[p[i][j]-1]++;
		}

		if (algunRepetido(flag_fila))
			return 2;

		// verifico la columna i
		Vec flag_col (n2, 0);
		for (int j = 0; j < n2; j++)
		{
			if (p[j][i] == 0)
				ceros = true;
			else
				flag_col[p[j][i]-1]++;
		}

		if (algunRepetido(flag_col))
			return 2;

		// verifico el cuadrante i
		Vec flag_cuad(n2, 0);
		int f = (i/n)*n; // fila donde empieza el cuadrante
		int c = (i % n)*n; // col donde empieza el cuadrante
		for (int j = 0; j < n; j++)
		for (int k = 0; k < n; k++)
		{
			if (p[f+j][c+k] == 0)
				ceros = true;
			else
				flag_cuad[p[f+j][c+k]-1]++;
		}

		if (algunRepetido(flag_cuad))
			return 2;
	}

	return ceros? 0 : 1;
}

/**
 * Método auxiliar del método check
 */
bool algunRepetido(const Vec& v)
{
	int k = v.size();
	for (int i = 0; i < k; i++)
		if (v[i] > 1)
			return true;

	return false;
}

