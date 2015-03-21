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
void mostrar(const Tablero& m);
int check(const Tablero& c, int n);
bool algunRepetido(const Vec &v);

bool aux_resolver(Tablero& p, int n, Coord anterior);
bool valido(Tablero& p, int n, Coord& actual, int k);

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
	Coord principio(0, 0);
	return aux_resolver(p, n, principio);
}

bool aux_resolver(Tablero& p, int n, Coord actual)
{
	//Encuentro proxima coordenada a rellenar
	bool encontroActual = p[actual.first][actual.second] == 0;
	while (actual.first < n*n && !encontroActual){
		if (actual.second < n*n-1){
			actual.second++;
		} else {
			actual.second = 0;
			actual.first = actual.first + 1;
		}
		if (actual.first < n*n && p[actual.first][actual.second] == 0)
			encontroActual = true;
	}

	//Si no encontro un actual, ya no hay mas nada para completar 
	//(es precondicion que el tablero 'p' sea valido)
	if (!encontroActual)
		return true;

	//Sino, trato de completar el actual con todos los numeros de 1 a n*n
	for (int i = 1; i <= n*n; i++){
		if (valido(p, n, actual, i)){
			p[actual.first][actual.second] = i; //pongo Coordenada
			bool resuelto = aux_resolver(p, n, actual); //llamada recursiva
			if (resuelto){
				return true;
			}else{
				p[actual.first][actual.second] = 0; //saco Coordenada
			}
		}
	}

	return false;
}

bool valido(Tablero& p, int n, Coord& actual, int k)
{
	//Me fijo si se va a repetir k en la fila o columna de 'actual'
	for (int j = 0; j < n*n; j++){
		//recorro la fila y la columna al mismo tiempo
		if (p[actual.first][j] == k || p[j][actual.second] == k)
			return false;
	}

	//(x,y) es el origen del subcuadrado al que pertenece 'actual'
	int x = actual.first - actual.first % n;
	int y = actual.second - actual.second % n;
	//Me fijo si se va a repetir k en el subcuadrado de 'actual'
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (p[x+i][y+j] == k)
				return false;
		}
	}

	return true;
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

