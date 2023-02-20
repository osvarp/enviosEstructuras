#include <stdio.h>

void leerImprimir();

int main(){
	leerImprimir();
	return 0;
}

/*
El sitio de parqueo optimo es en cualquier sitio entre la tienda con mayor xi y la tienda con menor xi.
Si xj es la tienda con mayor valor xi y xm es la tienda con menor valor xm, entonces xj - xm es la distancia 
desde xj a xm (o viceversa). Si Michael se parquease en alguna tienda xr en el medio, tendria que ir hasta xj 
y devolverse ((xj-xr)*2), y luego ir hasta xm y devolverse ((xr-xm)*2) y el valor de esto sumado seria 
((xj-xr)*2) + ((xr-xm)*2)
2xj-2xr + 2xr-2xm
2xj-2xm
2*(xj-xm)

(mayor-menor)*2
*/

/*
nombre: leerImprimir
entrada: nada
salida: nada
descripcion: toma del standard input la informacion referente al problema, computa el calculo (pues es muy 
				sencillo si se selecciona bien la informacion), e imprime con el formato estipulado.
*/
void leerImprimir(){
	int cases, cas, i, n, mayor, menor, actual;
	scanf("%d",&cases);
	for (cas = 0;cas < cases;cas++){
		scanf("%d",&n);
		scanf("%d",&mayor);
		menor = mayor;
		for (i = 1;i < n;i++){
			scanf("%d",&actual);
			if (actual > mayor){
				mayor = actual;
			} else if (actual < menor){
				menor = actual;
			}
		}
		printf("%d\n",((mayor-menor)*2));
	}
}