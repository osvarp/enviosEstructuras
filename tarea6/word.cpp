/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
Complejidad:
La solucion del problema se realiza en la funcion 'cuantosPosibles'. Esta itera por sobre todos los elementos de la
	lista. Por cada mapa de la lista, se realiza un ciclo que itera 1 vez (en el mejor caso) o 'k' veces (en el peor caso)
	donde 'k' es el tamaño del mapa. Cada vez que este segundo ciclo itera, se realiza una invocacion a 'act.find()'.
Se puede decir que en el mejor caso (en donde la primera letra de cada mapa de la lista es mayor a la cantidad de apariciones
	esta palabra entre las letras actuales), se realiza en T(n) = O(n * log m) donde 'n' representa la cantidad de elementos
	en la lista y 'm' representa la cantidad de letras en el mapa de las letras actuales.
El peor caso se da cuando todas las palabras en la lista se pueden formar con las letras dadas. En este caso el ciclo 
	while anidado itera 'k' veces. Si [k, k1, ..., kn] representa el 'k' de cada palabra en la lista, las complejidad
	del peor caso esta dada por:
       n                            n
T(n) = Σ ( ki * log m ) = (log m) * Σ ki
      i=1                          i=1
Sin embargo, notese que ki < 26, por lo que:
 n
 Σ ki < 26*n
i=1
lo que implica que
 n
 Σ ki = O(n)
i=1
Por esto en el peor caso el problema se resuelve en:
T(n) = O(n * log m)

En el peor y el mejor caso dio T(n) = O(n * log m)
*/

#include <stdio.h>
#include <map>
#include <list>

void leer();
int cuantosPosibles( std::map<char, int> &, std::list<std::map<char,int>> & );

int main(){
	leer();
	return 0;
}
/*
Nombre: leer
Descripcion: Se realiza el proceso de lectura e impresion. Invoca las operaciones necesarias para resolver el problema.
*/
void leer(){
	std::list<std::map<char,int>> palabras;
	std::map<char,int> tmp;
	std::map<char,int>::iterator mapValue;
	char t = getc( stdin ) ;
	int res;
	while ( t != '#' ){
		while( t != '\n' ){
			mapValue = tmp.find( t );
			if ( mapValue == tmp.end() ){
				tmp.insert( std::pair<char,int>( t, 1 ) );
			} else {
				(*mapValue).second += 1;
			}
			t = getc( stdin );
		}
		t = getc( stdin );
		palabras.push_back( tmp );
		tmp.clear();
	}

	t = getc( stdin );
	t = getc( stdin );
	while ( t != '#' ){
		while( t != '\n' ){
			mapValue = tmp.find( t );
			if ( mapValue == tmp.end() ){
				tmp.insert( std::pair<char,int>( t, 1 ) );
			} else {
				(*mapValue).second += 1;
			}
			t = getc( stdin );
		}
		t = getc( stdin );
		res = cuantosPosibles( tmp, palabras );
		printf( "%d\n", res );
		tmp.clear();
	}
	palabras.clear();
}

/*
Nombre: cuantosPosibles
Entrada: una lista de mapas 'cmp' que representa las palabras que queremos ver si pueden ser formadas. Un mapa 'act' que
			representa las letras que tenemos a disposcicion.
Salida: un entero que indica la cantidad de palabras de 'cmp' que pueden ser formadas con las letras de 'act'
*/
int cuantosPosibles( std::map<char, int> &act, std::list<std::map<char,int>> &cmp ){
	std::list<std::map<char,int>>::iterator it;
	std::map<char,int>::iterator mapIt;
	std::map<char,int>::iterator mapValue;
	bool flag;
	int ans = 0;
	for ( it = cmp.begin() ; it != cmp.end() ; ++it ){
		mapIt = (*it).begin(); 
		flag = true;
		while ( mapIt != (*it).end() && flag ){
			mapValue = act.find( (*mapIt).first );
			if ( mapValue == act.end() || (*mapValue).second < (*mapIt).second ){
				flag = false;
			}
			++mapIt;
		}
		if ( flag ){
			++ans;
		}
	}
	return ans;
}
