
/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
		Complejidad solucionar Problema:

En este hablare de la complejidad de la funcion modQuickSort. Aunque modQuickSort no retorna el resultado
	completamente, lo que se termina de hacer en printNFindMiddlePoint se hace a la par de la impresion.

Esta funcion esta dominada por un while, sin embargo, antes de entrar a este, tenemos una invocacion
	a la operacion 'startInOrder'. Esta operacion funciona en O(n), pues entra a su for n veces. Como
	el elemento que le pasamos como parametro n a la operacion 'startInOrder' es la variable 'n' que 
	representa la cantidad de palabras en 'names', se podria decir que la invocacion a 'startInOrder'
	se realiza en tiempo lineal en n.

Dentro del while tenemos una invocacion a la funcion 'sortInLists' y un condicional. Ninguno de los condicionales
	realiza operaciones o invocaciones que no sean constantes (son todos asignaciones), por lo que no añaden
	ningun elemento a considerar para la complejidad de la funcion 'modQuickSort'. Sin embargo, la funcion
	'sortInLists' si funciona en tiempo distinto a constante: es lineal sobre el valor que tenga 'lenLis'. Los 
	valores que obtenga 'lenLis' depende mucho de como este organizado 'names', sin embargo, en el mejor y peor
	caso adquiere valores predecibles.

		Mejor caso:
El mejor caso se da cuando los elementos que estarían en la mitad de 'names' si esta se ordenase, estan en el 
	indice 0 y 1 (independiente del orden en el que esten 'medioAlto' y 'medioBajo').
La primera vez que se entra al while, 'lenLis' es igual a 'n' (pues es con este valor con el que se inicializa),
	por lo que la invocacion a 'sortInLists' hace un multiplo a n pasos. 'lenIgual' se vuelve igual a 1, 
	'lenMayor' se vuelve n/2 o (n/2)-1 y 'lenMenor' se vuelve n/2 o (n/2)-1 (dependiendo del valor de 'lenMayor').
	En 'listaIgual[0]' esta 'medioAlto' o 'medioBajo'. Para la segunda vez que entra al while, 'lenLis' tiene n/2
	como valor, pues si  'lenMenor' == n/2, entonces 'else if (posAcum + lenMenor == posObj)' y si
	'lenMenor' == (n/2)-1, entonces 'lenMayor' == n/2 y 'else if (posAcum + lenMenor + lenIgual == posObj)'.
	La invocacion a 'sortInLists' haria un multiplo de n/2 pasos.

Ambas invocaciones a 'sortInLists' realizarian un multiplo de n y n/2, y la invocacion a 'startInOrder' hace
	otro multiplo a n de operaciones. Bajo este orden de ideas, en el mejor caso, la funcion 'modQuickSort' se
	realiza en tiempo O(n)

		Peor caso:
En el peor caso, las palabras en 'nombres' estan organizadas de mayor a menor hasta el indice que tomara
	'medioMenor' (primer caso) o estan organizadas de menor a mayor hasta el indice que tomara 'medioMayor' (segundo
	caso) . En el primer caso, dentro del while siempre se tomara el 'else', en el segundo, siempre se tomara el 
	'if (posAcum + lenMenor > posObj)'; esto con excepcion de las ultimas dos veces que entra al while, pues en
	estas ha de encontrar a 'medioMayor' y 'medioMenor'. En el primer caso, 'lenIgual' siempre es 1, 'lenMenor'
	siempre es 'lenLis'-1 y 'lenMayor' siempre es 0. En el segundo caso 'lenIgual' siempre es 1, 'lenMayor' siempre
	es 'lenLis'-1 y 'lenMenor' siempre es 0.
Por estos motivos, podemos plantear una sumatoria que va desde n/2 hasta n, pues estos son los valores que 
	va a tomar 'lenLis', variable de la que depende los pasos que realiza 'sorInLists'. 
Nota: voy a poner a la izquierda de 'Σ' el valor de i en el que inicia la sumatoria, a la derecha el valor en el que termina y
	en parentesis lo que suma la sumatoria.

