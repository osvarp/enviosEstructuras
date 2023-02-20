#include <stdio.h>
#include <stdlib.h>

void leerImprimir();
int solucion(int * estaciones, int n);


int main(){
	leerImprimir();
	return 0;
}

/*
Nombre: leerImprimir
Entrada: ninguna
Salida: ninguna
Descripcion: lee del standard input los datos del ejercicio, los guarda como se es requerido por 'solucion' y
				imprime la respuesta con el formato requerido.
*/
void leerImprimir(){
	int cases, cas, n, i, dato, res;
	int * list;
 	scanf("%d",&cases);
 	for (cas = 1;cas < cases+1;cas++){
 		scanf("%d",&n);
 		list = (int *) malloc(sizeof(int)*n);
 		for (i = 0;i < n;i++){
 			scanf("%d", list+i);
 		}
 		for (i = 0 ;i < n;i++){
 			scanf("%d", &dato);
 			list[i] = dato - list[i];
 		}

 		res = solucion(list, n);
 		free(list);
 		if (res == -1){
 			printf("Case %d: Not possible\n",cas);
 		} else{
 			printf("Case %d: Possible from station %d\n",cas,res);
 		}
 	}
}
/*
Nombre: solucion
Entrada: una lista que posee el combustible requerido para llegar a la proxima estacion restado por el combustible
			que puede recargar en la estacion. Esta lista es negativa, si el paso de esta estacion a la proxima le
			hace 'ganar' combustible, o positiva si requiere tener previo combustible para poder pasar por ahi. 
			Ademas, un integer que representa el tamaño de la lista.
Salida: Un integer que guarda la primera estacion por la que puede hacerse el recorrido. En caso de que no se
		pueda realizar el recorrido, retorna -1.
*/
int solucion(int * estaciones, int n){
	int i, estInicial = -1, gastAcum = 0, gastEst = 0, ans;
	for (i = 0;i < n;i++){
		if (estInicial == -1){
			if (estaciones[i] <= 0){
				estInicial = i;
				gastEst = estaciones[i];
			} else{
				gastAcum += estaciones[i];
			}
		} else{
			gastEst += estaciones[i];
			if (gastEst > 0){
				estInicial = -1;
				gastAcum += gastEst;
				gastEst = 0;
			}
		}
	}
	
	if (gastAcum + gastEst <= 0){
		ans = estInicial+1;
	} else{
		ans = -1;
	}
		
	return ans;
}
