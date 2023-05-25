/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

#include "bigInteger.h"



/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# constructores #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/

/*
Constructor
Entrada: nada.
Descripcion: inicia los digitos en NULL y el signo en true (true es el predeterminado para el signo).
*/
BigInteger::BigInteger(){
	sign = true;
}
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
		std::cerr << "Error: el arreglo tiene digitos no soportados por la clase BigInteger: " << str[i] << std::endl;
	} else if ( !sign && digits.size() == 0 ){
		std::cerr << "Error: has ingresado un numero no valido, que es usado por la clase como codigo de error: -0" << std::endl;
	}
}
/*
Constructor
Entrada: otra instancia BigInteger
Descripcion: hace una copia exacta del BigInteger de la entrada. 
*/
BigInteger::BigInteger( const BigInteger &ref ){
	std::list<type>::const_iterator it;
	sign = ref.sign;
	for ( it = (ref.digits).cbegin() ; it != (ref.digits).cend() ; ++it ){
		digits.push_back( *it );
	}
}

/*
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-# operaciones internas de la clase  #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
	#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/

/*
Nombre: rawAddition.
Entrada: un objeto BigInteger 'b', que es el que se le va a sumar.
Salida: una lista de enteros que representa la suma de ambas instancias BigInteger.
*/
std::list<type> BigInteger::rawAddition ( BigInteger &sumando ){
	std::list<type> res, *a, *b;
	type carreo = 0;
	type dig, tmp;

	if ( digits.size() >= (sumando.digits).size() ){
		a = &digits;
		b = &sumando.digits;
	} else{
		a = &sumando.digits;
		b = &digits;
	}

	std::list<type>::reverse_iterator itA = a->rbegin();
	std::list<type>::reverse_iterator itB = b->rbegin();

	while ( itA != a->rend() && itB != b->rend() ){
		tmp = (*itA) + (*itB) + carreo;
		dig = tmp % Base;
		carreo = tmp / Base;
		res.push_front( dig );
		++itA;
		++itB;
	}

	while ( itA != a->rend() ){
		tmp = (*itA) + carreo;
		dig = tmp % Base;
		carreo = tmp / Base;
		res.push_front( dig );
		++itA;
	}
	if ( carreo != 0 ){
		res.push_front( carreo );
	}
	return res;
}
/*
Nombre: rawSubstraction.
Entrada: un objeto BigInteger 'b', que es uno de los numeros a restar. Un booleano 'signB' que representa el
			signo de b (esto se hace porque no necesariamente sabemos si entramos aqui porque hay una resta o no).
			Un booleano pasado por referencia 'resultingSign', que es el metodo que usaremos para devolver el signo
			restante.
Salida: una lista de enteros que representa la resta de ambas instancias BigInteger.
*/
std::list<type> BigInteger::rawSubstraction ( BigInteger &restando, bool signB, bool &resultingSign ){
	std::list<type> res;

	type tmp;

	bool sA = sign, sR = restando.sign;

	sign = true;
	restando.sign = true;
	tmp = rawCmp( restando );
	sign = sA;
	restando.sign = sR;

	if ( tmp == 0 ){
		resultingSign = true;
	} else{
		std::list<type> *a, *b;

		std::list<type>::reverse_iterator itA;
		std::list<type>::reverse_iterator itB;

		type dig, carreo;

		if ( tmp == 1){
			a = &digits;
			b = &restando.digits;
			resultingSign = sign;
		} else {		
			a = &restando.digits;
			b = &digits;
			resultingSign = signB;
		}

		itA = a->rbegin();
		itB = b->rbegin();
		carreo = 0;

		while ( itB != b->rend() ){
			dig = (*itA) - ( (*itB) + carreo );

			if ( dig < 0 ){
				dig += Base;
				carreo = 1;
			} else{
				carreo = 0;
			}

			res.push_front( dig );

			++itA;
			++itB;
		}
		while ( itA != a->rend() ){
			dig = (*itA) - carreo;

			if ( dig < 0 ){
				dig += Base;
				carreo = 1;
			} else{
				carreo = 0;
			}

			res.push_front( dig );
			++itA;
		}
		borrar0Inicio( res );
	}
	return res;
}

