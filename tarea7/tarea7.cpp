
/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

#include <stack>
#include <list>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <stdio.h>


/*
Ejercicio 1

complejidad:
	El primer while va a iterar hasta que el ultimo valor de 'l' sea alcanzado, por lo que va a iterar l.back()
	veces. El segundo while va a iterar en todos los valores que no estan en 'l' en el rango de [0,l.back()], 
	por lo que el segundo while va a iterar: l.back() - l.size() veces
n := l.back()
T(n) = O(n)

*/
/*
nombre: elminarPosicionesPila
Entrada: una std::stack<int> 'pil' y una std::list<int> 'l' que es una lista ordenada de manera ascendente en
			donde cada elemento representa una posicion valida en 'pil'
Descripcion: Elimina los valores en 'pil' de todas las posiciones que representan los valores de 'l'
*/
void eliminarPosicionesPila( std::stack<int> &pil, std::list<int> &l ){
	std::stack<int> aux;
	std::list<int>::iterator it = l.begin();
	int i = 0;
	while ( !pil.empty() && it != l.end() ){
		
		if ( i == *it ){
			++it;
		} else{
			aux.push( pil.top() );
		}

		pil.pop();
		++i;
	}
	while ( !aux.empty() ){
		pil.push( aux.top() );
		aux.pop();
	}
}

void testExcercise1(){
	printf("ejercicio 1\n");	
	std::stack<int> pil;
	int aux[] = {0, 2, 5};
	std::list<int> l(aux, aux+3);
	int i;
	for( i = 0 ; i < 7 ; ++i ){
		pil.push( i );
	}
	eliminarPosicionesPila( pil, l );
	while ( !pil.empty() ){
		printf("%d | ", pil.top() );
		pil.pop();
	}
	putc( '\n', stdout );
}

/*
Ejercicio 2

complejidad:
	Se hace una copia de 'vec', lo que tiene una complejidad de O( vec.size() ), luego se invoca a std::make_heap, 
	lo que tambien tiene complejidad de O( vec.size() ). finalmente, se hace un ciclo que itera vec.size() veces
	en el cual se invoca a std::pop_heap(), que funciona en tiempo O(log ( vec.size() ) ).

n := vec.size()
T(n) = O( n log n)

*/
/*
Nombre: ordenarConMonticulo
Entrada: un std::vector<int> 'vec'
Descripcion: ordena utilizando heaps el vector 'vec'
*/
void ordenarConMonticulo( std::vector<int> &vec ){
	std::vector<int> aux(vec);

	std::make_heap( aux.begin(), aux.end() );
	std::vector<int>::iterator it = vec.begin();
	while( !aux.empty() ){
		*it = aux[0];
		std::pop_heap( aux.begin(), aux.end() );
		aux.pop_back();
		++it;
	}
}
void testExcercise2(){
	printf("ejercicio 2\n");
	int aux[] = {12,15,4512,548,21,56,3,5,48,5,7,56,23,45};
	std::vector<int> vec(aux, aux +14);

	ordenarConMonticulo( vec );
	for ( std::vector<int>::iterator it = vec.begin() ; it != vec.end() ; ++it ){
		printf("%d | ", *it);
	}
	putc( '\n', stdout );
}

