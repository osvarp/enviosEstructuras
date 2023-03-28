/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
			Complejidad:


El proceso para dar con cada caracter esta dado por: 
			if (anteriorEspacio == 1){
				printf(" ");
				++anteriorEspacio;
			} else{
				if (flag2 == -1 || h == EOF){
					flag = 0;
				} else{
					++anteriorEspacio;
				}

				palActual[j] = '\0';

				j = 0;
				while(strcmp(palActual,llaves[j]) != 0){
					++j;
				}
				printf("%c",valores[j]);

A esta porcion del codigo se entra despues de haber leido hasta encontrar un espacio, EOF o salto de linea.
	Nota: la lectura, aunque muy parecida al scanf("%s"), opte por hacerla a mano para manejar mejor los casos
			en los que hay un doble espacio.

El caracter que debo imprimir esta guardado en palActual. El condicional que verifica si (anteriorEspacio == 1)
es para discernir si estamos ante un doble espacio, pues en este caso no se debera buscar un caracter que lo
decodifique. El condicional que verifica si (flag2 == -1 || h == EOF) esta para ver si ya se acabo este 'caso'.

El codigo que más influye en el tiempo de ejecución es entonces:
				j = 0;
				while(strcmp(palActual,llaves[j]) != 0){
					++j;
				}
				printf("%c",valores[j]);

Esta porción realizara una busqueda en el array de llaves hasta que encuentre una igual a la secuencia del input.
el while itera entonces 53 veces en el peor caso (strcmp(palActual,llaves[52]) == 0) y 1 vez en el mejor caso 
(strcmp(palActual,llaves[0]) == 0). Como estas 53 veces no dependen de la entrada, se podria decir que este 
while lo hace en tiempo constante. A su vez, strcmp() ha de iterar en los array de caracteres hasta que 
encuntre una diferencia entre ambos. strcmp() haria entonces entre 1 iteracion en el mejor caso
(si palActual[0] != llaves[i][0]) y n iteraciones (entendiendo a n como el tamaño de los arrays de caracteres) en
el peor caso (si ambos son iguales). A su vez, no llega a haber un codigo de más de 6 caracteres de largo. Por esto
Digo que la complejidad para traducir 1 caracter de su codigo morse es constante T(n) = O(1).





*/



#include <stdio.h>
#include <string.h>

#define CAP 7
#define TOTAL 53

void leerImprimir();


int main(){
	leerImprimir();
	return 0;
}


void leerImprimir(){
	char llaves[TOTAL][CAP] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", ".--.-."};
	char valores[TOTAL] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ',', '?', '\'','!', '/', '(', ')', '&', ':', ';', '=', '+', '-', '_', '"', '@'};
	char palActual[CAP];
	int i, n, j, flag, flag2, h, inicio;
	int anteriorEspacio = 0;
	scanf("%d",&n);
	scanf("%c",palActual);
	for (i = 1;i <= n;++i){
		printf("Message #%d\n",i);
		flag = 1;
		inicio = 0;
		while(flag == 1){

			j = 0;
			flag2 = 0;
			h = scanf("%c",palActual+j);
			while (flag2 == 0 && h != EOF){
				if (palActual[j] == ' '){
					flag2 = 1;
				} else if(palActual[j] == '\n'){
					flag2 = -1;
				}else{
					++j;
					h = scanf("%c",palActual+j);
					anteriorEspacio = 0;
				}
			}

			if (anteriorEspacio == 1 && inicio == 1){
				printf(" ");
				++anteriorEspacio;
			} else if (anteriorEspacio == 0){
				if (flag2 == -1 || h == EOF){
					flag = 0;
				} else{
					++anteriorEspacio;
				}

				palActual[j] = '\0';

				j = 0;
				while(strcmp(palActual,llaves[j]) != 0 && j < TOTAL){
					++j;
				}
				if (j != TOTAL){
					printf("%c",valores[j]);
					inicio = 1 ;
				}
			} else if (flag2 == -1 || h == EOF){
				flag = 0;
				++anteriorEspacio;
			}
		}
		printf("\n");
		if (i != n){
			printf("\n");
		}
	}

}