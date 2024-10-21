/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 6: Autómatas Regulares
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 18/10/2024

** Archivo state.cc: Implementación de la clase State
**      Contiene los métodos de la clase State
**      
** Referencias:
**      Enlaces de interes
**          https://www.geeksforgeeks.org/multimap-associative-containers-the-c-standard-template-library-stl/

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      19/10/2024 - Adición del método UploadTransition
**      19/10/2024 - Sobrecarga del operador <<
**/

#include "state.h"

/**
 * @brief Adds a transition to an existant State. Increments its number of transitions.
 * @param Symbol. Symbol that produces de transition.
 * @param Int. Id of destiny transition.
 */
void State::AddTransition (Symbol trans_symbol, long unsigned int trans__state_id) {
  ++number_transitions_;
  transitions_.insert(std::pair<Symbol, long unsigned int> (trans_symbol, trans__state_id));
}

/**
 * @brief Adds a transition to an State. Doesn't increment its number of transitions.
 * @param Symbol. Symbol that produces de transition.
 * @param Int. Id of destiny transition.
 */
void State::UploadTransition (Symbol trans_symbol, long unsigned int trans__state_id) {
  transitions_.insert(std::pair<Symbol, long unsigned int> (trans_symbol, trans__state_id));
}

/**
 * @brief Overload of operator << for State class
 * @param ostream
 * @param State
 * @return ostream
 */
std::ostream& operator<<(std::ostream& os, const State& state) {
  os << "State " << state.getId() << ":" << std::endl;
  os << "Acceptation state: " << !state.getNonAcceptation() << std::endl;
  os << "Number of states: " << state.getNumberTransitions() << std::endl;
  return os;
}
