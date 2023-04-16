/*
Oscar Vargas Pabon
Punto 4-a
*/

#include <stdio.h>
#include "lista.h"

void concatenarListas(Lista& l1, Lista l2);

int main(){
	Lista l1 = Lista();
	Lista l2 = Lista();
	Lista m = Lista();
	int i, n = 10, h = 5;
	for ( i = n ; i > 0 ; --i ){
		l1.anxLista(i);
		l2.anxLista(i * h);
		m.anxLista( i + h);
	}
	printf("l1: ");
	l1.display();
	printf("l2: ");
	l2.display();

	concatenarListas(l1,l2);
	printf("\npostConcatenacion:\n");
	printf("l1: ");
	l1.display();
	printf("l2: ");
	l2.display();

	printf("\nm: ");
	m.display();

	Lista Vacia = Lista();

	concatenarListas(m,Vacia);
	printf("m y vacia: ");
	m.display();
	concatenarListas(Vacia,Vacia);
	printf("\nvacia y Vacia: ");
	Vacia.display();
	concatenarListas(Vacia,m);
	printf("\nvacia y m: ");
	Vacia.display();
	
	return 0;
}

/*
		Complejidad:
Se realiza un ciclo que itera 'n' veces donde 'n' es el tamaño de la lista 'l2'. Cada iteracion se hace la operacion
	'anxLista' en 'l1' y 'infoLista' en 'l2' en base a 'j'
Si tomamos 'k' como el tamaño inicial de la lista 'l1', se puede decir que en cualquier iteracion del ciclo for la 
	operacion 'anxLista' tiene complejidad 'k' + 'j' - 1.
La funcion 'infoLista' tiene complejidad 'j'- 1.
       n                     n                  n       n       n
T(n) = Σ ((k+j-1) + (j-1)) = Σ (k + 2j - 2) = k*Σ 1 + 2*Σ j - 2*Σ 1
      j=1                   j=1                j=1     j=1     j=1

T(n) = k*n + 2*((n^2 + n)/2) + 2*n
T(n) = k*n + n^2 + 3*n

si k > n, entonces k*n > n*n y T(n) = O(k*n) donde k es el tamaño inicial de l1 y n es el tamaño de l2.
si k <= n, entonces k*n <= n*n y T(n) = O(n^2) donde n es el tamaño de l2.
*/

/*
Nombre: concatenarListas
Entrada: una referencia a lista 'l1' y una lista 'l2'
Descripcion: le añade a 'l1' todos los elementos de 'l2'
*/
void concatenarListas(Lista& l1, Lista l2){
	int j, n = l2.longLista();
	for ( j = 1 ; j <= n ; ++j ){
		l1.anxLista( l2.infoLista( j ) );
	}
}