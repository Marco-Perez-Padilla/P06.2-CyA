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

** Archivo state.h: Declaración de la clase State
**      Contiene las declaraciones de la clase State
**      
** Referencias:
**      Enlaces de interes
**          https://www.geeksforgeeks.org/multimap-associative-containers-the-c-standard-template-library-stl/

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      19/10/2024 - Adición del método UploadTransition
**      19/10/2024 - Sobrecarga del operador <<
**/

#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <map>

#include "alphabet.h"
#include "symbol.h"

class State {
 private:
  long unsigned int Id_;  //Id of the states. Used in constructor, to start simulator and in AddState
  bool non_acceptation_;  //Checks if state is acceptation state or not. Used in simulator
  long unsigned int number_transitions_;  //Number of transitions, used in processing the automaton and in constructor as part of unique identification of the states
  std::multimap<Symbol, long unsigned int> transitions_; //Allows a state to have more than one transition with same symbol and stores all transitions. Used processing the automaton
 public:
  //Constructors
  State () = default;
  State (long unsigned int Id, bool non_acceptation, long unsigned int num_trans) : Id_ (Id), non_acceptation_ (non_acceptation), number_transitions_ (num_trans), transitions_() {}

  //Getters
  const long unsigned int& getId () const {return Id_;}
  const bool& getNonAcceptation () const {return non_acceptation_;}
  const long unsigned int& getNumberTransitions () const {return number_transitions_;}
  const std::multimap<Symbol, long unsigned int>& getTransitions () const {return transitions_;}

  //Method to add transitions. Must be careful with their uses
  void AddTransition (Symbol trans_symbol, long unsigned int trans_state);
  void UploadTransition (Symbol trans_symbol, long unsigned int trans_state);
};
std::ostream& operator<<(std::ostream& os, const State& state);

#endif