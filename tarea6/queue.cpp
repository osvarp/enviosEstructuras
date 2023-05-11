/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
	Complejidad:


'P' es igual a la poblacion del caso
'C' es igual al numero de 'E x' o 'N' que tiene el caso

La operacion 'emergency' realiza una invocación a la funcion 'find' de los mapass, la cual se hace en tiempo O(log n), y, 
	en ocasiones, también invoca a la operacion 'insert' de los mapas, la cual es tambien en tiempo O( log n ). Es por esto
	que la operacion 'emergency' se realiza en tiempo O(log P)

La funcion 'getNext' consta de tres ciclos while ( no anidados ) , los cuales hacen una invocacion a la funcion
	'find' de los mapas en cada iteración. 
	Analizemos el primer ciclo: "while ( !s.empty() && flag ){":
		- La variable 'flag' se vuelve false si el valor que estaba en el tope de la pila es mapeado a un numero positivo,
			sigue siendo true de lo contrario. Sin embargo, en cada iteración va a descartar un elemento de la pila. 
			Como la operacion 'emergency' es la unica parte donde se añaden elementos a la pila, podemos vincular cada
			iteración que este primer ciclo realiza con una invocacion a 'emergency'. De esta manera le podemos vincular
			el coste de las iteraciones fallidas a la operacion 'emergency'. 
	Analizemos el segundo ciclo: "while ( turno <= n && flag )":
		- La variable 'flag' se vuelve false si la variable 'turno' no lo encuentra en el mapa, lo que implica que se
			hace una invocacion a la funcion 'find' en cada iteracion. La variable 'turno' solo se reinicia al terminar
			el caso, por lo que, este while itera 'P' veces durante todas las invocaciones a 'getNext' en un solo caso.
	Analizemos el tercer ciclo: "while ( flag ){":
		- La variable 'flag' se vuelve false si el valor que se encuentra en frente de la cola es mapeado a 1 o -1. De lo
			contrario, reduce el valor absoluto del valor al que es mapeado en 1. Este valor solo es aumentado por la
			operacion 'emergency', sin embargo puede ser reducido en el primer ciclo (si este ciclo descarta el valor) . 
			Esto significa que esta persona es descartada (por estar repetida) en el primer ciclo o en este. De igual 
			manera le vinculamos el coste de las operaciones fallidas a 'emergency'.
	Donde 'h' son las invocaciones a 'getNext', se realiza en tiempo h*T(h) = O( P * log P + h * log P ). Notese que 
		el segundo ciclo solo puede iterar 'P' veces si 'h' >= 'p', por lo que h*logP > P*logP y h*T(h) = O( h * log P )

'emergency' sigue con un coste relacionado O(log P) porque cada elemento repetido generado por 'emergency' solo requiere
	1 iteracion en el primer o segundo ciclo de 'getNext' para ser corregido. 
Si 's' son las invocaciones a 'emergency', entonces tenemos que 'h'+'s' = 'C' y la complejidad del ejercicio es un multiplo de:
	h*logP + s*logP = C * log P 
	Si 'P'>'C' entonces P*logP > C*logP y de lo contrario C*logC > P*logP por lo que si n := max( P, C ), donde 'max' es una funcion que devuelve el mayor
	entonces la complejidad de la solucion es T(n) = O( n * log n )

T(n) = O( n * log n )
*/


#include <stdio.h>
#include <queue>
#include <stack>
#include <map>

void leer();
int getNext( std::queue<int> &, std::stack<int> &, std::map<int,int> &, int, int &, bool );
void emergency( std::stack<int> &, std::map<int,int> &, int );
void kill ( std::queue<int> &, std::stack<int> & );

