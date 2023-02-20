#include <stdio.h>

void leerImprimir();
int lockDegrees(int In, int x1, int x2, int x3);
int customDegConversor(int deg);
int aToB(int a, int b, int clockwise);

int main(){
	leerImprimir();
	return 0;
}

/*
Nombre: leerImprimir
Entrada: ninguna
Salida: no retorna nada.
Descripcion: Lee las entradas del standard input para despues invocar las funciones correspondientes a que
				hagan los calculos y luego imprime los resultados con el formato estipulado.
*/

void leerImprimir(){
	int In, x1, x2, x3, res;
	scanf("%d %d %d %d",&In,&x1,&x2,&x3);
	while (In != 0 || x1 != 0 || x2 != 0 || x3 != 0){
		res = lockDegrees(In, x1, x2, x3);
		printf("%d\n",res);
		scanf("%d %d %d %d",&In,&x1,&x2,&x3);
	}
}

/*
Nombre: lockDegrees
Entrada: 4 integers. El primero es la poscicion inicial(In), luego los demas son los numeros de la combinacion.
			Nota: estos lo pasan segun las 40 marcas de calibracion del 'lock'.
Salida: un integer que representa los grados que se roto el 'dial' para abrir el 'lock'
*/
int lockDegrees(int In, int x1, int x2, int x3){
	int ans = 1080;
	ans += aToB(In, x1, 0);
	ans += aToB(x1, x2, 1);
	ans += aToB(x2, x3, 0);
	return ans;
}

/*
Si va en sentido de las manecillas del reloj, el punto final siempre es mayor a no ser de que hayan pasado por 0.
Si va en sentido contrario a las manecillas del reloj, el punto final siempre es menor a no ser de que haya pasado	
	por 0.
*/
/*
Nombre: atoB
Entrada:  2 integers que representan la poscicion inicial y la final en el 'dial'. 1 booleano que indica si se
			esta moviendo con las manecillas del reloj o en contra.
Salida: 1 integer que es los grados girados del punto a al punto b.
*/
int aToB(int a, int b, int clockwise){
	int ans;
	if (clockwise){
		if (a > b){
			ans = b + (40-a); 
		} else{
			ans = b - a;
		}
	} else{
		if (a < b){
			ans = a + (40-b); 
		} else{
			ans = a - b;
		}
	}
	ans = customDegConversor(ans);
	return ans;
}
/*
40/x = 360/y
y * 40 = 360 * x
y = (360 * x)/40
y = 9 * x
f(x) = 9x

Conversion de 40 'calibration marks' a 360 grados
*/
/*
Nombre: customDegConversor
Entrada: un integer que representa ciertas 'calibration marks' giradas
Salida: un integer que representa los grados equivalentes a esas 'calibration marks'
*/
int customDegConversor(int deg){
	deg *= 9;
	return deg;
}
