#include <stdio.h>
#include <stdlib.h>

void leerImprimir();
int abs(int a);
void cuadrarInicial(int * lista, int n);
int enRango(int * logrados, int n, int val);

#define predetList 0;


/*
Esta version, a diferencia de la anterior, no debe buscar si 'val' ya ha sido guardado en algun punto previo
cualquiera del array, sino que utiliza los indices del mismo para guardar esta información. Esto le permite
verificar si el valor es o no repetido en tiempo constante. 
Lo referido a un valor absoluto 'val' se guarda en: array[val-1], pues val va desde 1 hasta n-1, mientras que 
el array que posee n-1 elementos va desde 0 hasta n-2.

Para hacer esto posible, me aseguro mediante la operacion 'cuadrarInicial' de que no va a haber ningun 
'valor basura' guardado en algun lugar del array que pueda interferir con el programa.
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
		cuadrarInicial(logrados, n-1);
		scanf("%d",&anterior);
		flag = 1;
		for (i = 1;i < n;i++){
			scanf("%d",&actual);
			if (flag == 1){
				flag = enRango(logrados, n, abs(actual-anterior));
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
		  Un int 'val' que es el valor absoluto de dos numeros seguidos del input.El valor n, para ver si 'val'
		  se ha pasado irremediablemente del rango.
Salida: Un valor booleano que indica si el nuevo 'val' permite a la secuencia ser 'Jolly' o no.
*/
int enRango(int * logrados, int n, int val){
	int ans;
	if (val >= n){
		ans = 0;
	} else{
		if (logrados[val-1] == predetList){
			logrados[val-1] = 1;
			ans = 1;
		} else{
			ans = 0;
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
Nombre: cuadrarInicial
Entrada: un array de int. Un valor n que representa el len del array.
Salida: Nada.
Descripcion: Entra a todos los espacios del array, poniendo en estos el valor predeterminado en la constante
				predetList.
*/
void cuadrarInicial(int * array, int n){
	int i;
	for (i = 0;i < n; i++){
		array[i] = predetList;
	}
}
