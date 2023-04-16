#include "lista.h"

Lista::Lista(){
  act = NULL;
}

void Lista::insListaOrdenada(Elemento elem){
  Nodo *nuevo;
  nuevo = new Nodo;
  nuevo->dato = elem;
  if (act == NULL){
    nuevo->sig = NULL;
    act = nuevo;
  } else if ( act->dato >= elem ){
    nuevo->sig = act;
    act = nuevo;
  } else {
    Nodo  *tmp;
    tmp = act;
    while ( tmp->sig != NULL && (tmp->sig)->dato <= elem ){
      tmp = tmp->sig;
    }
    nuevo->sig = tmp->sig;
    tmp->sig = nuevo;
  }
}

void Lista::elimLista(int pos){
  Nodo *tmp, *elim;
  if(pos >= 1 && pos <= longLista()){
    if(pos == 1)
      act = act->sig;
    else{
      tmp = act;
      for(int i = 0; i < pos-2; i++)
	tmp = tmp->sig;
      elim = tmp->sig;
      tmp->sig = tmp->sig->sig;
      delete elim;
    }
  }
}

Elemento Lista::infoLista(int pos){
  Nodo* tmp = act;

  for(int i = 1; i < pos; i++)
    tmp = tmp->sig;

  return tmp->dato;
}

int Lista::longLista(){
  Nodo* tmp = act;
  int cont = 0;

  while(tmp != NULL){
    tmp = tmp->sig;
    cont++;
  }

  return cont;
}

bool Lista::vaciaLista(){
  return act == NULL;
}

void Lista::display(){
  Nodo* tmp = act;
  cout << "[Head] ";
  while ( tmp != NULL ){
    cout << tmp->dato << " ";
    tmp = tmp->sig;
  }
  cout << "[Tail]" << endl;
}
