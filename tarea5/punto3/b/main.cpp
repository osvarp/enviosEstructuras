/*
Oscar Vargas Pabon
Punto 3-b
*/

#include <stdio.h>

#include "lista.h"

int main(){
	Lista l = Lista();

	l.display();
	l.insListaOrdenada(2);
	l.insListaOrdenada(20);
	l.insListaOrdenada(10);
	l.display();

	int a;
	printf("Escribir -0- para salir:\n");
	scanf("%d",&a);
	while ( a != 0 ){
		l.insListaOrdenada(a);
		l.display();
		scanf("%d",&a);
	}

	return 0;
}


/*
La operacion 'insListaOrdenada':
Funciona en el mejor caso en tiempo constante. Este se da cuando act == NULL o act->dato >= elem. En ambos de estos
	casos, solo basta con 2 lineas que determinan el 'sig' del nuevo nodo y que cambian el 'act' de la lista.
T(n) = O(1)

En el peor caso funciona en tiempo lineal. Este caso se da cuando 'elem' es mayor a todos los datos almacenados en la lista.
	Cuando esto ocurre, se toma el else. Aqui el while va a recorrer todos los nodos de la lista, hasta que el siguiente
	sea NULL. Ejecuta el while n-1 veces, por lo que se realiza en tiempo lineal.
T(n) = O(n)

void Lista::insListaOrdenada(Elemento elem){
  Nodo *nuevo;
  nuevo = new Nodo;
  nuevo->dato = elem;
  if (act == NULL){
    nuevo->sig = NULL;
    act = nuevo;
  } else if ( act->dato >= elem ){
    nuevo->sig = act;
    act = nuevo;
  } else {
    Nodo  *tmp;
    tmp = act;
    while ( tmp->sig != NULL && (tmp->sig)->dato <= elem ){
      tmp = tmp->sig;
    }
    nuevo->sig = tmp->sig;
    tmp->sig = nuevo;
  }
}
*/
