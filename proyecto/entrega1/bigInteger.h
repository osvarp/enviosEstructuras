/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <iostream>
#include <list>

using namespace std;

typedef int type;

#define Base 10

/* no se donde poner esto */
void borrar0Inicio( list<type> *);

class BigInteger {
private:
	list<type> *digits;
	bool sign;
	
	/* estas estan para tratar de no repetir tanto codigo */
	list<type>* sumaCompleta ( BigInteger & , bool, bool & );
	list<type>* rawAddition ( BigInteger & );
	list<type>* rawSubstraction ( BigInteger & , bool , bool & );
	list<type>* rawProduct( BigInteger & );
	
	/* aun por definir */
	void euclidianDivision( BigInteger &, list<type> **, list<type> ** );
	list<type>* rawPow( list<type> * );

public:
	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# Constructores #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/
	BigInteger();
	BigInteger( char* );
	BigInteger( const BigInteger & );

	void operator = ( const BigInteger & );

	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# operaciones aritmeticas #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	void add( BigInteger & );
	BigInteger addNew( BigInteger & );

	void substract( BigInteger & );
	BigInteger substractNew( BigInteger & );


	void product( BigInteger & );
	BigInteger productNew( BigInteger& );


	void quotient( BigInteger & );
	BigInteger quotientNew( BigInteger & );

	/*aun por definir*/
	void remainder( BigInteger & );
	BigInteger remainderNew( BigInteger & );

	void pow( BigInteger & );
	BigInteger powNew( BigInteger & );


	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-# sobrecargas operaciones aritmeticas #-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	BigInteger operator + ( BigInteger & );
	BigInteger operator - ( BigInteger & );
	BigInteger operator * ( BigInteger & );
	BigInteger operator / ( BigInteger & );
	BigInteger operator % ( BigInteger & );	


	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# operaciones comparacion #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	int rawCmp( BigInteger & );

	bool isBigger( BigInteger & );
	bool isSmaller( BigInteger & );
	bool isEqual( BigInteger & );

	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# sobrecargas comparacion #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	bool operator > ( BigInteger & );
	bool operator >= ( BigInteger & );
	bool operator < ( BigInteger & );
	bool operator <= ( BigInteger & );
	bool operator == ( BigInteger & );
	bool operator != ( BigInteger & );

	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# otras funciones #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	char* toString();
	void display();

};

/* aun por definir */
BigInteger sumarListaValores( BigInteger * );
BigInteger multiplicarListaValores ( BigInteger * );

#endif