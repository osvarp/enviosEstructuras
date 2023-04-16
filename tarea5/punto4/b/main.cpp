/*
Oscar Vargas Pabon
Punto 4-b
*/

#include <stdio.h>
#include "lista.h"

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

	Lista l3 = l1 + l2;

	printf("\nl3: ");
	l3.display();

	printf("\nm: ");
	m.display();

	printf("\nl3 + m: ");
	Lista otraL = l3 + m;
	otraL.display();

	Lista Vacia = Lista();

	Lista g = Vacia + m;
	printf("\nvacia + m: ");
	g.display();
	Lista y = m + Vacia;
	printf("\nm + vacia: ");
	y.display();
	Lista w = Vacia + Vacia;
	printf("\nVacia + vacia: ");
	w.display();

	return 0;
}


/*
		Complejidad:
la funcion esta dominada por un while que itera mientras j <= 1. 'j' lo que simboliza es la lista que estamos 
	recorriendo. j = 0 representa la que se encuentra a la izquierda del '+' mientras que j = 1 es la que se encuentra
	a la derecha del '+'. 'j' solo aumenta en valor cuando it == NULL, en otras palabras, cuando la lista que estabamos
	recorriendo ha llegado a su final.
En cada iteracion del while se realizan acciones que funcionan en tiempo constantes: se crea dinamicamente un nodo, se 
	le asignan sus datos segun 'it' y se inserta al final de la lista (este append funciona en tiempo constante porque
	 siempre guardamos un apuntador a la cola). Es por esto que la complejidad de la funcion depende de la cantidad de 
	 iteraciones del while.
Como el while itera tantas veces como el largo de ambas listas a concatenar, entonces:
	 T(n) = O(n) donde n = 'longLista()' + 'l.longLista()'

Lista Lista::operator + (Lista l){
  Lista res = Lista();
  if (act != NULL || l.act != NULL){
    Nodo *it = act, *last = NULL, *tmp;
    int j = 0;
    while( j <= 1 ){
      if ( it == NULL ){
        ++j;
        it = l.act;
      } else {
        tmp = new Nodo;
        tmp->dato = it->dato;
        tmp->sig = NULL;
        if ( last == NULL ){
          res.act = tmp;
          last = tmp;
          it = it->sig;
        } else {
          last->sig = tmp;
          last = tmp;
          it = it->sig;
        }
      }
    }
  }
  return res;
}  
*/