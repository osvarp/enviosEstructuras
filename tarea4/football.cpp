/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*

		complejidad solucion:

en esta parte me referire a la complejidad del proceso de actualizar los datos para cada partido en el torneo.
	Esta parte es realizada por el segundo for anidado en 'leer' : 'for (i = 0;i < G;++i)'. Aqui hay tres 
	invocaciones importantes: 2 a la operacion 'myFind' y una a la operacion 'actualizarInformacion'. La funcion
	'myFind' funciona en tiempo T(n) = O(n) con n siendo el tamaño del arreglo (variable 'T'), pues en el peor de 
	los casos, debe recorrer por completo el arreglo 'equipos'. La operacion 'actualizarInformacion' funciona en 
	tiempo T(n) = O(1), pues solo modifica los valores en algunos elementos del arreglo 'equipos'. 

Es por esto que la complejidad de la solucion es en T(n) = O(n) con n = 'T'

		complejidad impresion:

En esta parte me referire a la operacion 'printInfo', pues es la encargada de hacer toda la impresion. Esta 
	operacion tiene invocaciones a: 'sort', 'fullEqualityCmp' y 'printSpacesString'. La funcion 'sort' maneja
	tiempo T(n) = O(n*logn) con n = 'T', segun visto en clase. La funcion 'fullEqualityCmp' maneja tiempo 
	T(n) = O(1), pues solo accede a algunos elementos en las estructuras tipo Team y los compara. La operacion
	'printSpacesString' funciona en tiempo T(n) = O(n), sin embargo, como su n = 15 en todas sus invocaciones, 
	se podria decir que es constante en 'printInfo'.
Despues de las invocaciones, solo hay una estructura de control que pueda afectar la complejidad: el for. Este
	itera sobre el arreglo, por lo que se podria decir que funciona en tiempo lineal en 'T'.

Como la mayor complejidad la tiene 'sort' con T(n) = O(n*logn) y n = 'T', la operacion 'printInfo' funciona
	con tiempo T(n) = O(n) con n = 'T'

*/


#include <algorithm>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;
/*
int nonCapitalCmp(string a, string b);
void startTeam(Team A&, string name);
int calcDiferenciaGoles(struct Team A);
bool operator <(Team A, Team B);
bool operator == (Team A, Team B)

void leer();
void actualizarInformacion(Team a&, int golA, Team b&, int golB)
void printInfo(Team * equipos, int T);
void printSpacesString(string pal, int num);
bool fullEqualityCmp(Team A, Team B);
*/

#define MaxTeams 100

/* 
La estructura que representa 1 equipo durante el torneo
*/
typedef struct Team{
	string name;
	int puntos;
	int partidosJugados;
	int golesAnotados;
	int golesRecibidos;
} Team;

/*
Nombre: startTeam
Entrada: una estructura Team 'A' y un string 'name'.
Descripcion: 'A' es pasado por referencia, por lo que lo que se le modifica a 'A', es en cierta manera
				la salida. Inicia el nombre de 'A' con el string 'name'. Inicia todos los demas 
				valores de 'A' en 0.
*/ 
void startTeam(struct Team& A, string name){
	A.name = name;
	A.puntos = 0;
	A.partidosJugados = 0;
	A.golesAnotados = 0;
	A.golesRecibidos = 0;
}

/*
Nombre: calcDiferenciaGoles
Entrada: un elemento typo Team 'A'
Salida: un entero que representa la diferencia de goles (los anotados menos los recibidos). Del 
			equipo durante el torneo.
*/
int calcDiferenciaGoles(struct Team A){
	int ans = (A.golesAnotados - A.golesRecibidos);
	return ans;
}

/*
Nombre: nonCapitalCmp
entrada: dos strings 'a' y 'b'.
salida: un entero que toma valor 0 si ambos strings son iguales, 1 si 'b' es mayor y -1 si 'a' es mayor.
Nota: no considera las mayusculas como menores a las minusculas. 'A' == 'a'.
*/
int nonCapitalCmp(string a, string b){
	int ans = 0;
	string::iterator iA = a.begin();
	string::iterator iB = b.begin();
	char hA,hB;
	while (iA != a.end() && iB != b.end() && ans == 0){
		if (*iA <= 'Z'){
			hA = *iA + 32;
		} else{
			hA = *iA;
		}

		if (*iB <= 'Z'){
			hB = *iB + 32;
		} else{
			hB = *iB;
		}

		if (hA < hB){
			ans = 1;
		} else if (hA > hB){
			ans = -1;
		}
		++iA;
		++iB;
	}

	if (ans == 0 && (iA != a.end() || iB != b.end())){
		if (iA != a.end()){
			ans = 1;
		} else{
			ans = -1;
		}
	}
	return ans;
}

/*
Esta sobrecarga del operador < esta para utilizar en la operacion 'printInfo', la operacion 'sort'
	de la libreria 'algorithm'.
Compara priorizando los puntos, luego la diferencia de goles, luego los goles anotados, y finalmente
	el orden alfabetico de los nombres.
*/
bool operator <(struct Team A, struct Team B){
	bool ans;
	if (A.puntos != B.puntos){
		ans = A.puntos > B.puntos;
	} else if (calcDiferenciaGoles(A) != calcDiferenciaGoles(B)) {
		ans = calcDiferenciaGoles(A) > calcDiferenciaGoles(B);
	} else if (A.golesAnotados != B.golesAnotados){
		ans = A.golesAnotados > B.golesAnotados;
	} else {
		if (nonCapitalCmp(A.name, B.name) == 1){
			ans = true;
		} else {
			ans = false;
		}
	}
	return ans;
}

