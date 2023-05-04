/*
Oscar Vargas Pabon
8975574
Estructura de datos - Grupo B
*/

#include "bigInteger.h"

/*
Nombre: borrar0Inicio
Entrada: un puntero a list<int>.
Descripcion: borra los ceros que se encuentran al inicio, hasta que se topa con un digito distinto de 0.
*/
void borrar0Inicio( list<int> *ref){
	bool flag = true;
	while ( ref->size() > 0 && flag ){
		if ( ref->front() != 0 ){
			flag = false;
		} else{
			ref->pop_front();
		}
	}
}

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
	digits = new list<type>;
	sign = true;
}
/*
Constructor
Entrada: un arreglo de caracteres.
Descripcion: inicia los digitos como lo indica el arreglo.
*/
BigInteger::BigInteger( char *arr ){
	int i;
	bool error = false, primerNo0 = false;
	digits = new list<type>;
	if ( arr[0] == '-' ){
		i = 1;
		sign = false;
	} else if ( arr[0] == '+' ){
		i = 1;
		sign = true;
	} else {
		i = 0;
		sign = true;
	}
	while ( arr[i] != '\0' && !error ){
		if ( arr[i] < '0' || arr[i] > '9' ){
			error = true;
		} else if ( arr[i] == '0' ){
			if ( primerNo0 ){
				digits->push_back( arr[i] - '0' );
			}
			++i;
		} else {
			primerNo0 = true;
			digits->push_back( arr[i] - '0' );
			++i;
		}
	}
	if ( error ){
		delete digits;
		digits = NULL;
		sign = true;
		cerr << "Error: el arreglo tiene digitos no soportados por la clase BigInteger: " << arr[i] << endl;
	}
}
/*
Constructor
Entrada: otra instancia BigInteger
Descripcion: hace una copia exacta del BigInteger de la entrada. 
*/
BigInteger::BigInteger( const BigInteger &ref ){
	list<type>::iterator it;
	digits = new list<type>;
	sign = ref.sign;
	for ( it = (ref.digits)->begin() ; it != (ref.digits)->end() ; ++it ){
		digits->push_back( *it );
	}
}
/*
Sobrecarga: =
Entrada: una instancia BigInteger.
Descripcion: copia la informacion del objeto BigInteger.
*/
void BigInteger::operator = ( const BigInteger &ref ){
	list<type>::iterator it;
	digits->clear();
	sign = ref.sign;
	for ( it = (ref.digits)->begin() ; it != (ref.digits)->end() ; ++it ){
		digits->push_back( *it );
	}
}


/*
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-# operaciones definidas para la clase #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
*/

