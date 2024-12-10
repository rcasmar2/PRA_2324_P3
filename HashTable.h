#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <list>
#include <vector>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h" 
using namespace std;

template <typename V>
class HashTable: public Dict<V> {
    private:
        int n; //numero de elementos almacenados en tabla
        int max; //tamaño de la tabla hash
        ListLinked<TableEntry<V>>* table; //Tabla de cubetas representada por un array de punteros a listas enlazadas

        //Funcion Hash
        int h(string key){
            int sum = 0;
            for (char c: key){
                sum += static_cast<int>(c); // Convertir carácter a su valor ASCII y sumarlo
            }
            return sum % max;
        }
    
    public:
        //constructor que inicializa los miembros
        HashTable(int size) : max(size), n(0){//ahora max tiene el valor de size y n = 0
            table.resize(max); // Inicializamos la tabla con `size` listas vacías
        }

        //destructor que libera la memoria dinámica
        ~HashTable(){
            delete[]table;
        }

        //devuelve el valor total de cubetas
        int capacity(){
            return max;
        }

        // Sobrecarga del operador []: Devuelve el valor correspondiente a la clave
        V operator[](std::string key) {
            int index = h(key); // Índice calculado por la función hash
            auto& list = table[index]; // Referencia a la lista enlazada correspondiente

            // Buscar el elemento en la cubeta
            int pos = list.search(TableEntry<V>(key, V())); // Comparar claves usando TableEntry
            if (pos != -1) {
                return list.get(pos).getValue(); // Obtener el valor correspondiente
            }

            throw std::runtime_error("Clave no encontrada");
        }

        // Sobrecarga del operador << para imprimir el contenido de la tabla hash
        friend ostream& operator<<(ostream& out, const HashTable<V>& th) {
            for (int i = 0; i < th.max; i++) {
                out << "Cubeta " << i << ": ";
                if (!th.table[i].empty()) { // Usar el método empty() de ListLinked
                    out << th.table[i]; // Imprimir directamente la lista enlazada
                } else {
                    out << "VACÍA";
                }
                out << endl;
            }
            return out;
        }


};

#endif

