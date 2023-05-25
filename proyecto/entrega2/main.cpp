/*
Oscar vargas Pabon
8975574
Estructura de datos - Grupo B
*/

/*
################################################################################################################
############################### traer BigInteger y las operaciones que requiero ################################
################################################################################################################
*/
/*
Esto viene de bigInteger.h
*/
#include <iostream>
#include <list>
#include <stack>
#include <string>

typedef char type;

#define Base 10

class BigInteger {
private:
	std::list<type> digits;
	bool sign;
	
	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-# operaciones internas de la clase  #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	std::list<type> rawAddition ( BigInteger & );
	std::list<type> rawSubstraction ( BigInteger & , bool , bool & );
	std::list<type> rawProduct( BigInteger & );

	void euclidianDivision( BigInteger &, std::list<type> &, std::list<type> & );

	static void borrar0Inicio( std::list<type> & );


	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# operaciones comparacion #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	int rawCmp( BigInteger & );

	bool isBigger( BigInteger & );
	bool isSmaller( BigInteger & );
	bool isEqual( BigInteger & );

public:
	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# Constructores #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/
	BigInteger();
	BigInteger( const std::string & );
	BigInteger( const BigInteger & );

	/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-# operaciones aritmeticas #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	*/

	void add( BigInteger & );

	void substract( BigInteger & );

	void product( BigInteger & );

	void quotient( BigInteger & );

	void remainder( BigInteger & );

	void pow( int );
	BigInteger powNew( int );


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

	std::string toString();

	static BigInteger sumarListaValores( std::list<BigInteger> & );
	static BigInteger multiplicarListaValores ( std::list<BigInteger> & );

	bool getSign();
	int getDigitSize();
	type getDigit( int );

};
/*
Esto viene de bigInteger.cpp
*/
/*
Constructor
Entrada: una referencia a un std::string 'str'
Descripcion: inicia los digitos como lo indica el std::string.
*/
BigInteger::BigInteger( const std::string &str ){
	bool error = false, primerNo0 = false;
	int i = 0;
	if ( str[i] == '-' ){
		++i;
		sign = false;
	} else if ( str[i] == '+' ){
		++i;
		sign = true;
	} else {
		sign = true;
	}
	while ( i < str.size() && !error ){
		if ( str[i] < '0' || str[i] > '9' ){
			error = true;
		} else if ( str[i] == '0' ){
			if ( primerNo0 ){
				digits.push_back( 0 );
			}
			++i;
		} else {
			primerNo0 = true;
			digits.push_back( str[i] - '0' );
			++i;
		}
	}
	if ( error ){
		digits.clear();
		sign = false;
		std::cerr << "Error: el arreglo tiene digitos no soportados por la clase BigInteger: " << str[i] << '|' << std::endl;
	} else if ( !sign && digits.size() == 0 ){
		std::cerr << "Error: has ingresado un numero no valido, que es usado por la clase como codigo de error: -0" << std::endl;
	}
}

/*
Nombre: rawCmp
Entrada: un elemento del tipo BigInteger 'b', el otro ya esta 'pasado' en la invocacion.
Salida: retorna 0 si ambos son iguales, 1 si b es el menor y -1 si b es el mayor.
*/
int BigInteger::rawCmp( BigInteger &b ){
	int ans;
	if ( sign != b.sign ){
		ans = ( sign ) ? 1 : -1;
	} else if ( digits.size() != (b.digits).size() ){
		ans = ( digits.size() > (b.digits).size() ) ? 1 : -1;

		if ( !sign ){
			ans *= -1;
		}
	} else {
		std::list<type>::iterator itD = digits.begin();
		std::list<type>::iterator itB = (b.digits).begin();
		ans = 0;
		while ( itD != digits.end() && itB != (b.digits).end() && ans == 0 ){
			if ( *itD != *itB ){
				ans = ( (*itD) > (*itB) ) ? 1 : -1;
			}
			++itD;
			++itB;
		}

		if ( !sign ){
			ans *= -1;
		}

	}
	return ans;
}

/*
Nombre: isBigger
Entrada: un objeto BigInteger 'b'.
Salida: true si el objeto sobre el que fue invocada la funcion es mayor a 'b'.
*/
bool BigInteger::isBigger( BigInteger &b ){
	bool ans = ( rawCmp( b ) == 1 );
	return ans;
}
/*
Nombre: isEqual
Entrada: un objeto BigInteger 'b'.
Salida: true si el objeto sobre el que fue invocada la funcion es igual a 'b'.
*/
bool BigInteger::isEqual( BigInteger &b ){
	bool ans = ( rawCmp( b ) == 0 );
	return ans;
}

