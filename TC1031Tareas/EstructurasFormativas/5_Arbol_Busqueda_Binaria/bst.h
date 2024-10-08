#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Clase Nodo
template <class T>
class Node {
public:
    T value;
    Node* left;
    Node* right;

    Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

// Clase BST (Binary Search Tree)
template <class T>
class BST {
private:
    Node<T>* root;

    // Agrega un nodo al árbol.
    // Complejidad: 
    // - Mejor caso (árbol balanceado): O(log n)
    // - Peor caso (árbol desbalanceado): O(n)
    void add(Node<T>*& node, T val) {
        if (node == nullptr) {
            node = new Node<T>(val);
        } else if (val < node->value) {
            add(node->left, val);
        } else if (val > node->value) {
            add(node->right, val);
        }
    }

    // Recorrido preorden
    // Complejidad: O(n)
    void preOrder(Node<T>* node, stringstream& ss) const {
        if (node != nullptr) {
            ss << node->value << " ";
            preOrder(node->left, ss);
            preOrder(node->right, ss);
        }
    }

    // Recorrido inorden
    // Complejidad: O(n)
    void inOrder(Node<T>* node, stringstream& ss) const {
        if (node != nullptr) {
            inOrder(node->left, ss);
            ss << node->value << " ";
            inOrder(node->right, ss);
        }
    }

    // Recorrido postorden
    // Complejidad: O(n)
    void postOrder(Node<T>* node, stringstream& ss) const {
        if (node != nullptr) {
            postOrder(node->left, ss);
            postOrder(node->right, ss);
            ss << node->value << " ";
        }
    }

    // Calcula la altura del árbol
    // Complejidad: O(n), ya que se visitan todos los nodos para calcular la altura
    int height(Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    // Encuentra los ancestros de un nodo dado
    // Complejidad: O(n), ya que se debe buscar el nodo y recorrer los ancestros
    bool findAncestors(Node<T>* node, T val, vector<T>& ancestors) const {
        if (node == nullptr) {
            return false;
        }
        if (node->value == val) {
            return true;
        }
        ancestors.push_back(node->value);
        if (findAncestors(node->left, val, ancestors) || findAncestors(node->right, val, ancestors)) {
            return true;
        }
        ancestors.pop_back();
        return false;
    }

    // Encuentra el nivel de un nodo en el árbol
    // Complejidad: O(n), ya que debe recorrer el árbol hasta encontrar el nodo
    int findLevel(Node<T>* node, T val, int level) const {
        if (node == nullptr) {
            return -1;
        }
        if (node->value == val) {
            return level;
        }
        int leftLevel = findLevel(node->left, val, level + 1);
        if (leftLevel != -1) {
            return leftLevel;
        }
        return findLevel(node->right, val, level + 1);
    }

public:
    // Constructor
    BST() : root(nullptr) {}

    // Función para agregar un nodo
    // Complejidad: 
    // - Mejor caso: O(log n)
    // - Peor caso: O(n)
    void add(T val) {
        add(root, val);
    }

    // Función para recorrer el árbol en los 3 órdenes (preorden, inorden, postorden)
    // Complejidad: O(n), ya que se visitan todos los nodos una vez
    string visit() const {
        stringstream ss;
        ss << "[";
        preOrder(root, ss);
        ss.seekp(-1, ss.cur);  // Eliminar el último espacio
        ss << "]\n[";

        inOrder(root, ss);
        ss.seekp(-1, ss.cur);  // Eliminar el último espacio
        ss << "]\n[";

        postOrder(root, ss);
        ss.seekp(-1, ss.cur);  // Eliminar el último espacio
        ss << "]";

        return ss.str();
    }

    // Función para obtener la altura del árbol
    // Complejidad: O(n), ya que se recorre todo el árbol
    int height() const {
        return height(root);
    }

    // Función para obtener los ancestros de un valor dado
    // Complejidad: O(n), ya que se busca el nodo en el árbol
    string ancestors(T val) const {
        vector<T> ancestorList;
        stringstream ss;
        if (findAncestors(root, val, ancestorList)) {
            ss << "[";
            for (size_t i = 0; i < ancestorList.size(); ++i) {
                ss << ancestorList[i];
                if (i != ancestorList.size() - 1) {
                    ss << " ";
                }
            }
            ss << "]";
        } else {
            ss << "[]";
        }
        return ss.str();
    }

    // Función para encontrar el nivel de un nodo dado
    // Complejidad: O(n), ya que debe recorrer el árbol para encontrar el nodo
    int whatlevelamI(T val) const {
        return findLevel(root, val, 1);
    }
};

#endif // BST_H
