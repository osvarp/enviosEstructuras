/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

#include "bigInteger.h"
#include <stdio.h>
#include <string>
using namespace std;

void elContador();
void fib();
void imprimirFactorial();
BigInteger factorial( int );
char * intToCad( int );

int main(){
	int i;
	printf("[0]fib | [1]contador | [2]factorial:\n> ");
	scanf("%d",&i);
	if ( i == 0 ){
		fib();
	} else if ( i == 1 ){
		elContador();
	} else{
		imprimirFactorial();
	}
	return 0;
}

void imprimirFactorial(){
	BigInteger ans;
	int n = 10;
	while ( n != 0 ){
		scanf("%d",&n);
		ans = factorial( n );
		printf("%d! = ", n);
		ans.display();
		cout << endl;
	}
}

BigInteger uno("1");

BigInteger factorial( int n ){
	BigInteger ans;
	if ( n == 0 ){
		ans = uno;
	} else {
		BigInteger hola( intToCad( n ) ), otro = factorial( n -1 );
		ans = hola * otro;
	}
	return ans;
}

char * intToCad( int n ){
	string tmp;
	while ( n > 0 ){
		tmp.push_back( (n % 10) + '0' );
		n /= 10;
	}
	char *res = new char[tmp.size()+1];
	res[tmp.size()] = '\0';
	string::reverse_iterator it = tmp.rbegin();
	int i = 0;
	while  ( it != tmp.rend() ){
		res[i] = *it;
		++i;
		++it;
	}
	return res;
}


void fib(){
	printf("¿cual quiere que sea el tamaño de los bloques?:\n> ");
	int blockSize, i;
	scanf("%d", &blockSize);
	BigInteger a, b("1"), c;
	char t;
	do{
		i = 0;
		while ( i < blockSize ){
			b.display();
			cout << endl;
			c = b;
			b = b + a;
			a = c;
			++i;
		}
		t = getc( stdin );
	} while ( t != 'n' );
}

void elContador(){
	BigInteger uno("1"), i;
	char t;
	t = getc( stdin );
	while ( t != 'n' ){
		i.display();
		cout << endl;
		i = i + uno;
		t = getc( stdin );
	}
}