/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
		Complejidad solucionar Problema:

Aqui hablare de la complejidad de la operacion 'actualizarPuntaje', que se realiza 1 vez por cada puesto
	que recibe puntaje en el caso.

La complejidad de la funcion 'actualizarPuntaje' depende del valor que tome 'lenPuestos', que no es otra que
	la variable 'G' de la operacion 'leer', que realmente representa la cantidad de carreras que tuvo la copa.
	Esto porque esta operacion lo que hace es recorrer mediante un for todos los elementos del arreglo 'puestos', 
	los cuales son tantos como 'lenPuestos'. A excepcion de un condicional dentro del for y algunas asignaciones,
	esta funcion no realiza nada más complejo que el recorrido al arreglo. Por esto digo que esta funcion 
	funciona en tiempo O('lenPuestos') = O('G') (pues 'G' es lo que le pasamos a la funcion como 'lenPuestos').

No olvidemos que esta operacion lineal en 'G' itera tantas veces como puestos que tengan puntaje, los cuales estan
	dados por la variable 'K' en la operacion 'leer'.

T(n) = O(n)  con n = 'G'  -   'actualizarPuntaje'


		Complejidad Impresion:

En la impresion hablare de la complejidad de la operacion 'printMejores', que es la encargada de ver los pilotos
	que debe imprimir e imprimirlos con el formato indicado.

Esta operacion tiene dos estructuras de control que pueden afectar la complejidad: dos for. El primero itera 
	en la variable 'P' que representa la cantidad de pilotos, para asi acceder a todos los elementos del arreglo
	'puntaje'. El segundo itera sobre la variable 'topMejor' que representa el tamaño del arreglo 'indiceMejor'
	que guarda los indices que representan a los corredores con mejor puntaje. En el peor caso, topMejor = P
	porque todos los corredores estan empatados como los mejores; el segundo for iteraria tambien 'P' veces. En
	el mejor caso, topMejor = 1 porque solo hay un mejor corredor. Notese que en ambos casos, la operacion 
	manejaria complejidad lineal en la variable 'P', por lo que digo que la operacion es O('P').


T(n) = O(n) con n = 'P'
*/

#define MaxPilots 500
#define MaxPrix 500

#include <stdio.h>
#include <stdlib.h>

void leer();
void printMejores(int puntos[MaxPilots][2], int P, int caso, int * indiceMejor);
void actualizarPuntaje(int aumento, int * puestos, int puntos[MaxPilots][2], int lenPuestos, int caso);
void iniciarEn(int arr[MaxPilots][2]);

int main(){
	leer();
	return 0;
}

/*

----------------- puestos --------------------------

puestos tiene en una poscicion i
puestos[i] la lista de los pilotos
que llegaron en esa poscicion en cada
carrera.

-------------------- puntos -------------------------

puntos tiene en la poscicion i
puntos[i][0] los puntos del piloto i
puntos[i][1] el caso en el que fue actualizada la casilla la ultima vez (para saber si hace falta reinicializar la info)
*/
/*
Nombre: leer
Descripcion: realiza la lectura de los datos como lo especifica el caso y los guarda en el array de puestos.
				Invoca a la funcion actualizarPuntaje, que actualiza la informacion requerida para cada caso
				de prueba. Invoca la operacion printMejores que realiza la impresion con el formato requerido.
*/
void leer(){
	int G, P, scoringSyst, K;
	int puestos[MaxPilots][MaxPrix];
	int puntos[MaxPilots][2];
	iniciarEn(puntos);
	int caso = 0, i, j;
	int competidor;
	int indiceMejor[MaxPilots];
	scanf("%d %d",&G,&P);
	while (G != 0){

		for (i = 0;i < G;++i){
			for (j = 0;j < P;++j){
				scanf("%d",&competidor);
				puestos[competidor-1][i] = j;
			}
		}

		scanf("%d",&scoringSyst);

		for (i = 0;i < scoringSyst;++i){
			scanf("%d",&K);
			for (j = 0;j < K;++j){
				scanf("%d",&competidor);
				actualizarPuntaje(competidor, puestos[j], puntos, G, caso);
			}
			printMejores(puntos,P,caso, indiceMejor);
			++caso;
		}

		scanf("%d %d",&G,&P);
	}
}

/*
Nombre: printMejores
Entrada: una matriz 'puntos' que tiene los puntos totales de cada piloto. Un entero 'P' que guarda la cantidad
			de pilotos. un entero 'caso' que se usa para discernir si este piloto gano algun punto en este torneo.
			Ademas un arreglo 'indiceMejor', para no tener que reservar un espacio cada vez que se invoca la funcion.
Descripcion: Recorre por completo la matriz de 'puntos' para obtener los mejores corredores. Luego los imprime.
*/
void printMejores(int puntos[MaxPilots][2], int P, int caso, int * indiceMejor){
	int mejor = -1;
	int topMejor = -1;
	int i;
	for (i = 0;i < P;++i){
		if(puntos[i][1] != caso){
			puntos[i][0] = 0;
		}

		/*printf("puntos[i][0] = %d\n",puntos[i][0]);*/
		if (puntos[i][0] == mejor){
			++topMejor;
			indiceMejor[topMejor] = i+1;
		} else if (puntos[i][0] > mejor){
			mejor = puntos[i][0];
			indiceMejor[0] = i +1;
			topMejor = 0;
		}
	}
	for (i = 0;i < topMejor;++i){
		printf("%d ",indiceMejor[i] );
	}
	printf("%d\n",indiceMejor[topMejor]);
}

/*
Nombre: actualizarPuntaje
Entrada: un entero 'aumento' que contiene los puntos que ganan los que llegaron en cierto puesto. un arreglo
			'puestos' que contiene la lista de pilotos que llegaron en este puesto que estamos actualizando.
			Una matriz 'puntos' que guarda la informacion de los puntos que vamos a actualizar. Un entero
			'lenPuestos' que indica cuantos pilotos estan almacenados en 'puestos'. Un entero 'caso' que 
			nos ayuda a discernir si es la primera vez que nos topamos con cierto piloto en este caso.
*/
void actualizarPuntaje(int aumento, int * puestos, int puntos[MaxPilots][2], int lenPuestos, int caso){
	/*printf("aumento = %d, caso = %d\n",aumento,caso);*/
	int i;
	for (i = 0;i < lenPuestos;++i){
		/*printf("puestos[i] = %d\n",puestos[i]);*/
		if (puntos[puestos[i]][1] != caso){
			puntos[puestos[i]][1] = caso;
			puntos[puestos[i]][0] = aumento;
		} else{
			puntos[puestos[i]][0] += aumento;
		}
	}
}
/*
Nombre: iniciarEn
Entrada: una matriz 'arr'
Descripcion: esta hecho para inicializar todos los valores i de puntos[i][1] en un valor que no conflictue
				con los valores que va a tomar 'caso'.
*/
void iniciarEn(int arr[MaxPilots][2]){
	int i;
	for (i = 0;i < MaxPilots;++i){
		arr[i][1] = -1;
	}
}