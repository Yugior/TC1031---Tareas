//Horacio Villela Hernández
//A01712206

#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <string>
#include <sstream>

template <class T>
class SplayTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Métodos privados para las operaciones internas
    Node* rightRotate(Node* x); // Rotación a la derecha
    Node* leftRotate(Node* x);  // Rotación a la izquierda
    Node* splay(Node* root, T key); // Splay para traer el nodo con `key` a la raíz
    Node* add(Node* root, T key); // Inserta un nodo y hace splay
    Node* remove(Node* root, T key); // Elimina un nodo y hace splay
    void inorder(Node* node, std::stringstream& out) const; // Recorrido en inorden
    void preorder(Node* node, std::stringstream& out) const; // Recorrido en preorden

public:
    SplayTree();
    void add(T key); // Inserta un elemento en el árbol
    bool find(T key); // Busca y splaye el elemento
    void remove(T key); // Elimina un elemento
    std::string inorder() const; // Obtiene recorrido en inorden
    std::string preorder() const; // Obtiene recorrido en preorden
};

// Constructor: Inicializa el árbol vacío
// Complejidad: O(1)
template <class T>
SplayTree<T>::SplayTree() : root(nullptr) {}

// Rotación a la derecha
// Complejidad: O(1)
template <class T>
typename SplayTree<T>::Node* SplayTree<T>::rightRotate(Node* x) {
    Node* y = x->left;
    if (!y) return x; // Si no hay hijo izquierdo, no rota
    x->left = y->right;
    y->right = x;
    return y;
}

// Rotación a la izquierda
// Complejidad: O(1)
template <class T>
typename SplayTree<T>::Node* SplayTree<T>::leftRotate(Node* x) {
    Node* y = x->right;
    if (!y) return x; // Si no hay hijo derecho, no rota
    x->right = y->left;
    y->left = x;
    return y;
}

// Función splay: Lleva el nodo con `key` a la raíz del árbol
// Complejidad: O(log n) en promedio, O(n) en el peor caso
template <class T>
typename SplayTree<T>::Node* SplayTree<T>::splay(Node* root, T key) {
    if (!root || root->data == key)
        return root; // Si el árbol está vacío o ya está en la raíz, no hace nada

    // Caso: El nodo a splayear está en el subárbol izquierdo
    if (key < root->data) {
        if (!root->left) return root; // Si no hay subárbol izquierdo, no rota

        // Zig-Zig (left-left): Rotación doble hacia la derecha
        if (key < root->left->data) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (left-right): Rotación izquierda y luego derecha
        else if (key > root->left->data) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = leftRotate(root->left);
        }
        return root->left ? rightRotate(root) : root;

    } else { // El nodo a splayear está en el subárbol derecho
        if (!root->right) return root; // Si no hay subárbol derecho, no rota

        // Zag-Zag (right-right): Rotación doble hacia la izquierda
        if (key > root->right->data) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        // Zag-Zig (right-left): Rotación derecha y luego izquierda
        else if (key < root->right->data) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rightRotate(root->right);
        }
        return root->right ? leftRotate(root) : root;
    }
}

// Inserta un elemento y lo lleva a la raíz
// Complejidad: O(log n) en promedio
template <class T>
void SplayTree<T>::add(T key) {
    root = add(root, key);
}

// Función auxiliar de inserción con splay
// Complejidad: O(log n) en promedio
template <class T>
typename SplayTree<T>::Node* SplayTree<T>::add(Node* root, T key) {
    if (!root) return new Node(key); // Inserta el nuevo nodo si el árbol está vacío

    root = splay(root, key); // Realiza splay en el nodo buscado
    if (root->data == key) return root; // Si el nodo ya existe, no hace nada

    Node* newNode = new Node(key); // Crea el nuevo nodo

    // Inserta el nuevo nodo como raíz y ajusta los subárboles
    if (key < root->data) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    return newNode;
}

// Busca un elemento y lo lleva a la raíz
// Complejidad: O(log n) en promedio
template <class T>
bool SplayTree<T>::find(T key) {
    root = splay(root, key);
    return root && root->data == key;
}

// Elimina un elemento y reorganiza el árbol
// Complejidad: O(log n) en promedio
template <class T>
void SplayTree<T>::remove(T key) {
    root = remove(root, key);
}

// Función auxiliar de eliminación con splay
// Complejidad: O(log n) en promedio
template <class T>
typename SplayTree<T>::Node* SplayTree<T>::remove(Node* root, T key) {
    if (!root) return nullptr;

    root = splay(root, key); // Lleva el nodo a eliminar a la raíz
    if (root->data != key) return root; // Si no encuentra el nodo, no hace nada

    Node* temp;
    // Reorganiza el árbol después de eliminar el nodo
    if (!root->left) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key); // Splay en el subárbol izquierdo
        root->right = temp->right;
    }
    delete temp; // Libera el nodo eliminado
    return root;
}

// Obtiene el recorrido en inorden como una cadena
// Complejidad: O(n)
template <class T>
std::string SplayTree<T>::inorder() const {
    std::stringstream out;
    out << "[";
    inorder(root, out);
    std::string result = out.str();
    if (result.size() > 1) {
        result.pop_back(); // Elimina el último espacio extra
    }
    result += "]";
    return result;
}

// Función auxiliar para el recorrido en inorden
// Complejidad: O(n)
template <class T>
void SplayTree<T>::inorder(Node* node, std::stringstream& out) const {
    if (!node) return;
    inorder(node->left, out);
    out << node->data << " ";
    inorder(node->right, out);
}

// Obtiene el recorrido en preorden como una cadena (de raíz a derecha)
// Complejidad: O(n)
template <class T>
std::string SplayTree<T>::preorder() const {
    std::stringstream out;
    out << "[";
    preorder(root, out);
    std::string result = out.str();
    if (result.size() > 1) {
        result.pop_back(); // Elimina el último espacio extra
    }
    result += "]";
    return result;
}

// Función auxiliar para el recorrido en preorden (modificada para recorrido raíz-derecha)
// Complejidad: O(n)
template <class T>
void SplayTree<T>::preorder(Node* node, std::stringstream& out) const {
    if (!node) return;
    out << node->data << " ";   // Visita la raíz
    preorder(node->right, out); // Recorre el subárbol derecho primero
    preorder(node->left, out);  // Recorre el subárbol izquierdo después
}


#endif // SPLAY_H