/*
Ejercicio 3

complejidad:
	la funcion tiene tres whiles. El primero itera mientras los primeros elementos sean iguales. De entre los
	otros dos, solo se itera el caso que estemos considerando (ordenados de mayor a menor o menor a mayor). Como
	dos elementos iguales pueden estar ordenados tanto de mayor a menor como de menor a mayor, entonces estoy
	iterando mientras que el orden se incumpla. Resulto entonces en:
size() es una funcion que retorna la cantidad de elementos es un std::queue
n := size( q )
Mejor caso (no tiene ningun orden y esto se nota con los primeros 3 elementos):
T(n) = O(1)
Peor caso (tiene algun orden, cualquiera de los dos):
T(n) = O(n)
*/
/*
Nombre: verificarOrdenarCola
Entrada: un std::queue<int> 'q'
Salida: retorna un 0 si no hay ningun orden, 1 si esta ordenada de mayor a menor y -1 si esta ordenada de
		menor a mayor.
*/
int verificarOrdenarCola( std::queue<int> q ){
	int ans = 0;
	if ( !q.empty() ){
		ans = 1;
		int anterior = q.front();
		q.pop();
		while ( !q.empty() && q.front() == anterior ){
			q.pop();
		}

		if ( !q.empty() && q.front() > anterior ){
			ans = -1;
			anterior = q.front();
			q.pop();
		} else if ( !q.empty() && q.front() < anterior ){
			ans = 1;
			anterior = q.front();
			q.pop();
		}

		while ( !q.empty() && ans == -1 ){
			ans = ( q.front() > anterior ) ? -1 : 0;
			anterior = q.front();
			q.pop();
		}

		while ( !q.empty() && ans == 1 ){
			ans = ( q.front() < anterior ) ? 1 : 0;
			anterior = q.front();
			q.pop();
		}
	}
	return ans;
}

void testExcercise3(){
	std::queue<int> q1,q2,q3,q4;
	int i;
	q4.push( 20 );
	q3.push( 3 );
	for ( i = 0 ; i < 5 ; ++i ){
		q1.push( i );
		q2.push( 5-i );
		q3.push( 5-i );
		q4.push( i );
	}
	printf(" q1 %d | q2 %d | q3 %d | q4 %d\n", verificarOrdenarCola( q1 ), verificarOrdenarCola(q2), verificarOrdenarCola(q3), verificarOrdenarCola(q4));
}


/*
Ejercicio 4
*/