/*
Nombre: rawAddition.
Entrada: un objeto BigInteger 'b', que es el que se le va a sumar.
Salida: una lista de enteros que representa la suma de ambas instancias BigInteger.
*/
list<type>* BigInteger::rawAddition ( BigInteger &sumando ){
	list<type>* res = new list<type>;
	list<type> *a, *b;
	type carreo = 0;
	type tmp;

	if ( digits->size() != (sumando.digits)->size() ){
		if ( digits->size() > (sumando.digits)->size() ){
			a = digits;
			b = sumando.digits;
		} else{
			a = sumando.digits;
			b = digits;
		}
	} else{
		a = digits;
		b = sumando.digits;
	}

	list<type>::reverse_iterator itA = a->rbegin();
	list<type>::reverse_iterator itB = b->rbegin();

	while ( itA != a->rend() && itB != b->rend() ){
		tmp = (*itA) + (*itB) + carreo;
		if ( tmp >= Base ){
			carreo = 1;
			tmp -= Base;
		} else {
			carreo = 0;
		}
		res->push_front( tmp );
		++itA;
		++itB;
	}

	while ( itA != a->rend() ){
		tmp = (*itA) + carreo;
		if ( tmp >= Base ){
			carreo = 1;
			tmp -= Base;
		} else{
			carreo = 0;
		}
		res->push_front( tmp );
		++itA;
	}
	if ( carreo == 1 ){
		res->push_front( 1 );
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
list<type>* BigInteger::rawSubstraction ( BigInteger &b, bool signB, bool &resultingSign ){
	list<type>* res = new list<type>;
	list<type> *a, *e;

	list<type>::reverse_iterator itA;
	list<type>::reverse_iterator itE;

	type tmp, carreo;
	bool end = false;

	if ( (b.digits)->size() !=  digits->size() ){	
		if ( (b.digits)->size() > digits->size() ){
			resultingSign = signB;
			a = b.digits;
			e = digits;
		} else {
			resultingSign = sign;
			a = digits;
			e = b.digits;
		}
	} else {
		bool sA = sign, sB = b.sign;
		sign = true;
		b.sign = true;
		tmp = rawCmp( b );
		sign = sA;
		b.sign = sB;
		if ( tmp == 0 ){
			end = true;
			a = digits;
			e = b.digits;
			resultingSign = true;
		} else if ( tmp == 1){
			a = digits;
			e = b.digits;
			resultingSign = sign;
		} else {		
			a = b.digits;
			e = digits;
			resultingSign = signB;
		}
	}
	itA = a->rbegin();
	itE = e->rbegin();
	carreo = 0;
	while ( itE != e->rend() && !end ){
		tmp = (*itA) - ( (*itE) + carreo );
		if ( tmp < 0 ){
			carreo = 1;
			tmp += Base;
		} else {
			carreo = 0;
		}
		res->push_front(tmp);
		++itA;
		++itE;
	}
	while ( itA != a->rend() && !end ){
		tmp = (*itA) - carreo;
		if ( tmp < 0 ){
			carreo = 1;
			tmp += Base;
		} else {
			carreo = 0;
		}
		res->push_front( tmp );
		++itA;
	}
	borrar0Inicio( res );
	return res;
}
/*
Nombre: sumaCompleta
Entrada: un objeto BigInteger 'b', un booleano 'notBsign' que toma valor true cuando se esta realizando una resta y 
			un booleano 'ans' pasado por referencia con el que vamos a retornar el signo restante.
Salida: un puntero a list<type> que representa los digitos resultantes de hacer la suma.
Descripcion: verifica si la operacion es una suma o resta e invoca a las operaciones respectivas
				Notese que a-(-b) es una suma mientras que a+(-b) es una resta.
*/
list<type>* BigInteger::sumaCompleta ( BigInteger &b, bool notBsign, bool &ans ){
	list<type> *res;
	bool signB = ( notBsign ) ? !b.sign : b.sign;
	if ( ( ( !sign || signB ) && ( !signB || sign ) ) ) { /* esta condicion es una doble implicacion */
		res = rawAddition( b );
		ans = sign;
	} else {
		res = rawSubstraction( b, signB, ans );
	}
	return res;
}

/*
Nombre: rawProduct
Entrada: un objeto BigInteger 'b'.
Salida: una lista que representa los digitos despues de realizar la multiplicacion entre el objeto y 'b'.
*/
list<type>* BigInteger::rawProduct( BigInteger &b ){
	list<type> *res = new list<type>;
	res->push_front(0);
	list<type>::reverse_iterator itRes, itStartRes = res->rbegin(), ayuda;
	list<type>::reverse_iterator itA;
	list<type>::reverse_iterator itB;
	type tmp, carry;
	for ( itA = digits->rbegin() ; itA != digits->rend() ; ++itA, ++itStartRes ){
		carry = 0;
		itRes = itStartRes;
		for ( itB = (b.digits)->rbegin() ; itB != (b.digits)->rend() ; ++itB ){
			tmp = ( (*itA) * (*itB) ) + carry;
			carry = ((*itRes) + tmp) / Base;
			*itRes = ( (*itRes) + tmp ) % Base;

			ayuda = itRes;
			++ayuda; /* creo que es mas facil iniciar todos los ceros necesarios */
			if ( ayuda == res->rend() ){
				res->push_front(0);
			}

			++itRes;
		}
		*itRes += carry;
	}
	borrar0Inicio( res );
	return res;
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
	list<type> *res;
	bool tmp;
	res = sumaCompleta( b, false, tmp );
	delete digits;
	digits = res;
	sign = tmp;
}
/* 
Nombre: addNew
Entrada: un objeto BigInteger 'b'.
Salida: Un objeto BigInteger que contiene la suma solicitada.
*/
BigInteger BigInteger::addNew( BigInteger &b){
	BigInteger res;
	delete res.digits;
	res.digits = sumaCompleta( b, false, res.sign );
	return res;
}
/* 
Nombre: substract
Entrada: un objeto BigInteger 'b'.
Descripcion: realiza la resta solicitada y la guarda en el objeto.
*/
void BigInteger::substract( BigInteger &b ){
	list<type> *res;
	bool tmp;
	res = sumaCompleta( b, true, tmp );
	delete digits;
	digits = res;
	sign = tmp;
}
/* 
Nombre: substractNew
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la resta solicitada.
*/
BigInteger BigInteger::substractNew( BigInteger &b ){
	BigInteger res;
	delete res.digits;
	res.digits = sumaCompleta( b, true, res.sign );
	return res;
}
/* 
Nombre: product
Entrada: un objeto BigInteger 'b'.
Descripcion: realiza la multiplicacion solicitada y la almacena en el mismo objeto.
*/
void BigInteger::product( BigInteger &b ){
	sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );
	list<type> *tmp;
	tmp = rawProduct( b );
	delete digits;
	digits = tmp;
}
/* 
Nombre: productNew
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la multiplicacion solicitada.
*/
BigInteger BigInteger::productNew( BigInteger &b ){
	BigInteger res;
	delete res.digits;
	res.sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );
	res.digits = rawProduct( b );
	return res;
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
	BigInteger res;
	delete res.digits;
	res.digits = sumaCompleta( b, false, res.sign );
	return res;
}
/*
sobrecarga: -
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la resta solicitada.
*/
BigInteger BigInteger::operator - ( BigInteger &b ){
	BigInteger res;
	delete res.digits;
	res.digits = sumaCompleta( b, true, res.sign );
	return res;
}
/*
sobrecarga: *
Entrada: un objeto BigInteger 'b'.
Salida: un objeto BigInteger que contiene la multiplicacion solicitada.
*/
BigInteger BigInteger::operator * ( BigInteger &b ){
	BigInteger res;
	delete res.digits;
	res.sign = ( ( !sign || b.sign ) && ( !b.sign || sign ) );
	res.digits = rawProduct( b );
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
	} else if ( digits->size() != (b.digits)->size() ){
		ans = ( digits->size() > (b.digits)->size() ) ? 1 : -1;
	} else {
		list<type>::iterator itD = digits->begin();
		list<type>::iterator itB = (b.digits)->begin();
		ans = 0;
		while ( itD != digits->end() && itB != (b.digits)->end() && ans == 0 ){
			if ( *itD != *itB ){
				ans = ( (*itD) > (*itB) ) ? 1 : -1;
			}
			++itD;
			++itB;
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

char* BigInteger::toString(){
	char* res;
	if ( digits->empty() ){
		res = new char[2];
		res[0] = '0';
		res[1] = '\0';
	} else {
		int i;
		if ( sign ){
			 res = new char[digits->size() + 1];
		 	i = 0;
		} else {
			res = new char[digits->size() + 2];
			res[0] = '-';
			i = 1;
		}
		list<type>::iterator it;
		for ( it = digits->begin() ; it != digits->end() ; ++it, ++i ){
			res[i] = (*it) + '0';
		}
		res[i] = '\0';
	}
	return res;
}

void BigInteger::display(){
	if ( digits->size() == 0 ){
		cout << '0';
	} else {
		if ( !sign ){
			cout << '-';
		}
		list<type>::iterator it = digits->begin();
		while ( it != digits->end() ){
			cout << (*it);
			++it;
		}
	}
}
