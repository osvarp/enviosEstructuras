#include <stdio.h>

void leerImprimir();
int nlogonia(int n, int m, int x, int y);

int main(){
	leerImprimir();
	return 0;
}

/*
0 es 'divisa'
1 es 'NE'
2 es 'NO'
3 es 'SO'
4 es 'SE'
*/
/*
Nombre: leerImprimir
Entrada: nada
Salida: nada
descripcion: recibe los datos del standard input, llama la funcion 'nlogonia' que determina la respuesta y luego
				imprime la respuesta con el formato estipulado.
*/
void leerImprimir(){
	int cases,i, n, m, x, y, res;
	scanf("%d",&cases);
	while (cases != 0){
		scanf("%d %d",&n, &m);
		for (i = 0;i < cases;i++){
			scanf("%d %d",&x, &y);
			res = nlogonia(n, m, x, y);
			switch (res){
			case 0:
				printf("divisa\n");
				break;
			case 1:
				printf("NE\n");
				break;
			case 2:
				printf("NO\n");
				break;
			case 3:
				printf("SO\n");
				break;
			case 4:
				printf("SE\n");
				break;
			}
		}
		scanf("%d",&cases);
	}
}
/*
Nombre: nlogonia
Entrada: dos integers (n,m) que representan la poscicion del punto de division. dos integers (x,y) que representan
			la poscicion de una residencia.
Salida: un int de 0 a 1 que representa el estado al que la residencia pertenece. Se usa la siguiente tabla de 
			convenciones.
| 0 |es| 'divisa' |
| 1 |es|   'NE'   |
| 2 |es|   'NO'   |
| 3 |es|   'SO'   |
| 4 |es|   'SE'   |
*/
int nlogonia(int n, int m, int x, int y){
	int ans;
	if (x==n || y == m){
		ans = 0;
	} else if (x > n){
		if (y > m){
			ans = 1;
		} else{
			ans = 4;
		}
	} else{
		if (y > m){
			ans = 2;
		} else {
			ans = 3;
		}
	}
	return ans;
}