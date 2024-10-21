/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 6: Autómatas Finitos
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 20/09/2024

** Archivo alphabet.cc: Implementación de la clase alfabeto.
**      Contiene las implementaciones de la clase alfabeto.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      20/09/2024 - Creacion (primera version) del codigo
**      23/09/2024 - Adición del método empty
**      18/10/2024 - Adición del método find
**/

#include <iostream>
#include <algorithm>

#include "alphabet.h"


/**
 * @brief Checks if an alphabet is empty.
 * @param symbol 
 * @return bool-type. True if alphabet is empty. False otherwise.
 */
bool Alphabet::Empty() const {
  return symbols_.empty();
}

/**
 * @brief Function to add a symbol to an alphabet
 * @param symbol 
 */
void Alphabet::AddSymbol (const Symbol& symbol) {
  symbols_.insert(symbol);
}

/**
 * @brief Finds a symbol in an alphabet
 * @param symbol 
 * @return bool-type. True if found, false otherwise
 */
bool Alphabet::Find(const Symbol& symbol) {
  if (std::find(getSymbols().begin(), getSymbols().end(), symbol) == getSymbols().end()) {
    return false;
  } else {
    return true;
  }
}

/**
 * @brief Overload of << operator for Alphabet class
 * @param std::ostream  
 * @param symbol
 * @return ostream
 */
std::ostream& operator<<(std::ostream& os, const Alphabet& symbols)  {
  int counter {0};
  int alphabet_size = symbols.getSymbols().size();
  os << "{";
  for (const Symbol& symbol : symbols.getSymbols()) {
    os << symbol;
    if (counter < alphabet_size - 1) {
      os << ", ";
    }
    ++counter;
  }
  os << "}";
  return os;
}