class MinHeap{
private:
	std::vector<int> heap;
public:
	/*
	constructor
	Entrada: una std::list<int> 'l'
	Descripcion: organiza la lista en el vector 'heap' de tal manera que quede construido un min_heap
	*/
	MinHeap( const std::list<int> &l ){
		/*heap( l.begin(), l.end() );*/
		for ( std::list<int>::const_iterator it = l.cbegin() ; it != l.cend() ; ++it ){
			heap.push_back( *it );
		}
		for ( int i = getParent( l.size() ) ; i >= 0 ; --i ){
			heapify( i );
		}
	}
	/*
	Nombre: getLeftChild
	Entrada: un entero 'n' que representa un nodo del heap
	Salida: un entero que representa el hijo izquierdo del nodo 'n'
	*/
	int getLeftChild( int n ){
		int res = n * 2 + 1;
		return res;
	}
	/*
	Nombre: getRightChild
	Entrada: un entero 'n' que representa un nodo del heap
	Salida: un entero que representa el hijo derecho del nodo 'n'
	*/
	int getRightChild( int n ){
		int res = (n + 1) * 2;
		return res;
	}
	/*
	Nombre: getLeftChild
	Entrada: un entero 'n' que representa un nodo del heap
	Salida: un entero que representa el padre del nodo 'n'
	*/
	int getParent( int n ){
		int res = (n-1)/2;
		return res;
	}
	/*
	Nombre: heapify
	Entrada: un entero 'n' que representa un nodo del heap
	Descripcion: restituye la propiedad de orden del nodo, asumiendo que el nodo 'n' la esta incumpliendo.
	*/
	void heapify( int n ){
		bool flag = true;
		int left = getLeftChild( n ), right, swap, tmp;
		while ( flag && left < heap.size() ){
			right = getRightChild( n );
			swap = n;
			if ( heap[swap] > heap[left] ){
				swap = left;
			}
			if ( right < heap.size() && heap[right] < heap[swap] ){
				swap = right;
			}
			if ( swap == n ){
				flag = false;
			} else {
				tmp = heap[n];
				heap[n] = heap[swap];
				heap[swap] = tmp;
				n = swap;
				left = getLeftChild( n );
			}
		}
	}
	/*
	Nombre: getMin
	Salida: un entero que es el menor numero almacenado en el heap
	*/
	int getMin(){
		int res = heap[0];
		return res;
	}
	/*
	Nombre: pop
	Descripcion: elimina el menor numero almacenado en el heap, restituyendo las propiedades del heap necesarias.
	*/
	void pop(){
		heap[0] = heap[ heap.size() - 1 ];
		heap.pop_back();
		heapify( 0 );
	}
	/*
	Nombre: pop
	Entrada: un entero 'v'
	Descripcion: ingresa el elemento 'v', asegurandose de respetar las propiedades del min_heap
	*/
	void push( int v ){
		int n = heap.size();	
		heap.push_back( v );
		bool flag = true;
		int parent = getParent( n ), tmp;
		while ( flag && n != 0 ){
			if ( heap[parent] > heap[n] ){
				tmp = heap[n];
				heap[n] = heap[parent];
				heap[parent] = tmp;
				n = parent;
				parent = getParent( n );
			} else {
				flag = false;
			}
		}
	}
	/*
	Nombre: empty
	Salida: retorna true si el heap esta vacio, false de lo contrario
	*/
	bool empty(){
		bool res = heap.empty();
		return res;
	}
	/*
	Nombre: size
	Salida: retorna un entero que representa la cantidad de elementos dentro del min_heap
	*/
	int size(){
		int res = heap.size();
		return res;
	}
};
/*
Complejidad obtenerMenorCosto.
	el ciclo while itera l.size()-2 veces, cada vez invocando a la operacion pop de MinHeap que funciona en O(log n)
n:= l.size()
T(n) = O( n log n )
*/
/*
nombre: obtenerMenorCosto
Entrada: una std::list<int> 'l' que tiene los numeros a sumar
Salida: un numero que representa el coste minimo de sumar los elementos de 'l' mediante esta estrategia
*/
int obtenerMenorCosto( std::list<int> &l ){
	MinHeap heap( l );
	int costo = 0, anterior;
	if ( heap.size() > 1 ){
		anterior = heap.getMin();
		heap.pop();
		anterior += heap.getMin();
		costo += anterior;
		heap.pop();
		while ( !heap.empty() ){
			anterior += heap.getMin();
			costo +=  anterior;
			heap.pop();
		}
	}
	return costo;
}
/*
Complejidad obtenerMenorCosto2.
	El ciclo while itera l.size()-2 veces, esto porque reduce en 2 los elementos en el MinHeap pero a su vez lo aumenta
	en 1 durante cada iteracion. Cada vez que itera, invoca a la operacion pop de MinHeap 2 veces y a la operacion push
	1 vez.
n:= l.size()
T(n) = O( n * ( 3 * log n ) )
T(n) = O( n log n )

*/
/*
nombre: obtenerMenorCosto2
Entrada: una std::list<int> 'l' que tiene los numeros a sumar
Salida: un numero que representa el coste minimo de sumar los elementos de 'l' mediante esta estrategia
*/
int obtenerMenorCosto2( std::list<int> &l ){
	MinHeap heap( l );
	int costo = 0;
	int a;
	while ( heap.size() > 1 ){
		a = heap.getMin();
		heap.pop();
		a += heap.getMin();
		heap.pop();
		costo += a;
		heap.push( a );
	}
	return costo;
}

/*
1+2 = 3
3 + 3 = 6
6 + 4 = 10
3 + 6 + 10 = 19
*/

void testExcercise4(){
	int arr[] = { 1, 7,6,4,44, 2};
	std::list<int> l( arr, arr + 6);
	int res;
	res = obtenerMenorCosto( l );
	printf("Primera opcion = %d\n", res );
	res = obtenerMenorCosto2( l );
	printf("Segunda opcion = %d\n", res);
}


/*
ejercicio 5

	Complejidad:
Como solo estoy procesando cada caracter de la expresion 1 vez, considero que es O(n) para 'n' siendo el tamaño del 
	arreglo.
n := size(n)
T(n) = O(n)

*/

