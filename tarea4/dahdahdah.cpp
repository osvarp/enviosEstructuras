/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
Esta version en c++ utiliza 'find' de la libreria algorithm, vectores y strings.

			Complejidad:

La porcion que más influye en la complejidad por cada caso, es la invocacion a la operacion 'find' de la 
	libreria 'algorithm'. Esta funciona en tiempo lineal en 'llaves.size()', sin embargo, 
	'llaves.size()' == 'TOTAL', el cual es constante, por lo que, en 'leerImprimir', se estaria utilizando de
	manera constante la operacion 'find'. Por esto concluyo que la complejidad del programa que determina
	segun el codigo morse el caracter que representa, se realiza en tiempo constante. T(n) = O(1).

*/



#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>

#define TOTAL 53

using namespace std;

void leerImprimir();


int main(){
	leerImprimir();
	return 0;
}


void leerImprimir(){
	string llavesArr[TOTAL] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", ".--.-."};


	vector<string> llaves (llavesArr,llavesArr+TOTAL);

	char valores[TOTAL] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', ',', '?', '\'','!', '/', '(', ')', '&', ':', ';', '=', '+', '-', '_', '"', '@'};
	
	string palActual = "";
	
	int i, n, j, flag, flag2, h, inicio;
	int anteriorEspacio = 0;
	char temp;
	vector<string>::iterator res();
	scanf("%d",&n);
	scanf("%c",&temp);
	for (i = 1;i <= n;++i){
		printf("Message #%d\n",i);
		flag = 1;
		inicio = 0;
		while(flag == 1){

			j = 0;
			flag2 = 0;
			h = scanf("%c",&temp);
			while (flag2 == 0 && h != EOF){
				if (temp == ' '){
					flag2 = 1;
				} else if(temp == '\n'){
					flag2 = -1;
				}else{
					++j;
					palActual.push_back(temp);
					h = scanf("%c",&temp);
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

				vector<string>::iterator res = find(llaves.begin(),llaves.end(),palActual);

				/*cout << *res <<endl;*/
				j = res-(llaves.begin());
				palActual.clear();
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