n/2Σn(a*i) donde a representa los pasos que realiza 'sortInLists' en base a i 
a*(1Σn(i) - 1Σn/2(i))
a*(1/2*n**2 + 1/2*n - (1/8*n**2 + 1/4*n))
a*(3/8*n**2 + 1/4*n)
Este es el total de pasos que se realizan en la linea que invoca 'sortInLists'. Notese que tenemos un elemento
	que esta elevado al cuadrado, por lo que se puede decir que el peor caso se realiza en tiempo O(n**2).

       Mejor caso:   | peor caso:
T(n) =    O(n)          O(n**2)
              con n = 'n'


		Complejidad Impresion:

En esta parte hablare entonces de la complejidad de la operacion printNFindMiddlePoint.

Esta tiene 2 estructuras de control que no estan anidadas: 1 while y 1 condicional. El condicional solo elige
	entre imprimir 2 posibles cosas con la operacion printf, por lo que no afecta en mucho la complejidad de la
	funcion. El while si afecta la complejidad de la operacion. Este while itera mientra no se encuentre ninguna
	diferencia entre las dos cadenas guardadas en 'bajo' y 'alto', o 'bajo' no haya acabado (que encuentre el 
	caracter '\0'). Por este motivo, digo que en el mejor caso solo entra al while una vez (pues hay diferencia
	entre el primer caracter de 'bajo' y 'alto'), por lo que esta operacion sería O(1) en el mejor caso. En el 
	peor caso, el while entra hasta que 'bajo' acaba por lo que el while habría entrado tantas veces como el 
	tamaño de 'bajo'. Se podria decir que en el peor caso, esta operacion tendria complejidad O(len('bajo')) -
	para una funcion len() que retorna el tamaño del array-.

       Mejor caso:   |   Peor caso:
t(n) =     O(1)      |      O(n)
             con n = len('bajo')
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxLetters 32
#define MaxNames 1002

void leer();
void modQuickSort(int * medioBajo,int * medioAlto, char names[MaxNames][MaxLetters], int n, int * listaMenor, int * listaIgual, int * listaMayor, int * lis);

void sortInLists(char names[MaxNames][MaxLetters],int * lis, int n, int * listaMenor, int * lenMenor, int * listaIgual, int * lenIgual, int * listaMayor,int*lenMayor);
void solution(char names[MaxNames][MaxLetters], int n, int * listaMenor, int * listaIgual, int * listaMayor, int * lis);
void printNFindMiddlePoint(char * bajo, char * alto, int n);


void startInOrder(int * arr, int n);
void printList(char names[MaxNames][MaxLetters],int *arr,int n);


int main(){
	leer();
	return 0;
}
/*
Nombre: leer
Descripcion: realiza la lectura del stdin: organiza las palabras en la matriz de caracteres 'names', y la 
				cantidad de palabras del caso en el int 'n'. Ademas, se crean arrays de ints como 'listaMenor',
				'listaIgual' y demás para que no deban ser creados cada vez que se invocan en las funciones que
				lo necesitan. Despues de esto, invoca a 'solution', que gestiona la respuesta al caso.
*/
void leer(){
	char names[MaxNames][MaxLetters];
	int n,i;
	int listaMenor[MaxNames], listaIgual[MaxNames], listaMayor[MaxNames],lis[MaxNames];
	scanf("%d",&n);
	while (n != 0){
		for (i = 0;i < n;++i){
			scanf("%s",&names[i][0]);
		}
		
		solution(names, n, listaMenor,listaIgual,listaMayor,lis);
		
		scanf("%d",&n);
	}
}