/*
Nombre: evaluarExpresionAux
Entrada: un puntero a un arreglo de caracteres como especificado en la entrada de 'evaluarExpresion'
Salida: el resultado de evaluar la expresion.
Nota: esta funcion auxiliar existe para poder 'devolver' el ultimo caracter procesado de algun llamado recursivo.
*/
int evaluarExpresionAux( char **start ){
	int res, numA, numB;
	char operador;

	if ( *(*start) == '(' ){
		++(*start);
		numA = evaluarExpresionAux( start );
	} else {
		numA = *(*start) - '0';
		++(*start);
	}

	operador = *(*start);
	++(*start);

	if ( *(*start) == '(' ){
		++(*start);
		numB = evaluarExpresionAux( start );
	} else {
		numB = *(*start) - '0';
		++(*start);
	}

	if ( operador == '*' ){
		res = numA * numB;
	} else if ( operador == '-' ){
		res = numA - numB;
	} else {
		res = numA + numB;
	}

	/*printf(" %d %c %d = %d\n", numA,operador,numB,res);*/

	++(*start);


	return res;
}
/*
Nombre: evaluarExpresion
Entrada: un arreglo de caracteres que representa una ecuacion bien formada con digitos, parentesis y '*', '-' y '+'
			como operaciones. Cualquier subecuacion debe estar diligentemente demarcada por parentesis.
			Nota: no es necesario el '\0' al final.
Salida: el resultado de evaluar la ecuacion.
*/
int evaluarExpresion( char *expresion ){
	int res = evaluarExpresionAux( &expresion );
	return res;
}

void testExcercise5(){
	char expr1[] = {'(', '4', '+', '5', ')', '*', '3', '\0'};
	char expr2[] = {'(', '4', '+', '5', ')', '*', '(', '7', '-', '2',')', '\0'};
	char expr3[] = {'(', '(', '4', '+', '5', ')', '*', '5', ')', '+','4', '\0'};
	int ans = evaluarExpresion( expr1 );
	printf("%s = %d\n", expr1, ans );
	ans = evaluarExpresion( expr2 );
	printf("%s = %d\n", expr2, ans );
	ans = evaluarExpresion( expr3 );
	printf("%s = %d\n", expr3, ans );


}

/*
ejercicio 6

complejidad:
	hay un while que itera tantas veces como elementos en 'col'. En cada iteracion, se invoca a la operacion 'find' de std::map
	En el peor caso, en cada iteracion tambien se invocara a la operacion 'insert' de std::map. Ambas 'find' e 'insert' 
	funcionan en tiempo O( log n ) donde 'n' son los elementos en el mapa. Es por esto que la complejidad es:
para una función 'size' que retorna la cantidad de elementos en la cola

n := size( col )
T(n) = O( n * ( 2 *log n ) )
T(n) = O( n log n )
*/
/*
Nombre: verificarRepetidos
Entrada: una std::queue<int> 'col'
Salida: un entero que representa cuantos elementos repetidos distintos (ejemplo, si aparece 2 veces 3 o 8 veces 3, solo
			aportara en 1 la respuesta final) se encontraron en la cola 'col'
*/
int verificarRepetidos( std::queue<int> col ){
	std::map<int,bool> repeated;
	std::map<int,bool>::iterator it;
	int res = 0;
	while ( !col.empty() ){
		it = repeated.find( col.front() );
		if ( it == repeated.end() ){
			repeated.insert( std::pair<int,bool>( col.front(), false ) );
		} else if ( (*it).second == false ){
			(*it).second = true;
			++res;
		}
		col.pop();
	}
	return res;
}

void testExcercise6(){
	std::queue<int> col;
	col.push( 5 );
	col.push( 2 ); 
	col.push( 6 ); 
	col.push( 2 ); 
	col.push( 3 ); 
	col.push( 7 ); 
	col.push( 8 ); 
	col.push( 4 ); 
	col.push( 2 ); 
	col.push( 2 ); 
	col.push( 9 ); 
	col.push( 56 ); 
	col.push( 3 ); 
	printf("Hay %d repetidos en col\n", verificarRepetidos( col ));
}

