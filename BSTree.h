#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
    private:
        // Miembros privados
        int nelem;                // Número de elementos almacenados en el ABB
        BSNode<T>* root;          // Nodo raíz del ABB

        // Método recursivo para la búsqueda de elementos en el ABB
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                return nullptr; // Retornamos nullptr si no encontramos el elemento
            }
            if (e < n->elem) {
                return search(n->left, e); // Buscar en el subárbol izquierdo
            }
            if (e > n->elem) {
                return search(n->right, e); // Buscar en el subárbol derecho
            }
            return n; // Devolvemos el nodo encontrado
        }

        // Método recursivo para la inserción ordenada de elementos
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++; // Actualizamos el contador de nodos
                return new BSNode<T>(e); // Crear nuevo nodo
            }
            if (e == n->elem) {
                throw std::runtime_error("Elemento ya existente");
            }
            if (e < n->elem) {
                n->left = insert(n->left, e); // Insertar en el subárbol izquierdo
            } else {
                n->right = insert(n->right, e); // Insertar en el subárbol derecho
            }
            return n; // Retornamos el nodo modificado
        }

        // Recorrido INORDER
        void print_inorder(std::ostream& out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);   // Recorrer subárbol izquierdo
                out << n->elem << " ";         // Imprimir el nodo actual
                print_inorder(out, n->right);  // Recorrer subárbol derecho
            }
        }

        // Método recursivo para la eliminación de elementos
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Elemento NO existe");
            }
            if (e < n->elem) {
                n->left = remove(n->left, e); // Buscar en el subárbol izquierdo
            } else if (e > n->elem) {
                n->right = remove(n->right, e); // Buscar en el subárbol derecho
            } else {
                // Caso: Nodo encontrado
                if (n->left == nullptr && n->right == nullptr) {
                    // Caso 1: Nodo sin hijos
                    delete n;
                    nelem--; // Actualizar contador de nodos
                    return nullptr;
                } else if (n->left == nullptr) {
                    // Caso 2: Nodo con un hijo (derecho)
                    BSNode<T>* temp = n->right;
                    delete n;
                    nelem--; // Actualizar contador de nodos
                    return temp;
                } else if (n->right == nullptr) {
                    // Caso 2: Nodo con un hijo (izquierdo)
                    BSNode<T>* temp = n->left;
                    delete n;
                    nelem--; // Actualizar contador de nodos
                    return temp;
                } else {
                    // Caso 3: Nodo con dos hijos
                    nelem--; // Actualizar contador de nodos
                    T maxVal = max(n->left);      // Encontrar el máximo del subárbol izquierdo
                    n->elem = maxVal;            // Reemplazar con el valor máximo
                    n->left = remove_max(n->left); // Eliminar el nodo con el valor máximo
                }
            }
            return n; 	// Devolvemos el nodo que encabeza el subárbol en el que hemos eliminado el nodo
        }

        // Método recursivo que devuelve el elemento de máximo valor contenido en el (sub-)árbol
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("Árbol vacío");
            }
            if (n->right != nullptr) {
                return max(n->right); // Continuar buscando en el subárbol derecho
            }
            return n->elem; // El nodo actual es el mayor
        }

        // Método recursivo que elimina el elemento de máximo valor contenido en el (sub-)árbol
        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                return n->left; // Eliminar el nodo actual y conectar con su hijo izquierdo
            }
            n->right = remove_max(n->right); // Continuar eliminando en el subárbol derecho
            return n;
        }

        // Método recursivo para liberación de la memoria dinámica ocupada por los nodos
        void delete_cascade(BSNode<T>* n) {
            if (n == nullptr) return; //no hay más nodos por procesar (caso base)
            delete_cascade(n->left);  // Eliminar subárbol izquierdo
            delete_cascade(n->right); // Eliminar subárbol derecho
            delete n;                 // Eliminar el nodo actual, liberando la memoria dinamica
        }

    public:
        // Constructor, crea el ABB vacío
        BSTree() : nelem(0), root(nullptr) {}

        // Devuelve el número de elementos almacenados
        int size() const {
            return nelem;
        }

        // Busca y devuelve el elemento `e` de tipo T en el ABB
        T search(T e) const {
            BSNode<T>* result = search(root, e);
            if (result == nullptr) {
                throw std::runtime_error("Elemento NO encontrado");
            }
            return result->elem;
        }

        // Sobrecarga del operador []. Actúa como interfaz al método search(T e)
        T operator[](T e) const {
            return search(e);
        }

        // Inserta el elemento `e` de tipo T de manera ordenada en el ABB
        void insert(T e) {
            root = insert(root, e);
        }

        // Elimina el elemento `e` de tipo T del ABB
        void remove(T e) {
            root = remove(root, e);
        }

        // Sobrecarga del operador << para imprimir el árbol en orden
        friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }

        //Metodo destructor
        ~BSTree(){
            delete_cascade(root);
        }
};

#endif