int main(){
	leer();
	return 0;
}
/*
Nombre: leer
Descripcion: realiza el proceso de lectura e invoca a las operaciones respectivas. Ademas imprime.
*/
void leer(){
	int P,C;
	int i, tmp, anterior;
	std::queue<int> q;
	std::stack<int> s;
	std::map<int,int> mapa;
	char t;
	int turno;
	int cas = 1;
	bool modo;
	scanf("%d %d",&P, &C);
	while ( P != 0 ) {
		printf("Case %d:\n", cas);
		++cas;

		turno = 1;
		anterior = 0;
		modo = P < C ;

		getc( stdin ); /* para deshacerse del '\n' */
		for ( i = 0 ; i < C ; ++i ){
			t = getc( stdin );
			if ( t == 'N' ){
				tmp = getNext( q, s, mapa, P, turno, modo );
				printf("%d\n", tmp );
			} else {
				scanf("%d", &tmp);
				emergency( s, mapa, tmp );
				tmp = 0;
			}
			getc( stdin ); /* para deshacerse del '\n' */

		}
		scanf("%d %d",&P, &C);
		
		mapa.clear();
		kill( q, s );
	}
}

/*
Nombre: getNext
Entrada: una queue<int> 'q' que contiene los elementos en una cola ( cuando el modo lo permite ). Un stack<int> 's' que 
			tiene almacenados los elementos que han pasado por el comando 'E'. un map<int,int> 'mapa' que gestiona
			los elementos repetidos en 'q' y 's'. un entero 'n' que representa 'P'. Un entero pasado por referencia
			'turno' que representa el orden inicial (cuando todos estan ordenados 1..P ). Un booleano 'modo' que 
			determina si es necesario llevar la cola 'q' o realmente 'turno' jamas sobrepasara 'n'.
Salida: Un numero que representa la persona a atender para el comando 'N'.
*/
int getNext( std::queue<int> &q, std::stack<int> &s, std::map<int,int> &mapa, int n, int &turno, bool modo ){
	int res;
	bool flag = true;
	std::map<int,int>::iterator mapValue;
	while ( !s.empty() && flag ){
		res = s.top();
		s.pop();
		mapValue = mapa.find( res );
		if ( (*mapValue).second > 0 ){
			(*mapValue).second *= -1;
			flag = false;
			if ( modo ){
				q.push( res );
			}
		} else {
			(*mapValue).second += 1;
		}
	}

	while ( turno <= n && flag ){
		res = turno;
		++turno;
		mapValue = mapa.find( res );
		if ( mapValue == mapa.end() ){
			flag = false;
			mapa.insert( std::pair<int,int>( res, 1 ) );
			if ( modo ){
				q.push( res );
			}
		} 
	}

	while ( flag ){
		res = q.front();
		q.pop();
		mapValue = mapa.find( res );
		if ( (*mapValue).second < -1 ){
			(*mapValue).second += 1;
		} else if ( (*mapValue).second > 1 ){
			(*mapValue).second -= 1;
		} else {
			flag = false;
			q.push( res );
		}
	}
	
	return res;
}
/*
Nombre: emergency
Entrada: una stack<int> 's' que contiene las personas previas que se han beneficiado del comando 'E'. un map<int,int> 
			'mapa' con el que prevendremos duplicados. Un entero 'v' que representa la persona que recibe el comando 'E'.
Descripcion: realiza el comando 'E' con la persona 'v'.
*/
void emergency( std::stack<int> &s, std::map<int,int> &mapa, int v ){
	s.push( v );
	std::map<int,int>::iterator mapValue = mapa.find( v);
	if ( mapValue != mapa.end() ){
		if ( (*mapValue).second < 1 ){
			(*mapValue).second *= -1;		
		}
		(*mapValue).second = (*mapValue).second + 1;
	} else {
		mapa.insert( std::pair<int,int>( v, 1 ) );
	}
}

/*
Nombre: kill
Entrada: una queue<int> 'q' y una stack<int> 's'.
Descripcion: vacia 'q' y 's'.
*/
void kill ( std::queue<int> &q, std::stack<int> &s ){
	while ( !q.empty() ){
		q.pop();
	}
	while ( !s.empty() ){
		s.pop();
	}
}


