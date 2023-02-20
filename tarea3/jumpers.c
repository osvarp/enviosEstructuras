#include <stdio.h>
#include <stdlib.h>

void leerImprimir();
int abs(int a);
int enRango(int * logrados, int n, int iter, int val);
int enArray(int * array, int n, int val);

/*
Si algun valor 'val' (representa el valor absoluto de la resta de dos elementos consecutivos del input).
es superior a n-1, sabemos que esta secuencia ya no es 'Jolly', pues solo hay n-1 valores 'val'. De la 
misma manera, si dos valores 'val' se repiten, ya no podra ser 'Jolly'.
*/

int main(){
	leerImprimir();
	return 0;
}

/*
Nombre: leerImprimir.
Entrada: nada
Salida: nada
Descripcion: Recibe del standard input la informacion del ejercicio, invoca a las funciones auxiliares que 
				resuelven el problema y imprime los resultados con el formato estipulado.
*/

void leerImprimir(){
	int n, i, anterior, actual, flag;
	int * logrados;
	while (scanf("%d",&n) != EOF){
		logrados = (int *) malloc(sizeof(int)*(n-1));
		scanf("%d",&anterior);
		flag = 1;
		for (i = 1;i < n;i++){
			scanf("%d",&actual);
			if (flag == 1){
				flag = enRango(logrados, n, (i-1), abs(actual-anterior));
				anterior = actual;
			}
		}
		if (flag == 1){
			printf("Jolly\n");
		} else{
			printf("Not jolly\n");
		}
		free(logrados);
	}
}
/*
Nombre: enRango
Entrada: El array de int 'logrados' que contiene los valores absolutos de las restas de los numeros del input.
			el valor n. El int 'iter' vendria siendo la cantidad de espacios que se le han añadido a 'logrados'.
			un int 'val' que es el valor absoluto de dos numeros seguidos del input.
Salida: Un valor booleano que indica si el nuevo 'val' permite a la secuencia ser 'Jolly' o no.
*/
int enRango(int * logrados, int n, int iter, int val){
	int ans;
	if (val >= n){
		ans = 0;
	} else{
		if (enArray(logrados, iter, val)){
			ans = 0;
		} else{
			logrados[iter] = val;
			ans = 1;
		}
	}
	return ans;
}
/*
Nombre: abs (absoluto)
Entrada: un integer
Salida: el valor absoluto del integer
*/
int abs(int a){
	if (a < 0){
		a = -a;
	}
	return a;
}
/*
Nombre: enArray
Entrada: un array de ints, la cantidad de datos del array (n), y un valor a buscar en el array(val).
Salida: un booleano que indica si val esta en el array. (1 si si esta, 0 si no).
*/
int enArray(int * array, int n, int val){
	int ans = 0, i = 0;
	while (i < n && ans == 0){
		if (array[i] == val){
			ans = 1;
		}
		i++;
	}
	return ans;
}