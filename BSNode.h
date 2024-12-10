#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>
using namespace std;

template <typename T> 
class BSNode {
    public:
        // Atributos
        T elem; // Elemento almacenado en el nodo
        BSNode<T>* left; // Puntero al nodo sucesor izquierdo
        BSNode<T>* right; // Puntero al nodo sucesor derecho

        // Método constructor que inicializa los miembros
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
            : elem(elem), left(left), right(right) {}

        // Sobrecarga global del operador << para imprimir el nodo por pantalla
        friend ostream& operator<<(ostream& out, const BSNode<T>& bsn) {
            out << bsn.elem; // Imprimir el elemento almacenado
            return out;
        }
};

#endif
