/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
		Complejidad solucionar problema:

La solucion de este problema se realiza en la operacion 'solve'. Esta tiene una invocacion a la 
	operacion 'sartCadIn' que funciona en tiempo T(n) = O(n) con n = 'len', sin embargo, siempre
	se invoca con 'len' = 'lenGuess-1', por lo que en la operacion 'solve' no afecta mucho la
	complejidad.
Esta operación tiene: (1)'while (right <= 1 && i < 10000)'. Este itera 10000 veces en el peor caso y 
	2 veces en el mejor caso (cuando '0000' y '0001' son posibles); sin embargo, como en el peor caso
	siempre iterara 10000 veces sin importar la entrada, se puede decir que trabaja en tiempo constante.
	Dentro de este ciclo hay otro while: (2)'while (flag == 0 && j < g)' que itera 'g' veces o hasta 
	que 'verCumplimiento' retorne 0. 'verCumplimiento' a su vez, se puede decir que tambien funciona
	en tiempo constante, pues aunque tiene 2 for: el primero siempre itera 'lenGuess-1' veces y el
	segundo siempre itera 'Dig' veces. El while (2) es el unico que puede manejar cierta variabilidad,
	pues en el mejor de los casos solo itera 1 vez, mientras que en el peor de los casos itera 'g' veces.
	Como el while (2) itera entre 1 y 'g', dire que funciona en tiempo lineal en 'g', por lo que 
	la operacion 'solve' funciona en tiempo T(n) = O(n) con n = 'g'.

		Complejidad impresion:

Este problema no tiene mayores requerimientos de formato, por lo que la parte de la impresion se 
	resume en:
	if (right == 0){
		printf("impossible\n");
	} else if (right >= 2){
		printf("indeterminate\n");
	} else {
		guess[lenGuess-1] = '\0';
		printf("%s\n", guess);
	}
Esto funciona en T(n) = O(1)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxGuesses 10
#define lenGuess 5
#define Dig 10



typedef struct Guess Guess;

void leer();
int verCumplimiento(char * opcion, Guess* g);
void startCadIn(char * cad, int len, char v);
void modBy1(char * pos, int n);
void solve(Guess * guesses, int g);

int cantCond[Dig][2];
int cantOpcion[Dig][2];
int cas;

struct Guess{
	char cad[lenGuess];
	int inPlace;
	int inGuess;
};

int main(){
	leer();
	return 0;
}

/*
Nombre: leer
Descripcion: realiza la lectura del stdin, guarda la informacion e invoca a la operacion 'solve' que 
				soluciona el problema.
*/
void leer(){
	int n,i, j;
	scanf("%d",&n);
	Guess guesses[MaxGuesses];
	for ( i = 0 ; i < Dig ; ++i ){
		cantCond[i][1] = -1;
		cantOpcion[i][1] = -1;
	}
	cas = 0;
	int g;
	for (i = 0 ; i < n ; ++i){
		scanf("%d",&g);
		for (j = 0 ; j < g ; ++j){
			scanf("%s",guesses[j].cad);
			scanf("%d/%d",&guesses[j].inPlace,&guesses[j].inGuess);
		}
		solve(guesses, g);
	}
}

/*
Nombre: solve
Entrada: un arreglo tipo Guess que contiene la informacion de cada pista que fue dada en el caso.
			Un entero 'g' que representa la cantidad de pistas que nos dieron en el caso.
Descripcion: Prueba por fuerza bruta todas las posibles combinaciones hasta que las probamos todas, o
				nos damos cuenta de que puede haber más de una respuesta ('indeterminate'). Despues 
				imprime la respuesta, o 'impossible' si no hay ninguna posibilidad.
*/
void solve(Guess * guesses, int g){
	int right = 0;
	char pos[lenGuess];
	startCadIn(pos,lenGuess-1,'0');
	pos[lenGuess-1] = '\0';
	char guess[lenGuess];
	int flag, j, i = 0;
	while (right <= 1 && i < 10000){
		flag = 0;
		j = 0;
		while (flag == 0 && j < g){
			if( ! verCumplimiento(pos,&guesses[j]) ){
				flag = 1;
			}
			++j;
		}
		if (flag == 0){
			++right;
			strcpy(guess,pos);

		}
		modBy1(pos,lenGuess-1);
		++i;
	}
	if (right == 0){
		printf("impossible\n");
	} else if (right >= 2){
		printf("indeterminate\n");
	} else {
		guess[lenGuess-1] = '\0';
		printf("%s\n", guess);
	}
}

