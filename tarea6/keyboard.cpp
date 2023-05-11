/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
	Complejidad Solucion:
Donde n es la cantidad de caracteres que tiene la linea, O(n) es la complejidad que tiene resolver el problema para
	esa linea. Esto porque el while itera tantas veces como caracteres en la linea, leyendo 1 por uno. Para cada caracter
	nos encontramos con un condicional que determina que hacer con el caracter, sin embargo, todas las posibilidades
	desembocan en operaciones que funcionan en O(1). Como esto se repite n veces: T(n) = n*O(1) = O(n).

while( t != '\n' ){
	if ( t == '['){
		final = false;
		it = text.begin();
	}else if ( t == ']' ){
		final = true;
	} else if ( final ){
		text.push_back( t );
	} else{
		text.insert( it, t );
	}
	t = getc( stdin );
}
*/

#include <list>
#include <stdio.h>

void leer();
void printList( std::list<char> & );

int main(){
	leer();
	return 0;
}
/*
Nombre: leer
Descripcion: realiza la lectura del problema, resolviendo el problema en el proceso.
*/
void leer(){
	std::list<char> text;
	std::list<char>::iterator it;
	bool final; /* toma valor true cuando nos encontramos al final */
	char t = getc( stdin );
	while ( t != EOF ){
		final = true;
		while( t != '\n' ){
			if ( t == '['){
				final = false;
				it = text.begin();
			} else if ( t == ']' ){
				final = true;
			} else if ( final ){
				text.push_back( t );
			} else{
				text.insert( it, t );
			}
			t = getc( stdin );
		}
		printList( text );
		text.clear();
		t = getc( stdin );
	}
}

/*
Nombre: printList
Entradad: una referencia a una lista de caracteres.
Descripcion: imprime la lista de caracteres del primer nodo al ultimo nodo. Al final imprime un '\n'.
*/
void printList( std::list<char> &text ){
	std::list<char>:: iterator it = text.begin();
	while ( it != text.end() ){
		putc( *it, stdout );
		++it;
	}
	putc( '\n' , stdout );
}