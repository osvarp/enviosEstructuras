
/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack; 

/*
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|  Estructura Stack |<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
*/

struct Node{
	int item;
	Node *next;
};

struct Stack{
	Node *head;

	int (*peek) ( Stack * );
	void (*pop) ( Stack * );
	void (*push) ( Stack *, int );
	void (*kill) ( Stack * );
	int (*empty) ( Stack * );
};

int peek( Stack * );
void pop ( Stack * );
void push ( Stack *, int );
void kill ( Stack * );
int empty ( Stack * );

/*
Nombre: createStack
Descripcion: crea un elemento del TAD Stack. Inicializa los valores y vincula las operaciones al 'objeto'.
Complejidad: O(1)
*/
Stack createStack(){
	Stack s;
	s.head = NULL;
	s.peek = peek;
	s.pop = pop;
	s.push = push;
	s.kill = kill;
	s.empty = empty;
	return s;
}

/*
Nombre: peek
Entrada: un puntero a un elemento de la estructura Stack
Salida: un entero que representa el último valor guardado en el Stack
Complejidad: O(1)
*/
int peek( Stack *s ){
	int res;
	if ( s->head == NULL ){
		/*fprintf( stderr, "Error: El stack esta vacio: peek no tiene ningun elemento a devolver.\n" );*/	
		res = -1;
	} else {
		res = (s->head)->item;
	}
	return res;
}
/*
Nombre: pop
Entrada: un puntero a un elemento de la estructura Stack
Descripcion: elimina el ultimo elemento añadido en la Stack.
Complejidad: O(1)
*/
void pop ( Stack *s ){
	if ( s->head == NULL ){
		/*fprintf( stderr, "Error: El stack esta vacio: pop no tiene ningun elemento a eliminar.\n" );*/
	} else {
		Node *tmp = s->head;
		s->head = (s->head)->next;
		free( tmp );
	}
}
/*
Nombre: push
Entrada: un puntero a un elemento de la estructura Stack y un entero 'v'
Descripcion: crea un nodo para guardar el entero ´v´ dentro del Stack.
Complejidad: O(1)
*/
void push( Stack *s, int v ){
	Node *new = (Node*) malloc ( sizeof ( Node ) );
	new->next = s->head;
	new->item = v;
	s->head = new;
}
/*
Nombre: kill
Entrada: un puntero a un elemento de la estructura Stack
Descripcion: Elimina todos los nodos del Stack
Complejidad: O(n), donde n es la cantidad de elementos en el Stack
*/
void kill( Stack *s ) {
	Node *tmp;
	while ( s->head != NULL ){
		tmp = s->head;
		s->head = (s->head)->next;
		free( tmp );
	}
}
/*
Nombre: empty
Entrada: un puntero a un elemento de la estructura Stack
Salida: un entero que toma valor 1 si el Stack esta vacio, 0 de lo contrario.
Complejidad: O(1)
*/
int empty( Stack *s ){
	int res = ( s->head == NULL );
	return res;
}

/*
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|  analisis complejidad  |<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>

La solución se basa en la operacion 'actualizar', la que manipula la variable 'j' y el Stack 's' dependiendo del
	tren que nos encontramos leyendo en el input. Esta operación se invoca tantas veces como trenes que leemos, si
	llamamos 'n' a la cantidad de trenes del caso, estaremos invocando 'actualizar' 'n' veces.

La operación 'actualizar' no necesariamente funciona en tiempo constante, pues en la peor invocación, el while del
	tercer condicional iteraria n-1 veces. Sin embargo, este while funciona en base al valor al que apunta 'j', el
	cual solo es reiniciado al inicio de cada caso, por lo que en todas las 'n' invocaciones a 'actualizar' combinadas,
	este while itera 'n' veces. Es por esto que la operacion 'actualizar' funciona en O(1) amortizado.

T(n) = n * O(1)amortizado
T(n) = O(n)

funciona en tiempo lineal

|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>| Solucion del problema  |<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>|<_|>
*/

void leer();
void actualizar( int, int, Stack *, int * );

int main(){
	leer();
	return 0;
}
/*
Nombre: leer
Descripcion: realiza el proceso de lectura e invoca a las operaciones respectivas.
*/
void leer(){
	int n, i, flag = 0, tmp, j;
	Stack s = createStack();
	while ( scanf("%d", &n) != EOF ){
		
		if ( flag ){
			printf("\n");
		} else {
			flag = 1;
		}

		scanf("%d", &tmp);
		while( tmp != 0 ){
			j = 1;
			for ( i = 1 ; i < n ; ++i ){
				actualizar( n, tmp, &s, &j );
				scanf("%d", &tmp );
			}
			
			actualizar( n, tmp, &s, &j );


			if ( s.empty( &s ) ){
				printf("Yes\n");
			} else{
				printf("No\n");
			}

			s.kill( &s );

			scanf("%d", &tmp );
		}
		getc( stdin );
	}
}
/*
Nombre: actualizar.
Entrada: un entero 'n' que representa el mayor número con el que identificaremos a un tren en este caso, 
			un entero 'act' que es el entero que representa el número del tren que estamos procesando, un
			puntero a una Stack 's' que representa a los trenes represados en la estacion, un puntero a entero
			'j' que posee la información sobre el proximo tren que llegara a la estacion.
Descripcion: Si el último tren que llego es igual a 'act' o si el proximo tren que llega es igual a 'act', sabemos
			que este tren debe salir. Esto se representa quitando un elemento del Stack (cuando el ultimo tren que 
			llego es 'act') o agregandole 1 al valor al que 'j' apunta ( cuando el proximo tren es 'act' ). De lo
			contrario, tenemos que esperar a que lleguen suficientes trenes como para que 'act' sea el siguiente, 
			representado al agregarle mediante 'push' los valores intermedios al Stack 's'.
*/
void actualizar( int n, int act, Stack *s, int *j ){
	if ( *j == act ){
		*j += 1;
	} else if ( act == s->peek( s ) ){
		s->pop( s );
	} else {
		while ( *j < act ){
			s->push( s, *j );
			*j += 1;
		}
		*j += 1;
	}
}