/*
ejercicio 7

Complejidad:
	hay un for que itera para todas los caracteres en 'cad'. En cada iteracion se hace una invocacion a 'find' de std::map.
	En el peor de los casos, tambien hace una invocacion a 'insert' de std::map. Ambas operaciones, 'find' e 'insert', se
	realizan en O( log n ) donde 'n' es la cantidad de elementos en el mapa. 
n := cad.size()
T(n) = O( n * ( 2 * log n ) )
T(n) = O( n log n )
*/

/*
Nombre: obtenerPoscicionesOcurrencias
Entrada: una cadena 'cad'
Salida: un mapa que mapea caracteres a listas. Estas listas contienen las posiciones en 'cad' que tienen el caracter
			que los mapea.
*/
std::map< char, std::list<int> > obtenerPosicionesOcurrencias( std::string &cad ){
	std::map< char, std::list<int> > ans;
	std::map< char, std::list<int> >::iterator mapValue;
	int pos = 0;
	for( std::string::iterator it = cad.begin() ; it != cad.end() ; ++it, ++pos ){
		mapValue = ans.find( *it );
		if ( mapValue == ans.end() ){
			std::list<int> tmp;
			tmp.push_back( pos );
			ans.insert( std::pair< char, std::list<int> >( *it, tmp ) );
		} else{
			((*mapValue).second).push_back( pos );
		}
	}
	return ans;
}

void testExcercise7(){
	std::string cad = "Erase una vez un raton de agudos sentidos que no supo grunir y perecio.";
	std::map< char, std::list<int> > m = obtenerPosicionesOcurrencias( cad );
	std::map< char, std::list<int> >::iterator it;
	std::list<int>::iterator otroIt;
	for ( it = m.begin() ; it != m.end() ; ++it ){
		printf("Letra |%c|\n", (*it).first );
		for ( otroIt = ((*it).second).begin() ; otroIt != ((*it).second).end() ; ++otroIt ){
			printf("Pos %d = |%c|\n", *otroIt, cad[*otroIt]);
		}
	}
}

/*
ejercicio 8
*/

/*
Nombre: crearMatrizDispersa
Entrada: una matriz creada a base de vectores 'vec'
Salida: una matriz dispersa, como especificada en el enunciado
*/
std::vector< std::list< std::pair< int, int > > > crearMatrizDispersa( std::vector< std::vector <int> > &vec ){
	std::list< std::pair< int, int > > tmp;
	std::vector< std::list< std::pair< int, int > > > ans;
	std::vector<int>::iterator colIt;
	int columna;
	for ( std::vector< std::vector <int> >::iterator rowIt = vec.begin() ; rowIt != vec.end() ; ++rowIt ){
		for( colIt = (*rowIt).begin(), columna = 0 ; colIt != (*rowIt).end() ; ++colIt, ++columna ){
			if ( *colIt != 0 ){
				tmp.push_back( std::pair< int, int > ( *colIt, columna ) );
			}
		}
		ans.push_back( tmp );
		tmp.clear();
	}
	return ans;
}

/*
Nombre: crearMapaDisperso
Entrada: una matriz creada a base de vectores 'vec'
Salida: un mapa disperso, como especificado en el enunciado
*/
std::map< int, std::list< std::pair< int, int > > > crearMapaDisperso( std::vector< std::vector <int> > &vec ){
	std::list< std::pair< int, int > > tmp;
	std::map< int, std::list< std::pair< int, int > > > ans;
	std::vector<int>::iterator colIt;
	int columna, fila = 0;
	for ( std::vector< std::vector <int> >::iterator rowIt = vec.begin() ; rowIt != vec.end() ; ++rowIt, ++fila ){
		for( colIt = (*rowIt).begin(), columna = 0 ; colIt != (*rowIt).end() ; ++colIt, ++columna ){
			if ( *colIt != 0 ){
				tmp.push_back( std::pair< int, int > ( *colIt, columna ) );
			}
		}
		if ( tmp.size() > 0 ){
			ans.insert( std::pair< int, std::list< std::pair< int, int > > > ( fila, tmp ) );
		}
		tmp.clear();
	}
	return ans;
}

