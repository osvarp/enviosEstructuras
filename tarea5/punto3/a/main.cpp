/*
Oscar Vargas Pabon
Punto 3-a
*/

#include <stdio.h>

#include "lista.h"

void insertarEnListaOrdenada(Lista* l, int v);

int main(){
	Lista l = Lista();

	insertarEnListaOrdenada(&l, 10);
	l.display();
	l.elimLista(1);
	l.display();

	insertarEnListaOrdenada(&l, 9);
	insertarEnListaOrdenada(&l, 11);
	l.display();

	insertarEnListaOrdenada(&l, 11);
	insertarEnListaOrdenada(&l, 10);
	insertarEnListaOrdenada(&l, 1);
	insertarEnListaOrdenada(&l, 101);
	insertarEnListaOrdenada(&l, 20);
	l.display();

	int a;
	printf("Escribir -0- para salir:\n");
	scanf("%d",&a);
	while ( a != 0 ){
		insertarEnListaOrdenada(&l, a);
		l.display();
		scanf("%d",&a);
	}

	return 0;
}

/*
		Complejidad:
En el mejor de los casos, 'vaciaLista' retorna 1 y 'anxLista' se hace en tiempo constante (porque el 'act' de lista == NULL. 
	o no entra al while, por lo que j==1 y 'insLista' se hace en tiempo constante.
T(n) = O(1)
En el peor de los casos, 'v' es mayor a todos los elementos de la lista, por lo que el while itera 'n' veces. Cada iteracion
	del while, se invoca la funcion 'infoLista' con parametro 'j'. La complejidad de la funcion 'infoLista' es lineal
	dependiendo de 'j'.
       n          n      n
T(n) = Σ (i-1) =  Σ i  - Σ 1
      i=1        i=1    i=1
T(n) = (n^2 + n)/2 - n
T(n) = (n^2)/2 - n/2
T(n) = O(n^2)
*/

/*
Nombre: insertarEnListaOrdenada
Entrada: un puntero a lista 'l' y un entero 'v'.
Descripcion: recorre la lista hasta encontrar la poscicion en donde se debe insertar el entero 'v' de tal manera que 
				quede ordenado.
*/
void insertarEnListaOrdenada(Lista* l, int v){
	if (l->vaciaLista()){
		l->anxLista( v );
	} else {
		int j = 1, n = l->longLista();
		while ( j <= n && v > l->infoLista(j) ){
			++j;
		}
		/*printf("j = %d, n = %d, v = %d\n",j,n,v);*/
		if ( j <= n ){
			l->insLista(v, j);
		} else {
			l->anxLista( v );
		}
	}
}