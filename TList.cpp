//
// Created by usuario on 10/6/20.
//

#include "TList.h"

/**
 * Metodo constructor de la lista
 */
TList::TList()
{
    first = nullptr;
    largo=0;
}
/**
 * Metodo que retorna el primer nodo de la lista
 * @return Primer nodo de la lista
 */
TNode* TList::getFirst()
{
    return this->first;
}
/**
 * Metodo que devuelve el nodo que contenga el valor dado
 * @param val Valor a buscar
 * @return Nodo que contiene el valor
 */
TNode* TList::getNodoVal(string val) {
    TNode *present = this->first;
    while (present != nullptr) {
        if(present->getValue() == val)
            return present;
        else{
            present = present->next;
        }
    }
    return nullptr;
}
/**
 * Funcion para obtener el pos-esimo nodo de la lista
 * @param pos Posicion a buscar
 * @return Nodo de la lista
 */
TNode* TList::getNodoPos(int pos) {
    TNode *present = this->first;
    int i=0;
    while (i != pos){
        present = present->next;
        i+=1;
    }
    return present;
}
/**
 * Funcion para obtener el indicie del nodo que contiene cierto valor
 * @param value Valor a buscar en la TList
 * @return Retorna un entero con la posicion del nodo buscado
 */
int TList::getPos(string value) {
    TNode *present = this->first;
    int i = 0;
    while (present != nullptr) {
        if(present->getValue() == value)
            return i;
        else{
            present = present->next;
            i+=1;
        }
    }
    return -1;
}
/**
 * Funcion para agregar un dato a la lista
 * @param data Dato a agregar
 */
void TList::addLast(string data)
{
    if(this->first == nullptr){
        this->first = new TNode(data);
        largo +=1;
    }
    else{
        TNode *present =  this->first;
        while(present->next != nullptr){
            present = present->next;
        }
        present->next = new TNode(data);
        largo +=1;
    }
}
/**
 * Funcion para eliminar una posicion de la lista
 * @param pos Posicion a eliminar
 */
void TList::deletePos(int pos) {
    TNode *temp1 = this->first;
    TNode *temp2 = this->first->next;
    if(pos == 0){
        this->first = temp1->next;
        largo -=1;
    }
    else{
        int  i = 0;
        while (i != pos-1){
            temp1 = temp1->next;
            temp2 = temp2->next;
            i+=1;
        }
        TNode *aux = temp2;
        if(pos<largo) {
            temp1->next = temp2->next;
        }else{
            temp1->next= nullptr;
        }

        delete aux;
        largo -=1;
    }
}
/**
 * Metodo para obtener string de la lista
 * @return String con toda la info de la lista
 */
string TList::printList()
{
    TNode *present = this->first;
    string values;
    while (present != nullptr) {
        values+=present->getValue()+";";
        present = present->next;
    }
    return values;
}