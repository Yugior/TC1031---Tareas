/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "exception.h"
#include <iostream>

//Test 1
// O(n) lienal

long sum_seq(int n) {
    long resultado ;
    for (int i = 0;i <= n; i++){
        resultado += i;
    }
	return resultado;
}

//Test 2
// O(n)
long sum_rec(int n) {
    long resultado;
    if (n == 0){
        return 0;
    } 
    else {
        return n + sum_rec(n -1);
    }
}

//Test 3
//O(n) lineal

long fact_seq(int n) {
    int resultado = 1;
    for (int i = 1;i <= n; i++){
        resultado *= i;
    }
	return resultado;
}

//Test 4
//O(n)
long fact_rec(int n) {
    int resultado = 1;
    if (n == 1) {
        return 1;
    }
    else {
        return n * fact_rec(n -1);;
    }
}

// Test 5
// O(2n) lineal

long fib_seq(int n) {
    long a, b, aux;
    int i;
    
    if (n==1||n == 2) {
        return 1;
    }
    
    a = 1;
    b = 1;
    i = 3;
    
    while (i <= n) {
        aux = a + b;
        a = b;
        b = aux;
        i++;
    }
    
    return b;
}

//Test 6
// O(2^n)
long fib_rec(int n) {
    if (n==1||n == 2) {
        return 1;
    }
    else {
        return (fib_rec(n - 1) + fib_rec(n - 2));
    }

}

//Test 7
// O( log n )

long gcd_seq(long a, long b) {
    long aux;
    
    while (b != 0) {
        aux = b;
        b = a % b;
        a = aux;
    }
	return a;
}

//Test 8
 //0( log n)
long gcd_rec(long a, long b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd_rec(b, a % b);
    }
}
//Test 9
// O(n) lineal 

bool find_seq(int arr[], int size, int val) {
	// ciclo for O(n)
	for (int i = 0; i < size; i++) {
		if (val == arr[i]) {
			return true;
		}
	}
	return false;
}

// funcion O log(n)
bool find_rec(int arr[], int low, int high, int val) {
	int mid;
	bool aux;

  // cada llamada recursiva parte por la mitad el arreglo, por lo que todos
	// los recorridos que se generen serán menores n, es decir, cada siguiente paso
	// toma solo la mitad de lo que queda en el arreglo.

	if ( ((high - low) + 1) == 1) {
		return (val == arr[low]);
	} else {
		aux = false;
		mid = (high + low) / 2;
		aux = find_rec(arr, low, mid, val);
		if (!aux) {
			aux = find_rec(arr, mid + 1, high, val);
		}
		return aux;
	}
}

//funcion O(n)
int max_seq(int arr[], int size) {
	int m = arr[0];
	// ciclo for O(n)
	for (int i = 1; i < size; i++) {
		if (m < arr[i]) {
			m = arr[i];
		}
	}
	return m;
}


// funcion O log(n)
int max_rec(int arr[], int low, int high) {
	int mid, left, right;

	  // cada llamada recursiva parte por la mitad el arreglo, por lo que todos
		// los recorridos que se generen serán menores n, es decir, cada siguiente paso
		// toma solo la mitad de lo que queda en el arreglo.

	if ( ((high - low) + 1) == 1) {
		return arr[low];
	} else {
		mid = (high + low) / 2;
		left = max_rec(arr, low, mid);
		right = max_rec(arr, mid + 1, high);
		return ( (left > right)? left : right );
	}
}
// O( log n) Logaritmic7}2n
int unimodal_seq(int arr[], int size) {
	if (size < 3) {
		return -1;
	}

	int mid;
	int low = 0;
	int high = size - 1;
	while (low < high) {
		mid = (high + low) / 2;
		if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) {
			return mid;
		} else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) {
			low = mid + 1;
		} else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) {
			high = mid - 1;
		}
	}
	return low;
}




// O (log n) 
int unimodal_rec(int arr[], int low, int high) {
	int mid;

	if (low <= high) {
		mid = (high + low) / 2;
		if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) {
			return mid;
		} else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) {
			return unimodal_rec(arr, mid + 1, high);
		} else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) {
			return unimodal_rec(arr, low, mid - 1);
		}
	}
	return -1;
}

int unimodal_rec(int arr[], int size) {

	if (size < 3) {
		return -1;
	}
	return unimodal_rec(arr, 0, size - 1);
}

int bs_seq(int arr[], int size, int val) {
	int mid;
	int low = 0;
	int high = size - 1;

	while (low < high) {
		mid = (high + low) / 2;
		if (val == arr[mid]) {
			return mid;
		} else if (val < arr[mid]) {
			high = mid - 1;
		} else if (val > arr[mid]) {
			low = mid + 1;
		}
	}
	return low;
}

int bs_aux(int arr[], int low, int high, int val) {
	int mid;

	if (low <= high) {
		mid = (high + low) / 2;
		if (val == arr[mid]) {
			return mid;
		} else if (val < arr[mid]) {
			return bs_aux(arr, low, mid - 1, val);
		} else if (val > arr[mid]) {
			return bs_aux(arr, mid + 1, high, val);
		}
	}
	return low;
}

int bs_rec(int arr[], int size, int val) {
	return bs_aux(arr, 0, size - 1, val);
}

#endif /* RECURSION_H_ */