/*
Nombre: solution
Entrada: la matriz de caracteres 'names', que contiene todas las palabras que tiene el caso. El int 'n' que
			representa la cantidad de palabras del caso. Arrays de ints como 'listaMenor', 'listaIgual' y demas
			que estan para ser pasados a 'modQuickSort' y que esta funcion no deba volverlos a crear cada que 
			sea invocada.
Descripcion: Crea las variables medioBajo y medioAlto, las que representan el indice en 'names' en el que esta la 
				secuencia de caracteres que hacen las dos palabras que se encuentran en la mitad (con la mitad
				me refiero a que si ordenasemos de menor a mayor todo 'names', estas dos estarian en el medio). 
				Invoca la funcion 'modQuickSort', para buscar estos indices y luego pasarle las palabras a la 
				funcion 'printNFindMiddlePoint' que terminara de calcular el resultado y lo imprime.
*/
void solution(char names[MaxNames][MaxLetters], int n, int * listaMenor, int * listaIgual, int * listaMayor, int * lis){
	int medioBajo,medioAlto;
	modQuickSort(&medioBajo, &medioAlto, names,n, listaMenor, listaIgual, listaMayor, lis);
	/*printf("%s - %s\n",names[medioBajo],names[medioAlto]);*/
	printNFindMiddlePoint(names[medioBajo],names[medioAlto], n);
}
/*
Nombre: printNFindMiddlePoint
Entrada: dos array de caracteres 'bajo' y 'alto' que representan las dos palabras que se encuentran
			en el medio (si ordenasemos 'names' de menor a mayor). un int 'n' que representa la 
			cantidad de palabras del caso.
Descripcion: encuentra e imprime la palabra que es inmediatamente mayor a 'bajo' pero menor a 'alto'.
*/
void printNFindMiddlePoint(char * bajo, char * alto, int n){
	/*printf("%s - %s\n",bajo,alto);*/
	int i = 0, flag = 0;
	while (flag == 0 && bajo[i] != '\0'){
		if (bajo[i] != alto[i] && (bajo[i]+1 != alto[i] || alto[i+1] != '\0') && bajo[i] != 'Z'){
			flag = 1;
		} else{
			printf("%c",bajo[i]);
			++i;
		}
	}
	if (bajo[i] == '\0'){
		printf("\n");
	} else if (bajo[i+1] == '\0'){
		printf("%c\n",bajo[i]);
	} else{
		printf("%c\n",bajo[i]+1);
	}
}
/*
Nombre: sortInLists
Entrada: una matriz de caracteres 'names'. Un array de int 'lis' que representa las palabras en 'names' con las
			que vamos a aplicar la operacion. Un int 'n' que representa el tamaño de 'lis'. Una serie de arrays
			de int 'listaMenor','listaMayor' y 'listaIgual' con int pasados como puntero 'lenMenor','lenMayor' y
			'lenIgual'. Los punteros representan los tamaños de su respectivo array. Son estos arrays de int y sus
			punteros lo que retornara esta funcion.
Salida: no hace un return, sin embargo pasa la informacion mediante 'listaMenor','listaMayor','listaIgual' y sus
			respectivos punteros. En 'listaMenor' pasa los indices de 'lis' que representan una palabra en 
			'names' menor a names[lis[0]], 'lenMenor' pasa el tamaño de 'listaMenor'. De manera analoga funciona
			'listaIgual' con 'lenIgual' y 'listaMayor' con 'lenMayor'. 
*/
void sortInLists(char names[MaxNames][MaxLetters], int * lis, int n, int * listaMenor, int * lenMenor, int * listaIgual, int * lenIgual, int * listaMayor,int*lenMayor){
	int i,h;
	listaIgual[0] = lis[0];
	*lenIgual = 1;
	*lenMenor = 0;
	*lenMayor = 0;
	for (i = 1; i < n; ++i){
		h = strcmp(names[listaIgual[0]],names[lis[i]]);
		if (h == 0){
			listaIgual[(*lenIgual)++] = lis[i];
		} else if(h > 0){
			listaMenor[(*lenMenor)++] = lis[i];
		} else {
			listaMayor[(*lenMayor)++] = lis[i];
		}
	}
	/*
	printf("menor |");
	printList(names,listaMenor,*lenMenor);
	printf("igual |");
	printList(names,listaIgual,*lenIgual);
	printf("mayor |");
	printList(names,listaMayor,*lenMayor);
	*/
}
/*
nombre: modQuickSort
entrada: una matriz de caracteres 'names' y un int 'n' que representa la cantidad de palabras que contiene 
			'names'. Los punteros 'medioBajo' y 'medioAlto' son para retornar la informacion. Los array
			'listaMenor', 'listaMayor', 'listaIgual' y 'lis' son pasados para que esta funcion no deba crearlos
			cada vez que sea invocada (en estos no viene ninguna informacion relevante).
salida: por medio de los punteros 'medioBajo' y 'medioAlto' salen los indices de 'names' de las palabras
	 		que estarian en la mitad si organizacemos de menor a mayor todas las palabras en 'names'. 
	 		names[*medioBajo] <= names[*medioAlto]. Cuando 'n' es par no hay un unico elemento en el centro, por
	 		lo que ambos 'medioBajo' y 'medioAlto' representan estos dos. Cuando 'n' es impar, 'medioBajo' seria
	 		el que se encuentra en el centro mientras que 'medioAlto' es el inmediatamente superior.
Descripcion: Lo que realiza esta funcion es parecido a lo que se realiza en un quickSort, con la diferencia de
				que no es necesario calcular toda la lista ordenada. Es por este motivo que se puede realizar
				con ciclos. Se usa la variable 'posAcum' y la cantidad de elementos en 'listaMenor' y 'listaIgual'
				para determinar si nos encontramos con el elemento que requerimos. 'posAcum' solo se modifica
				cuando el indice que buscamos se encuentra en la lista de los mayores a 'listaIgual[0]' porque
				si ordenasemos todo 'names' de menor a mayor, los indices que se encuentran en 'listaMayores'
				terminarian siempre hacia la derecha de los indices de 'listaMenores' y 'listaIgual'.
*/
void modQuickSort(int * medioBajo,int * medioAlto, char names[MaxNames][MaxLetters], int n, int * listaMenor, int * listaIgual, int * listaMayor, int * lis){
	int lenMenor = 0;
	int lenIgual = 0;
	int lenMayor = 0;
	int lenLis = n;
	int * t;
	startInOrder(lis,n);
	int posAcum = 0, posObj = (n/2);
	int bajoHecho = 0, altoHecho = 0;
	while(bajoHecho == 0 || altoHecho == 0){
		sortInLists(names, lis,lenLis,listaMenor, &lenMenor, listaIgual, &lenIgual, listaMayor, &lenMayor);	
		if (posAcum + lenMenor > posObj){
			t = listaMenor;
			listaMenor = lis;
			lis = t;
			lenLis = lenMenor;
		} else if (posAcum + lenMenor == posObj){
			*medioAlto = listaIgual[0];
			altoHecho = 1;
			t = listaMenor;
			listaMenor = lis;
			lis = t;
			lenLis = lenMenor;
		} else if (posAcum + lenMenor + lenIgual == posObj){
			*medioBajo = listaIgual[0];
			bajoHecho = 1;
			posAcum += lenMenor + lenIgual;
			t = listaMayor;
			listaMayor = lis;
			lis = t;
			lenLis = lenMayor;
		}else if (posAcum + lenMenor + lenIgual > posObj){
			if (bajoHecho == 0){
				*medioBajo = listaIgual[0];
				bajoHecho = 1;
			}
			if (altoHecho == 0){
				*medioAlto = listaIgual[0];
				altoHecho = 1;
			}
		} else{
			posAcum += lenMenor + lenIgual;
			t = listaMayor;
			listaMayor = lis;
			lis = t;
			lenLis = lenMayor;
		}
	}
}
/*
Nombre: startInOrder
Entrada: un array de int 'arr' y un int 'n' que representa el tamaño del array.
Descripcion: inicia todos los espacios en array con el mismo numero que su indice.
*/
void startInOrder(int * arr, int n){
	int i;
	for (i = 0;i < n;++i){
		arr[i]=i;
	}
}
/*
Nombre: printList
Entrada: una matriz de caracteres 'names', un array de ints 'arr' y un int 'n' que representa
			el tamaño del array 'arr'. El array 'arr' contiene las palabras a imprimir de la matriz 'names'
Descripcion: imprime todas las palabras de 'names' indicadas por los valores en 'arr'. Esta funcion
				fue realizada para poder visualizar los elementos en 'names' que representan los arrays
				'listaMenor', 'listaMayor' y 'listaIgual'. 
*/
void printList(char names[MaxNames][MaxLetters],int *arr,int n){
	int i;
	for (i=0;i<n;++i){
		printf("%s | ",names[arr[i]]);
	}
	printf("len = %d\n",n);
}