/*
Nombre: rawProduct
Entrada: un objeto BigInteger 'b'.
Salida: una lista que representa los digitos despues de realizar la multiplicacion entre el objeto y 'b'.
*/
std::list<type> BigInteger::rawProduct( BigInteger &b ){
	std::list<type> res( ( digits.size() + (b.digits).size() ), 0 );

	std::list<type>::reverse_iterator itRes, itStartRes;
	std::list<type>::reverse_iterator itA;
	std::list<type>::reverse_iterator itB;

	type tmp, carry;

	for ( itA = digits.rbegin(), itStartRes = res.rbegin() ; itA != digits.rend() ; ++itA, ++itStartRes ){
		carry = 0;
		itRes = itStartRes;
		for ( itB = (b.digits).rbegin() ; itB != (b.digits).rend() ; ++itB ){
			tmp = ( (*itA) * (*itB) ) + carry + (*itRes);
			carry = tmp / Base;
			*itRes = tmp % Base;

			++itRes;
		}
		*itRes += carry;
	}
	borrar0Inicio( res );
	return res;
}
/*
Nombre: euclidianDivision
Entrada: una referencia a una instancia BigInteger 'b'. Dos punteros a punteros a std::list<type>: 
			'quotient' y 'remainder' que seran utilizado para retornar los valores.
Descripcion: realiza la division euclidiana de 'this' entre 'b' (no toma en cuenta los signos).
*/
void BigInteger::euclidianDivision( BigInteger &b, std::list<type> &quotient, std::list<type> &remainder ){
	bool bSign = b.sign;
	b.sign = true;/* para usar comodamente 'substract' */

	BigInteger aux ( *this );
	aux.sign = true;

	quotient.push_back( 0 );

	int count = 0;
	while ( (b.digits).size() < digits.size() ) {
		++count;
		(b.digits).push_back( 0 );
		quotient.push_back( 0 );
	}
	std::list<type>::iterator quoPos;
	for ( quoPos = quotient.begin() ; quoPos != quotient.end() ; ++quoPos ){		
		while ( aux >= b ){
			*quoPos += 1;
			aux.substract( b );
		}

		if ( count > 0 ) {
			(b.digits).pop_back();
		}
		--count;
	}
	remainder = aux.digits; 
	b.sign = bSign;
}

/*
Nombre: borrar0Inicio
Entrada: un puntero a std::list<int>.
Descripcion: borra los ceros que se encuentran al inicio de la lista, hasta que se topa con un digito distinto de 0.
*/
void BigInteger::borrar0Inicio( std::list<type> &ref){
	bool flag = true;
	while ( ref.size() > 0 && flag ){
		if ( ref.front() != 0 ){
			flag = false;
		} else{
			ref.pop_front();
		}
	}
}

/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# operaciones aritmeticas #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/

/* 
Nombre: add
Entrada: un objeto BigInteger 'b'.
Descripcion: realiza la suma solicitada y la guarda en el objeto.
*/
void BigInteger::add( BigInteger &b){
	if ( ( ( !sign || b.sign ) && ( !b.sign || sign ) ) ){
		digits = rawAddition( b );
	} else{
		bool tmp;
		digits = rawSubstraction( b, b.sign, tmp );
		sign = tmp;
	}
}
/* 
Nombre: substract
Entrada: un objeto BigInteger 'b'.
Descripcion: realiza la resta solicitada y la guarda en el objeto.
*/
void BigInteger::substract( BigInteger &b ){
	if ( ( ( !sign || !b.sign ) && ( b.sign || sign ) ) ){
		digits = rawAddition( b );
	} else{
		bool tmp;
		digits = rawSubstraction( b, !b.sign, tmp );
		sign = tmp;
	}
}
/*
Nombre: quotient
Entrada: una instancia BigInteger 'b'
Descripcion: realiza la division entera solicitada y la guarda en el objeto.
*/
void BigInteger::quotient ( BigInteger &b ){

	if ( (b.digits).size() == 0 ){
		std::cerr << "Error: no se puede realizar una division entre 0." << std::endl;
	} else {

		std::list<type> rem, quo;
		euclidianDivision( b, quo, rem );
		digits = quo;
	
		sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );
	
		borrar0Inicio( digits );
	}
}
/*
Nombre: remainder
Entrada: una instancia BigInteger 'b'
Descripcion: realiza la division entera solicitada y la guarda en el objeto
*/
void BigInteger::remainder( BigInteger &b ) {
	if ( (b.digits).size() == 0 ){
		std::cerr << "Error: no se puede realizar un modulo entre 0." << std::endl;
	} else{
		std::list<type> quo;
	
		euclidianDivision( b, quo, digits );
		
		if ( ( sign && !b.sign ) || ( b.sign && !sign )  ){
			add ( b );
		}
	}
}