/*
Nombre: modBy1
Entrada: un arreglo tipo char que contiene unicamente digitos
			 y un entero n que representa el tamaño del arreglo.
Descripcion: El arreglo representa un numero, pues este esta compuesto de solo digitos. Lo que hace
				esta operacion, es modificar el arreglo de tal manera que si N es el numero que 
				representa antes de 'modBy1', N+1 es el numero que representa de manera posterior.
Nota: la operacion no maneja el caso cuando pos[i] = '9' para i = 0,1,...,n-1.
*/
void modBy1(char * pos, int n){
	--n;
	int change = 1;
	while (change == 1){
		++pos[n];
		if (pos[n] > '9'){
			pos[n] = '0';
			change = 1;
			--n;
		} else{
			change = 0;
		}
	}
}

/*
Nombre: startCadIn
Entrada: un arreglo de caracteres 'cad', un entero 'len' que representa el tamaño de 'cad',  y 
			un caracter 'v'.
Descripcion: modifica todas las posciciones en 'cad' de tal modo que ahora contengan el valor 'v'.
*/
void startCadIn(char * cad, int len, char v){
	int i;
	for (i = 0 ; i < len ; ++i){
		cad[i] = v;
	}
}

/*
Nombre: verCumplimiento
Entrada: un arreglo de caracteres 'opcion' y un puntero a un elemento de la estructura Guess 'g'.
Salida: retorna 1 si 'opcion' cumple con la condicion propuesta por 'g',0 de lo contrario. Que cumpla
			con la condicion propuesta por 'g' significa que 'opcion' comparte con 'g->cad' en la 
			misma poscicion exactamente la misma cantidad de caracteres que los que diga 'g->inPlace',
			y que comparten en posciciones estrictamente distintas la misma cantidad de caracteres
			que los que dice 'g->inGuess'.
*/
int verCumplimiento(char * opcion, Guess* g){
	int inPlaceVer = 0;
	int inGuessVer = 0;
	int ans;
	int i = 0, j;
	for (i = 0 ; i < lenGuess-1 ; ++i){
		if (opcion[i] == g->cad[i]){
			++inPlaceVer;
		} else{
			if (cantOpcion[opcion[i]-'0'][1] == cas){
				cantOpcion[opcion[i]-'0'][0]++;
			} else {
				cantOpcion[opcion[i]-'0'][1] = cas;
				cantOpcion[opcion[i]-'0'][0] = 1;
			}
			if (cantCond[g->cad[i]-'0'][1] == cas){
				cantCond[g->cad[i]-'0'][0]++;
			} else {
				cantCond[g->cad[i]-'0'][1] = cas;
				cantCond[g->cad[i]-'0'][0] = 1;
			}
		}
	}
	ans = inPlaceVer == g->inPlace;
	if (ans){
		for (i = 0 ; i < 10 ; ++i){
			if (cantCond[i][1] == cas && cantOpcion[i][1] == cas){
				while (cantCond[i][0] != 0 && cantOpcion[i][0] != 0){
					++inGuessVer;
					--cantCond[i][0];
					--cantOpcion[i][0];
				}
			}
		}
	}
	++cas;
	ans = inGuessVer == g->inGuess && ans;
	/*if (strcmp(opcion,"3411") == 0){
		printf("inPlaceVer = %d - inGuessVer = %d\n",inPlaceVer,inGuessVer);
		printf("%s |%d||%d|||\n",g->cad,g->inPlace,g->inGuess);
	}*/
	return ans;
}