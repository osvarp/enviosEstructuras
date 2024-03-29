#include "lista.h"

Lista::Lista(){
  act = NULL;
}

void Lista::anxLista(Elemento elem){
  Nodo* tmp;
  Nodo* nuevo = new Nodo;
  nuevo->dato = elem;
  nuevo->sig = NULL;

  if(act == NULL)
    act = nuevo;
  else{
    tmp = act;
    while(tmp->sig != NULL)
      tmp = tmp->sig;
    tmp->sig = nuevo;
  }
}

void Lista::insLista(Elemento elem, int pos){
  Nodo *nuevo, *tmp;
  nuevo = new Nodo;
  nuevo->dato = elem;
  nuevo->sig = NULL;

  if(pos >= 1 && pos <= longLista()){
    if(pos == 1){
      nuevo->sig = act;
      act = nuevo;
    }
    else{
      tmp = act;
      for(int i = 0; i < pos - 2; i++)
	tmp = tmp->sig;
      nuevo->sig = tmp->sig;
      tmp->sig = nuevo;
    }
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

Lista Lista::operator + (Lista l){
  Lista res = Lista();
  if (act != NULL || l.act != NULL){
    Nodo *it = act, *last = NULL, *tmp;
    int j = 0;
    while( j <= 1 ){
      if ( it == NULL ){
        ++j;
        it = l.act;
      } else {
        tmp = new Nodo;
        tmp->dato = it->dato;
        tmp->sig = NULL;
        if ( last == NULL ){
          res.act = tmp;
          last = tmp;
          it = it->sig;
        } else {
          last->sig = tmp;
          last = tmp;
          it = it->sig;
        }
      }
    }
  }
  return res;
}  

