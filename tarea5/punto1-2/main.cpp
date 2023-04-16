/*
Oscar Vargas Pabon
Puntos 1 y 2
*/


#include <stdio.h>
#include "lista.h"

int contarOcurrencias (Lista l, int v);
Lista obtenerMenores(Lista input, int v);

int main(){
	Lista l = Lista();
	l.anxLista(10);
	l.anxLista(12);
	l.anxLista(13);
	l.anxLista(34);
	l.anxLista(5);
	l.anxLista(67);
	l.display();
	int j = contarOcurrencias(l, 10);
	printf("Las ocurrencias del 10 han sido %d\n\n", j );
	l.anxLista(10);
	l.anxLista(10);
	l.display();
	j = contarOcurrencias(l, 10);
	printf("Las ocurrencias del 10 han sido %d\n\n", j );
	j = contarOcurrencias(l, 5);
	printf("Las ocurrencias del 5 han sido %d\n\n", j );
	j = contarOcurrencias(l, 67);
	printf("Las ocurrencias del 67 han sido %d\n", j );

	Lista menoresA11 = obtenerMenores(l, 11);
	printf("\n\nLos menores a 11:\n");
	menoresA11.display();
	Lista menoresA10 = obtenerMenores(l , 10);
	printf("\nLos menores a 10:\n");
	menoresA10.display();
	Lista menoresA100 = obtenerMenores(l , 100);
	printf("\nLos menores a 100:\n");
	menoresA100.display();
	return 0;
}

/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- Punto 1 _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/

/*
		Complejidad:
La funcion ejecuta un ciclo que itera 'n' veces donde 'n' es el tamaño de la lista. Cada iteracion, hace un 
	llamado a la funcion 'infoLista' con parametro 'i'. La funcion 'infoLista' funciona en tiempo lineal en 'i'.
Analisis a la linea 'if ( l.infoLista( i ) == v ){', que es la que tiene mayor complejidad.
       n          n      n
T(n) = Σ (i-1) =  Σ i  - Σ 1
      i=1        i=1    i=1
T(n) = (n^2 + n)/2 - n
T(n) = (n^2)/2 - n/2
T(n) = O(n^2)
Funciona en tiempo cuadratico.
*/

/*
Nombre: contarOcurrencias
Entrada: una lista l y un entero v
Salida: las veces que el entero v esta en la lista l
*/
int contarOcurrencias (Lista l, int v){
	int i, n = l.longLista(), res = 0;
	for ( i = 1 ; i <= n ; ++i ){
		if ( l.infoLista( i ) == v ){
			++res;
		}
	}
	return res;
}

/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_- Punto 2 _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/

/*
		Complejidad:
La funcion ejecuta un ciclo que itera 'n' veces donde 'n' es el tamaño de la lista. Cada iteracion, hace un 
	llamado a la funcion 'infoLista' con parametro 'i'. La funcion 'infoLista' funciona en tiempo lineal en 'i'.
Analisis a la linea 'h = input.infoLista( i );', pues todas las demás funcionan en tiempo constante o lineal.
       n          n      n
T(n) = Σ (i-1) =  Σ i  - Σ 1
      i=1        i=1    i=1
T(n) = (n^2 + n)/2 - n
T(n) = (n^2)/2 - n/2
T(n) = O(n^2)
Funciona en tiempo cuadratico.
*/

/*
Nombre: obtenerMenores
Entrada: una lista 'input' y un entero 'v'
Salida: una lista que contiene todos los elementos de 'input' que son estrictamente menores a 'v'
*/
Lista obtenerMenores(Lista input, int v){
	Lista output = Lista();
	int i, n = input.longLista(), h;
	for ( i = 1 ; i <= n ; ++i ){
		h = input.infoLista( i );
		if ( h < v ){
			output.anxLista( h );
		}
	}
	return output;
}