/*
 * Autor: Carlos Ramírez
 * Fecha de creación: 30 de Octubre
 * Fecha última modificación: 30 de Octubre
 * Versión: 1.0
 * 
 * Archivo encabezado libreria TAD Lista
 * Representación Estructuras Encadenadas Simples
 */

/*
He añadido de base la operacion 'display', que imprime la lista. Esto para facilitar la visualizacion de la lisa.
*/

#ifndef __LISTA_H
#define __LISTA_H

#include <iostream>

using namespace std;

/************************
* ESTRUCTURAS DE DATOS *
************************/
typedef int Elemento;

class Nodo{
   public:
     Elemento dato;
     Nodo* sig;
};

class Lista{
  private:
    Nodo* act;

  public:
    /************************
    * OPERACIONES DEL TAD *
    ************************/

    /* Constructoras */
    Lista();

    /* Modificadoras */
    void elimLista(int pos);
    void insListaOrdenada(Elemento elem);

    /* Analizadoras */
    Elemento infoLista(int pos);
    int longLista();
    bool vaciaLista();
    void display();
};

#endif
