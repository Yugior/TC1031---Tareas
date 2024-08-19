#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones {
public:
    // Suma iterativa de los números de 1 a n
    long sumaIterativa(int n) {
        long resultado = 0; 
        for (int i = 1; i <= n; i++) {
            resultado += i;
        }
        return resultado;
    }

    // Suma recursiva de los números de 1 a n
    long sumaRecursiva(int n) {
        if (n == 0) {
            return 0;
        } else {
            return n + sumaRecursiva(n - 1);
        }
    }

    // Suma directa de los números de 1 a n utilizando la fórmula de Gauss
    long sumaDirecta(int n) {
        return n * (n + 1) / 2;
    }
};

#endif // FUNCIONES_H_