/*
nombre: myFind
entrada: un arreglo de tipo Team 'equipos', un entero 'T' que representa el tamaño del arreglo y 
			un string 'pal'.
salida: un entero que representa el indice en 'equipos' en el que el nombre del equipo que este 
			representa es igual a 'pal'
*/
int myFind(Team * equipos, int T, string pal){
	int i = 0;
	while (i < T && equipos[i].name != pal){
		++i;
	}
	if (i==T){
		fprintf(stderr,"Error: index not found\n");
	}
	return i;
}

/*
Nombre: printSpacesString
Entrada: un string 'pal' y un entero 'num' que representa los espacios que debe ocupar.
Descripcion: imprime 'pal', haciendo que ocupe 'num' espacios. Los que hagan falta los añade al inicio.
*/
void printSpacesString(string pal, int num){
	while (num > pal.size()){
		printf(" ");
		--num;
	}
	cout << pal;
}

/*
Nombre: fullEqualityCmp
Entrada: dos estructuras Team 'A' y 'B'.
Salida: retorna 'true' si ambas son iguales desde puntos, diferencia de goles y goles anotados. De lo 
			contrario retorna 'false'.
*/
bool fullEqualityCmp(struct Team A, struct Team B){
	bool ans = (A.puntos == B.puntos);
	ans = ans && (A.golesAnotados == B.golesAnotados);
	ans = ans && (calcDiferenciaGoles(A) == calcDiferenciaGoles(B));
	return ans;
}

/*
Nombre: actualizarInformacion
entrada: dos estructuras Team 'a' y 'b' y dos enteros 'golA' y 'golB'. Las structuras son los equipos que disputaron
			el partido, y 'golA' y 'golB' son los goles que metio cada uno.
Descripcion: las estructuras son pasadass por referencia, por lo que el 'retorno' se realiza por este mecanismo. Lo que
				hace la operacion es actualizar los partidosJugados, golesAnotados, golesRecibidos y puntos de 
				cada equipo segun como quedo el partidos.
*/
void actualizarInformacion(struct Team& a, int golA, struct Team& b, int golB){
	++a.partidosJugados;
	a.golesAnotados += (golA);
	a.golesRecibidos += (golB);

	++b.partidosJugados;
	b.golesAnotados += (golB);
	b.golesRecibidos += (golA);

	if (golA == golB){
		a.puntos += (1);
		b.puntos += (1);
	} else if (golA > golB){
		a.puntos += (3);
	} else{
		b.puntos += (3);
	}
}
/*
nombre: printInfo
Entrada: un arreglo de Team: 'equipos' que contiene toda la informacion de los distintos equipos del caso. Un 
			entero 'T' que indica cuantos elementos tiene el arreglo.
Descripcion: imprime la informacion segun el formato requerido.
*/
void printInfo(struct Team* equipos, int T){
	sort(equipos,equipos+T);
	int i;
	int puesto = 1;
	for (i = 0 ; i < T ; ++i, ++puesto){
		if (puesto == 1){
			printf("%2d. ",puesto);
		} else if (!fullEqualityCmp(equipos[i-1], equipos[i])){
			printf("%2d. ",puesto);
		}else{
			printf("    ");
		}
		printSpacesString(equipos[i].name, 15);
		printf(" %3d %3d %3d %3d %3d ",equipos[i].puntos,equipos[i].partidosJugados,equipos[i].golesAnotados,equipos[i].golesRecibidos, calcDiferenciaGoles(equipos[i]));

		if (equipos[i].partidosJugados == 0){
			printf("   N/A\n");
		} else{
			printf("%6.2lf\n",((float)(equipos[i].puntos*100))/((float)(equipos[i].partidosJugados*3)));
		}
	}
}

/*
nombre: leer
Descripcion: realiza la lectura de los datos, los guarda en las estructuras requeridas e invoca a las operaciones
				/funciones requeridas.
*/

void leer(){
	struct Team equipos[MaxTeams];
	int T, G;
	int i;
	int index1, index2;
	int golEqu1, golEqu2;
	string nEqu1,nEqu2, nEqu;
	char t;
	scanf("%d %d",&T,&G);
	while (T != 0 || G != 0){
		for (i = 0;i < T;++i){
			cin >> nEqu;
			startTeam(equipos[i], nEqu);
		}
		/*cout << "T es: " << T << " Estes es G: "<< G <<endl;*/
		for (i = 0;i < G;++i){
			cin >> nEqu1;
			index1 = myFind(equipos,T,nEqu1);
			scanf("%d",&golEqu1);
			scanf("%c",&t);
			scanf("%c",&t);
			scanf("%d",&golEqu2); 
			cin >> nEqu2;
			/*cout << nEqu1 << golEqu1 << golEqu2 << nEqu2 << endl;*/
			index2 = myFind(equipos,T,nEqu2);
			/*
			if (index1 == index2){
				fprintf(stderr,"Error: index is the same\n");
				cerr << equipos[index1].name << " | y el otro | "<<equipos[index2].name<<endl;
				cerr << nEqu1 << " | y el otro | "<<nEqu2<<endl;
				fprintf(stderr,"goles primero %d - goles segundo %d\n",golEqu1,golEqu2);
			}
			*/
			actualizarInformacion(equipos[index1],golEqu1,equipos[index2],golEqu2);
		}

		printInfo(equipos, T);
		
		scanf("%d %d",&T,&G);
		if (T != 0 || G != 0){
			cout << endl;
		}
	}
}

int main(){
	leer();
	return 0;
}