bool BigInteger::operator > ( BigInteger &b ){
	bool ans = isBigger( b );
	return ans;
}
bool BigInteger::operator == ( BigInteger &b ){
	bool ans = isEqual( b );
	return ans;
}

/*
#################################################################################################################
############################################ resolver el problema ###############################################
#################################################################################################################
######################################## B - Bigger or Smaller ##################################################
#################################################################################################################
*/

/*
	Complejidad solucion:

la solucion se realiza en la funcion 'esMayor'. Esta realiza hasta 3 comparaciones entre los BigInteger.
	La segunda y tercera se realizan solo cuando la parte entera de ambos decimales es igual. La tercera se
	realiza cuando la parte decimal de ambos decimales es distinta. Sin embargo, para la segunda y tercera 
	comparacion, se agregan a las partes decimales tantos ceros a la derecha como necesarios para que ambos
	BigInteger terminen con la misma cantidad de digitos. Es por esto que:
l:= entero1.size()
n:= max( decimal1.size(), decimal2.size() )
T(n) = O( l + 2n)
T(n) = O( l + n)
*/

#include <stdio.h>


void leerDecimal( std::string &, std::string & );
void reverseString( std::string & );
int esMayor( std::string &, std::string &, std::string &, std::string & );
void leerImprimir();

int main(){
	leerImprimir();
	return 0;
}

void leerImprimir(){
	std::string entero1, entero2, decimal1, decimal2;
	char t;
	int i = 1;
	int res;
	while ( scanf( "%c", &t ) != EOF ){
		if ( t > '0' && t <= '9' ){
			entero1.push_back( t );
		}
		printf("Case %d: ", i );
		leerDecimal( entero1, decimal1 );
		leerDecimal( entero2, decimal2 );

		res = esMayor( entero1, decimal1, entero2, decimal2 );

		if ( res == 0 ){
			printf("Same\n");
		} else if ( res == 1 ) {
			printf("Bigger\n");
		} else{
			printf("Smaller\n");
		}

		entero1.clear();
		entero2.clear();
		decimal1.clear();
		decimal2.clear();
		++i;
	}

}

/*
Nombre: esMayor
Entrada: std::string que representan dos numeros con sus respectivos decimales
Salida: retorna 0 si ambos numeros son iguales, 1 si el '1' es mayor al '2' y -1 de lo contrario.
*/
int esMayor( std::string &entero1, std::string &decimal1, std::string &entero2, std::string &decimal2 ){
	int ans;
	BigInteger numA( entero1 ), numB( entero2 );

	if ( numA == numB ){
		int maxLen = ( decimal1.size() > decimal2.size() ) ? decimal1.size() : decimal2.size();
		
		while ( decimal1.size() < maxLen ){
			decimal1.push_back( '0' );
		}
		while ( decimal2.size() < maxLen ){
			decimal2.push_back( '0' );
		}

		numA = BigInteger( decimal1 );
		numB = BigInteger( decimal2 );

		if ( numA == numB ){
			ans = 0;
		} else if ( numA > numB ){
			ans = 1;
		} else{
			ans = -1;
		}

	} else if ( numA > numB ){
		ans = 1;
	} else{
		ans = -1;
	}
	return ans;
}

/*
Nombre: leerDecimal
Entrada: referencias a std::string 'entero' y 'decimal'
Descripcion: lee 1 numero decimal compuesto por su parte entera y su parte decimal, guardandolo en los std::string
				que recibe la funcion como referencia.
*/
void leerDecimal( std::string &entero, std::string &decimal ){
	int t;
	t = getc( stdin );
	while ( t != '.' ){
		entero.push_back( t );
		t = getc( stdin );
	}
	t = getc( stdin );
	decimal.push_back('1');
	int ceros = 0;
	while ( t != '\n' && t != ' ' ){
		if ( t == '0' ){
			++ceros;
		} else {

			while ( ceros > 0 ){
				decimal.push_back( '0' );
				--ceros;
			}

			decimal.push_back( t );
		}
		t = getc( stdin );
	}
}
