#ifndef SORTS_H_
#define SORTS_H_


#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
	
public:
	std::vector<T> ordenaBurbuja( std::vector<T>&);
	std::vector<T> ordenaSeleccion( std::vector<T>&);
	std::vector<T> ordenaMerge( std::vector<T>&);
	int busqSecuencial(const std::vector<T>&, T);
	int busqBinaria(const std::vector<T>&, T);
	int bs_aux(const std::vector<T>&, int, int, T);

};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}


//Peor caso O(n^2)
template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja( std::vector<T> &v) {
	

	for (int i = v.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j] > v[j + 1]) {
				swap(v, j, j + 1);
			}
		}
	}
	return v;
}

//Peor caso O(n^2)

template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion( std::vector<T>& v) {
    
    	int p;
    	
    	for (int i = 0; i < v.size() - 1; i++) {  
        p = i;  
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[p]) {  
                p = j;
            }
        }
        if (p != i) { 
            swap(v, p, i);
        }
    }

    return v;
}

//Peor caso O(n) donde n es el num de elementos copiados
template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
   
     for (int i = low; i <= high;i++){
        A[i] = B[i];
    }
    
}

//Peor caso O(n) donde n es el num de elementos combinados
template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
    int i, j, k;
    
    i = low;
    j = mid + 1;
    k= low;
    
    while ( i <= mid && j <= high){
        if (A[i]< A[j]){
            B[k] = A[i];
            i++;
        }
        else {
            B[k] = A[j];
            j++;
        }
        k++;
        
    }
    
    if (i > mid){
        for(; j<= high; j++) {
            B[k++] = A[j];
        }
    }
    else {
        for(;i <= mid;i++){
            B[k++] = A[i];
        }
    }
}
    
   
//Peor caso O(n log n) 
template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
    int mid;
    
    if ( (high - low) < 1){
        return;
    }
    
    mid = (high + low) / 2;
    mergeSplit(A,B,low,mid);
    mergeSplit(A,B,mid + 1,high);
    mergeArray(A,B,low,mid,high);
    copyArray(A,B,low,high);
    
}

//Peor caso O(n log n)

template <class T>
std::vector<T> Sorts<T>::ordenaMerge( std::vector<T> &v) {
	std::vector<T> tmp(v.size());
	
	mergeSplit(v, tmp, 0, v.size() - 1);
	return v;
	
	


}

//Peor caso O(n)

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T>& v, T val) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == val) {
            return i;
        }
    }
    return -1;
}





// Peor O(log n)
template <class T>
int Sorts<T>::bs_aux(const std::vector<T>& v, int low, int high, T val) {
    if (low <= high) {
        int mid = (low + high) / 2;
        if (val == v[mid]) {
            return mid;  // Valor encontrado
        } else if (v[mid] > val) {
            return bs_aux(v, low, mid - 1, val);  // Buscar en la mitad izquierda
        } else {
            return bs_aux(v, mid + 1, high, val);  // Buscar en la mitad derecha
        }
    }
    return -1;  
}

//Peor caso O(log n)

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T>& v, T val) {
    int size = v.size();
    return bs_aux(v, 0, size - 1, val);
}

#endif /* SORTS_H_ */
