"""
Oscar Vargas Pabon
Tarea 1
Estructura de datos 
8975574
"""

#######punto 1 ##############

"""
- Nombre: verificarDiagonales.
- Entrada: Una matriz
- Salida: un valor booleano que es True si cumple la condicion de que 
			ambas diagonales (que comienzan desde mat[0][0] y mat[0][-1]) son iguales, False en el caso opuesto.
"""

def verificarDiagonales(mat):
	ans = True
	i, j = 0, len(mat[0])-1
	while ans and i < len(mat):
		if mat[i][i] != mat[i][j]: 
			ans = False
		i += 1
		j -= 1
	return ans


########################## punto 2 ####################################

"""
- Nombre: esCapicua
- Entrada: una lista compuesta por numeros enteros
- Salida: Un valor booleano que toma True cuando la lista tiene los mismos valores cuando es leida de izquierda a
			derecha que cuando es leida de derecha a izquierda. De lo contrario toma False.
"""


def esCapicua(l):
	ans = True
	i, j = 0, len(l)-1
	while ans and i < (len(l)//2):
		if l[i] != l[j]: ans = False
		i += 1
		j -= 1
	return ans



####################### punto 3 ##################################


#### a)

"""
-Nombre: diferenciaListas
-Entrada: 2 listas. La primera es la lista a la que se le va a restar la segunda
-Salida: 1 lista. Es el resultado de quitarle a la primera lista de la entrada, los elementos que 
		comparte con la segunda lista de la entrada.
"""


def diferenciaListas(listaRestada, listaRestadora):
	ans = []
	for elemento in listaRestada:
		if not elemento in listaRestadora:
			ans.append(elemento)
		else:
			listaRestadora.remove(elemento)
	return ans

############# b)

"""
-Nombre: leerImprimir
-Entrada: No toma ninguna variable. Toma mediante input() la informacion referente a 
			numero de casos y los elementos de las listas.
-Salida: No retorna ningun valor. La salida es entonces el print que realiza de la lista que retorna la operacion
			diferenciaListas.
"""

def leerImprimir():
	n = int(input())
	for x in range(n):
		listaRestada = input().split(" ")
		listaRestadora = input().split(" ")
		respuesta = diferenciaListas(listaRestada[1:], listaRestadora[1:])
		print(", ".join(respuesta))


####################### punto 4 ####################################



#################################################################################################################
################ AUN BAJO REPARACIONES  ---------  NO OLVIDAR ESTO .-.,--MÑLJ.M+´PO43209751MC#########################
#################################################################################################################



"""
-Nombre: sumaDigitos
-Entrada: numero tipo int
-Salida: numero tipo int que es resultado de la suma de los digitos del de la entrada
"""

def sumaDigitos(n):
    n = str(n)
    suma = 0
    for digito in n:
        suma += int(digito)
    return suma

"""
-Nombre: mostrarPrimos
-Entrada: un numero entero que delimita el intervalo en el que se hallaran los primos de la manera [0, n]
-Salida: no retorna nada. La salida serian los numeros primos en el intervalo [0,n] con el formato especificado.
"""

def mostrarPrimos(n):
    primos = [2]
    primoEnDigitos = ["2"]

    print("Numeros primos entre 1 y %d" % (n))
    if n >= 2:
    	print("--> 2", end = "")
    
    for i in range(3, n, 2):
        primalidad = True
        j = 0 
        while primalidad and j < len(primos):
            if i%primos[j] == 0:
                primalidad = False
            else:
                j += 1
        if primalidad:
            primos.append(i)
            print(",\n--> %d" % (i), end ="")
            if sumaDigitos(i) in primos:
                primoEnDigitos.append(str(i))
    print("\n\nNumeros entre 1 y %d con suma de digitos con valor primo" % (n))
    if n >= 2:
    	print(", ".join(primoEnDigitos))

######################## punto 5 ###################################

"""
-Nombre: sumarValoresMatriz()
-Entrada: matDis: la matriz dispersa que contiene los datos a sumar. pos: una lista que contiene tuplas
			que representan las posciciones a sumar de matDis. 
			pos = [(#fila1, #columna1),(#fila2, #columna2),...,(#filan, #columnan)]
-Salida: un numero entero que representa la suma de los valores de matDis que se encontraban en las
			posciciones referidas por pos.
"""

def sumarValoresMatriz(matDis, pos):
	ans = 0
	for coord in pos:
		if coord[0] in matDis:
			i, flag = 0, True
			while i < len(matDis[coord[0]]) and flag:
				if matDis[coord[0]][i][0] == coord[1]:
					ans += matDis[coord[0]][i][1]
					flag = False
				else:
					i += 1

	return ans