void testExcercise8();

/*
ejercicio 9

Complejidad
	hay un while que itera tantas veces como elementos en 'col'. En cada iteracion, se invoca a la operacion 'find'
	y a la operacion 'insert' de std::map. Ambas 'find' e 'insert' funcionan en tiempo O( log n ) donde 'n' son los 
	elementos en el mapa. En el mejor caso, el while solo va a iterar dos veces, pues encontrara que los primeros dos
	elementos de 'col' son iguales. En el peor caso, el while va a iterar tantas veces como elementos en 'col', pues
	no hay ningun repetido.
para una función 'size' que retorna la cantidad de elementos en la cola
n := size( col )
En el peor caso:
T(n) = O( n * ( 2 *log n ) )
T(n) = O( n log n )
en el mejor caso:
T(n) = O(1)
*/

/*
Nombre: verificarRepetidosCola
Entrada: una std::queue<int> 'q'
Salida: un booleano que toma valor true si hay al menos 2 elementos en 'q' que tienen el mismo valor. De lo contrario
			toma valor false.
*/
bool verificarRepetidosCola( std::queue<int> q ){
	bool ans = false;
	std::map<int, bool> repetidos;
	std::map<int,bool>::iterator mapValue;
	while ( !ans && !q.empty() ){
		mapValue = repetidos.find( q.front() );
		if ( mapValue != repetidos.end() ){
			ans = true;
		} else{
			repetidos.insert( std::pair< int, bool > ( q.front(), false ) );
		}
		q.pop();
	}
	return ans;
}

void testExcercise9(){
	std::queue<int> q1, q2;
	q1.push( 1 );
	q1.push( 16 );
	q1.push( 15 );
	q1.push( 14 );
	q1.push( 13 );
	q1.push( 12 );
	q1.push( 1 );
	q2.push( 1 );
	q2.push( 16 );
	q2.push( 15 );
	q2.push( 14 );
	q2.push( 13 );
	q2.push( 12 );

	printf("q1 %d | q2 %d\n", verificarRepetidosCola( q1 ), verificarOrdenarCola( q2 ));

}

/*
ejercicio 10

Complejidad
	En el peor de los casos, el ultimo par necesario para completar los 'n' pares va a estar en la ultima posicion
	de 'q'. En este caso, el while va a iterar tantas veces como elementos en 'q'.
n := size( q )
T(n) = O( n )
*/

/*
Nombre: filtrarNParesCola
Entrada: un entero 'n' y una std::queue<int> 'q'
Salida: un std::stack<int> que contiene los primeros 'n' elementos de 'q' que fueron divisibles entre 2.
*/
std::stack < int > filtrarNParesCola( int n, std::queue < int > q ){
	std::stack < int > ans;
	while ( n > 0 && !q.empty() ){
		if ( q.front() % 2 == 0 ){
			ans.push( q.front() );
			--n;
		}
		q.pop();
	}
	return ans;
}

void testExcercise10(){
	std::queue<int> q;
	q.push( 2 );
	q.push( 9 );
	q.push( 7 );
	q.push( 56789890 );
	q.push( 123 );
	q.push( 4 );

	std::stack<int> s = filtrarNParesCola( 3, q );

	while ( !s.empty() ){
		printf("%d | ", s.top() );
		s.pop();
	}
	putc( '\n', stdout );


}


/*
int main(){
	//testExcercise1();
	//testExcercise2();
	//testExcercise3();
	//testExcercise4();
	//testExcercise5();
	//testExcercise6();
	//testExcercise7();
	//testExcercise8();
	//testExcercise9();
	//testExcercise10();

	return 0;
}
*/