/* 
Nombre: product
Entrada: un objeto BigInteger 'b'.
Descripcion: realiza la multiplicacion solicitada y la almacena en el mismo objeto.
*/
void BigInteger::product( BigInteger &b ){
	if ( digits.size() == 0 || (b.digits).size() == 0 ){
		digits.clear();
		sign = true;
	} else {
		sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );
		digits = rawProduct( b );
	}
}
/*
Nombre: powNew
Entrada: un entero 'exponente' que representa el exponente a elevar.
Salida: un BigInteger que representa la instancia BigInteger elevada por el 'exponente'
*/
BigInteger BigInteger::powNew( int exponente ){
	BigInteger tmp( *this );

	tmp.pow( exponente );
	return tmp;
}

/*
Nombre: pow
Entrada: un entero 'exponente' que representa el exponente a elevar.
Descripcion: guarda en la instancia BigInteger el resultado de elevarla por 'exponente'.
*/
void BigInteger::pow( int exponente ){
	if ( exponente < 0 || ( exponente == 0 && digits.size() == 0 ) ){
		std::cerr << "Error: el contenedor BigInteger no soporta elevarlo por el exponente " << exponente << " o 0^0." << std::endl;
	} else if ( exponente == 0 ){
		digits.clear();
		digits.push_back( 1 );
		sign = true;
	} else if ( exponente > 1) {

		BigInteger otro( *this );

		std::stack<bool> operar;
		while ( exponente > 1 ){
			operar.push( (exponente % 2 ) == 1 );
			exponente /=  2;
		}
		while ( !operar.empty() ){
			product( *this );
			if ( operar.top() ){
				product( otro );
			}
			operar.pop();
		}
	}
}

/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# sobrecargas operaciones aritmeticas #-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/
/*
sobrecarga: +
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la suma solicitada.
*/
BigInteger BigInteger::operator + ( BigInteger &b ){	
	BigInteger res( *this );
	res.add( b );
	return res;
}
/*
sobrecarga: -
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la resta solicitada.
*/
BigInteger BigInteger::operator - ( BigInteger &b ){
	BigInteger res( *this );
	res.substract( b );
	return res;
}
/*
sobrecarga: *
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la multiplicacion solicitada.
*/
BigInteger BigInteger::operator * ( BigInteger &b ){
	BigInteger res;
	if ( digits.size() != 0 && (b.digits).size() != 0 ){
		res.sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );
		res.digits = rawProduct( b );
	}
	return res;
}
/*
sobrecarga: /
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la division solicitada.
*/
BigInteger BigInteger::operator / ( BigInteger &b ){
	BigInteger res;

	if ( (b.digits).size() == 0 ){
		std::cerr << "Error: no se puede realizar una division entre 0." << std::endl;
		res.sign = false;
	} else if ( digits.size() != 0 ){

		std::list<type> rem;
		euclidianDivision( b, res.digits, rem );


		res.sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );

		borrar0Inicio( res.digits );
		if ( (res.digits).size() == 0 ){
			res.sign = true;
		}
	}

	return res;
}
/*
sobrecarga: %
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la operacion modulo solicitada.
*/
BigInteger BigInteger::operator % ( BigInteger &b ){
	BigInteger res;
	if ( (b.digits).size() == 0 ){
		std::cerr << "Error: No se puede realizar un modulo entre 0." << std::endl;
		res.sign = false;
	} else if ( digits.size() != 0 ){

		std::list<type> quo;
		euclidianDivision( b, quo, res.digits );

		res.sign = sign;

		if ( ( sign && !b.sign ) || ( b.sign && !sign )  ){
			res.add ( b );
		}
	}
	return res;
}



