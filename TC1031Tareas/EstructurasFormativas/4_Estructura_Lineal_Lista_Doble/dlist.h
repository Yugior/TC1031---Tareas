// dlist.h
//Horacio Villela Hernandez A01712206

#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <sstream>
#include <string>

template <class T>
class DList {
private:
    // Estructura del nodo
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // Constructor
    DList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor para liberar memoria
    ~DList() {
        Node* current = head;
        Node* nextNode;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Inserción de un elemento al final de la lista
    // Complejidad: O(1)
    void insertion(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    // Convertir la lista a string en dirección adelante
    // Complejidad: O(n)
    std::string toStringForward() const {
        std::stringstream ss;
        ss << "[";
        Node* current = head;
        while (current != nullptr) {
            ss << current->data;
            if (current->next != nullptr) {
                ss << ", ";
            }
            current = current->next;
        }
        ss << "]";
        return ss.str();
    }

    // Convertir la lista a string en dirección atrás
    // Complejidad: O(n)
    std::string toStringBackward() const {
        std::stringstream ss;
        ss << "[";
        Node* current = tail;
        while (current != nullptr) {
            ss << current->data;
            if (current->prev != nullptr) {
                ss << ", ";
            }
            current = current->prev;
        }
        ss << "]";
        return ss.str();
    }

    // Buscar un elemento en la lista y devolver el índice, o -1 si no se encuentra
    // Complejidad: O(n)
    int search(T value) const {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1; // Si no se encuentra el valor
    }

    // Actualizar el valor en un índice específico
    // Complejidad: O(n)
    void update(int index, T value) {
        if (index < 0 || index >= size) return; // Índice fuera de rango
        Node* current = head;
        int i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            i++;
        }
        if (current != nullptr) {
            current->data = value;
        }
    }

    // Eliminar el nodo en un índice específico
    // Complejidad: O(n)
    void deleteAt(int index) {
        if (index < 0 || index >= size) return; // Índice fuera de rango
        Node* current = head;
        int i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            i++;
        }

        if (current == nullptr) return;

        // Si el nodo es la cabeza
        if (current == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        }
        // Si el nodo es la cola
        else if (current == tail) {
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        }
        // Si el nodo está en medio
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        size--;
    }
};

#endif // DLIST_H
