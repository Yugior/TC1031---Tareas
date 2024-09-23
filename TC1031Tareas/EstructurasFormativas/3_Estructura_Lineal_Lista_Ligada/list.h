//Horacio Villela Hernandez
//A01712206


#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>
#include <string>

template <class T>
class Link {
public:
    T value;
    Link* next;

    Link(T val) : value(val), next(nullptr) {}
};

template <class T>
class List {
private:
    Link<T>* head;
    
public:
    List() : head(nullptr) {}
    ~List();

    void insertion(T value);
    int search(T value) const;
    void update(int index, T value);
    void deleteAt(int index);
    std::string toString() const;

};

template <class T>
List<T>::~List() {
    while (head) {
        Link<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

   // La complejidad O(n) debido a que se recorre toda la lista para eliminar cada nodo
template <class T>
void List<T>::insertion(T value) {
    Link<T>* newLink = new Link<T>(value);
    if (!head) {
        head = newLink;
    } else {
        Link<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newLink;
    }
}

// La complejidad es O(n)  pues en el peor caso se deberia recorrer toda la lista para insertar al final
template <class T>
int List<T>::search(T value) const {
    Link<T>* temp = head;
    int index = 0;
    while (temp) {
        if (temp->value == value) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1; // Not found
}

// La complejidad es O(n) - debido a que en el peor caso se recorre toda la lista hasta encontrar el valor o determinar que no está presente
template <class T>
void List<T>::update(int index, T value) {
    Link<T>* temp = head;
    int currentIndex = 0;
    while (temp) {
        if (currentIndex == index) {
            temp->value = value;
            return;
        }
        temp = temp->next;
        currentIndex++;
    }
}


  //La complejidad es O(n) debido a que recorre toda la lista para llegar al índice especificado           
template <class T>
void List<T>::deleteAt(int index) {
    if (index < 0 || !head) return;

    Link<T>* temp = head;
    if (index == 0) {
        head = head->next;
        delete temp;
        return;
    }

    for (int i = 0; temp && i < index - 1; i++) {
        temp = temp->next;
    }

    if (!temp || !temp->next) return;

    Link<T>* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
}

template <class T>
std::string List<T>::toString() const {
    std::stringstream aux;
    Link<T>* p = head;
    aux << "[";
    while (p != nullptr) {
        aux << p->value;
        if (p->next != nullptr) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

#endif // LIST_H