/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-# operaciones comparacion #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/

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
Nombre: isSmaller
Entrada: un objeto BigInteger 'b'.
Salida: true si el objeto sobre el que fue invocada la funcion es menor a 'b'.
*/
bool BigInteger::isSmaller( BigInteger &b ){
	bool ans = ( rawCmp( b ) == -1 );
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

/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-# sobrecargas comparacion #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/

bool BigInteger::operator > ( BigInteger &b ){
	bool ans = isBigger( b );
	return ans;
}
bool BigInteger::operator >= ( BigInteger &b ){
	bool ans = !isSmaller( b );
	return ans;
}

bool BigInteger::operator < ( BigInteger &b ){
	bool ans = isSmaller( b );
	return ans;
}

bool BigInteger::operator <= ( BigInteger &b ){
	bool ans = !isBigger( b );
	return ans;
}
bool BigInteger::operator == ( BigInteger &b ){
	bool ans = isEqual( b );
	return ans;
}
bool BigInteger::operator != ( BigInteger &b ){
	bool ans = !( isEqual( b ) );
	return ans;
}

/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-# otras funciones #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/
/*
Nombre: toString
Salida: genera un string que contiene los digitos del numero.
*/
std::string BigInteger::toString(){
	std::string res;
	if ( digits.empty() ){
		if ( sign ){
			res.push_back( '0' );
		} else {
			res.push_back( '-' );
			res.push_back( '0' );
		}
	} else {
		if ( !sign ){
			res.push_back( '-' );
		}
		std::list<type>::iterator it;
		for ( it = digits.begin() ; it != digits.end() ; ++it ){
			res.push_back( (*it) + '0' );
		}
	}
	return res;
}

/*
Nombre: getSign
Salida: el signo (en booleano) que tiene la instancia BigInteger. 'true' para los positivos y 'false' para los negativos.
*/
bool BigInteger::getSign(){
	return sign;
}
/*
Nombre: getDigitSize
Salida: un entero que tiene la cantidad de digitos que posee el numero
*/
int BigInteger::getDigitSize(){
	return digits.size();
}

/*
Nombre: getDigit
Entrada: un entero 'n' que representa la poscicion del digito solicitado
Salida: un tipo 'type' que tiene el valor del digito 'n'.
*/
type BigInteger::getDigit( int n ){
	type res;
	if ( n < 0 || n >= digits.size() ){
		std::cerr << "Error: El digito solicitado : " << n << " es inexistente." << std::endl;
		res = -1;
	} else if ( n <= digits.size()/2 ){
		int i = 0;
		std::list<type>::iterator it = digits.begin();
		while ( i < n ){
			++it;
			++i;
		}
		res = *it;
	} else {
		int i = digits.size() - 1;
		std::list<type>::reverse_iterator it = digits.rbegin();
		while ( i > n ){
			++it;
			--i;
		}
		res = *it;
	}
	return res;
}
/*
Nombre: sumarListaValores
Entrada: una referencia a un std::list<BigInteger> 'ref'
Salida: un BigInteger que contiene la suma de todos los elementos de la lista
*/
BigInteger BigInteger::sumarListaValores( std::list<BigInteger> &ref ){
	BigInteger res;
	for ( std::list<BigInteger>::iterator it = ref.begin() ; it != ref.end() ; ++it ){
		res.add( *it );
	}
	return res;
}
/*
Nombre: multiplicarListaValores
Entrada: una referencia a un std::list<BigInteger> 'ref'
Salida: un BigInteger que contiene la multiplicacion de todos los elementos de la lista
*/
BigInteger BigInteger::multiplicarListaValores ( std::list<BigInteger> &ref ){
	BigInteger res("1");
	for ( std::list<BigInteger>::iterator it = ref.begin() ; it != ref.end() ; ++it ){
		res.product( *it );
	}
	return res;
}

