// Horacio Villela Hernámdez A01712206
// Fecha: 28/10/2024
#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

template <class T>
class Heap {
private:
    std::vector<T> data; // Almacenamiento de datos del heap.
    unsigned int count; 

    
    void heapifyDown(int index); // Reorganiza el heap hacia abajo. Complejidad: O(log n)
    void heapifyUp(int index);   // Reorganiza el heap hacia arriba. Complejidad: O(log n)

public:
    Heap(int capacity);


    void push(T value);         // Inserta un valor en el heap. Complejidad: O(log n)
    void pop();                 // Elimina el elemento en la raíz. Complejidad: O(log n)
    T top() const;              // Devuelve el elemento en la raíz sin eliminarlo. Complejidad: O(1)
    bool empty() const;         // Verifica si el heap está vacío. Complejidad: O(1)
    unsigned int size() const;  // Devuelve el tamaño del heap. Complejidad: O(1)
    std::string toString() const; // Devuelve el heap como una cadena. Complejidad: O(n)
};

// Constructor del heap
template <class T>
Heap<T>::Heap(int capacity) : count(0) {
    data.reserve(capacity); 
}

// Inserta un valor en el heap.
template <class T>
void Heap<T>::push(T value) {
    data.push_back(value); // Agrega el nuevo valor al final del vector.
    count++;               
    heapifyUp(count - 1);   // Ajusta el heap hacia arriba. Complejidad: O(log n)
}

// Elimina el elemento en la raíz del heap.
template <class T>
void Heap<T>::pop() {
    if (empty()) throw std::out_of_range("Heap is empty"); 
    data[0] = data[count - 1]; // Reemplaza la raíz con el último elemento.
    data.pop_back();           // Elimina el último elemento.
    count--;                  
    heapifyDown(0);            // Ajusta el heap hacia abajo. Complejidad: O(log n)
}

// Devuelve el elemento en la raíz del heap sin eliminarlo.
template <class T>
T Heap<T>::top() const {
    if (empty()) throw std::out_of_range("Heap is empty"); 
    return data[0]; // Retorna el primer elemento (mínimo dado en el min-heap). Complejidad: O(1)
}

// Verifica si el heap está vacío.
template <class T>
bool Heap<T>::empty() const {
    return count == 0; // Retorna true si es 0, false en otro contrario. Complejidad: O(1)
}

// Devuelve el tamaño actual del heap.
template <class T>
unsigned int Heap<T>::size() const {
    return count; // Retorna la cantidad de elementos en el heap. Complejidad: O(1)
}

// Convierte el heap en una cadena de texto para su impresión.
template <class T>
std::string Heap<T>::toString() const {
    std::stringstream aux;
    aux << "[";
    for (unsigned int i = 0; i < count; i++) {
        if (i != 0) {
            aux << " ";
        }
        aux << data[i];
    }
    aux << "]";
    return aux.str(); // Complejidad: O(n), ya que recorre todos los elementos del heap.
}

// Reorganiza el heap hacia abajo desde el índice dado para mantener la propiedad del min-heap.
template <class T>
void Heap<T>::heapifyDown(int index) {
    int left = 2 * index + 1;    // Índice hijo izquierdo.
    int right = 2 * index + 2;   // Índice hijo derecho.
    int smallest = index;        // Asume índice actual como menor.

    // Encuentra el menor entre el nodo y sus hijos.
    if (left < count && data[left] < data[smallest]) {
        smallest = left;
    }
    if (right < count && data[right] < data[smallest]) {
        smallest = right;
    }
    // Si el menor no es el nodo actual,sigue ajustando.
    if (smallest != index) {
        std::swap(data[index], data[smallest]);
        heapifyDown(smallest); // Llamada recursiva para ajustar más abajo. Complejidad: O(log n)
    }
}

// Reorganiza el heap hacia arriba desde el índice dado para mantener la propiedad del min-heap.
template <class T>
void Heap<T>::heapifyUp(int index) {
    int parent = (index - 1) / 2; // Calcula el índice del padre.
    // Si el elemento actual es menor que su padre, los intercambia.
    if (index && data[parent] > data[index]) {
        std::swap(data[index], data[parent]);
        heapifyUp(parent); // Llamada recursiva para ajustar más arriba. Complejidad: O(log n)
    }
}

#endif /* HEAP_H_ */
