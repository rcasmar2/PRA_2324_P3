#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <ostream>
#include <string>

using namespace std;

template <typename V>
class TableEntry {
    public:
        // Atributos 
        string key;
        V value;

        // Constructor 1: Inicializamos clave y valor
        TableEntry(string key, V value) : key(key), value(value) {}

        // Constructor 2: Inicializamos solamente con clave
        TableEntry(string key) : key(key), value(V()) {}

        // Constructor 3: Inicializamos sin clave ni valor
        TableEntry() : key(""), value(V()) {}

        // Sobrecargamos el operador ==
        friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key == te2.key;
        }

        // Sobrecargamos el operador !=
        friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key != te2.key;
        }

        // Sobrecargamos el operador <<
        friend ostream &operator<<(ostream &out, const TableEntry<V> &te) {
            out << "('" << te.key << "' => " << te.value << ")";
            return out;
        }
};

#endif
