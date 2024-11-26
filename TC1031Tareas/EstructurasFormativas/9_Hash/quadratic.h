//Horacio Villela Hernandez A01712206


#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template <typename KeyType, typename ValueType>
class Quadratic {
private:
    std::vector<std::pair<KeyType, ValueType>> table;  // Tabla de almacenamiento
    std::vector<bool> occupied;  
    size_t table_size;  // Tamaño de la tabla
    KeyType empty_value; 
    unsigned int (*hash_function)(KeyType);  // Función de hash que toma una copia de la clave

    // Calcula el siguiente índice para la posición de inserción
    // Complejidad: O(1) por su cálculo directo de la fórmula 
    int quadraticProbe(int hash, int i) {
        return (hash + i * i) % table_size;
    }

public:
    // Constructor 
    // Complejidad: O(n) 
    Quadratic(size_t size, KeyType empty_val, unsigned int (*hash_fn)(KeyType))
        : table_size(size), empty_value(empty_val), hash_function(hash_fn) {
        table.resize(table_size);          
        occupied.resize(table_size, false);
    }

    // Método para insertar un elemento 
    // Complejidad O(1) cuando no hay colisiones,podría llegar a O(n) si se requieren muchas colisiones.
    void put(const KeyType& key, const ValueType& value) {
        int hash = hash_function(key) % table_size;  // O(1), cálculo de hash
        int i = 0;  // Contador 

        //  Encontrar un espacio libre
        // En el peor caso, complejidad de O(n).
        while (occupied[hash] && table[hash].first != key) { 
            i++;  
            hash = quadraticProbe(hash, i);  
        }

        // Inserta el par clave-valor en la posición encontrada
        table[hash] = std::make_pair(key, value);  // O(1)
        occupied[hash] = true;                     // O(1)
    }

    // Método para obtener el valor asociado a una clave
    // Complejidad O(1),  el peor caso podría ser O(n) debido a si hay muchas colisiones.
    ValueType get(const KeyType& key) {
        int hash = hash_function(key) % table_size;  
        int i = 0;  

        // Sondeo cuadrático para encontrar la clave
        // Peor caso, la complejidad de este bucle es O(n).
        while (occupied[hash]) {
            if (table[hash].first == key) {  
                return table[hash].second;  
            }
            i++;  // Incrementa el índice de sondeo
            hash = quadraticProbe(hash, i); 
        }

        // Si no se encuentra la clave, lanzamos una excepción
        throw std::out_of_range("Key not found");
    }

    // Método para devolver una representación en string de la tabla
    // Complejidad: O(n), ya que recorre todo el arreglo de la tabla.
    std::string toString() const {
        std::ostringstream oss;
        for (int i = 0; i < table_size; i++) {  // O(n) por recorrer toda la tabla
            if (occupied[i]) {  // O(1) por verificar si la posición está ocupada
                oss << "(" << i << " " << table[i].first << " : " << table[i].second << ") ";  // O(1) para agregar el par al string
            }
        }
        return oss.str(); 
    }
};

#endif // QUADRATIC_H
