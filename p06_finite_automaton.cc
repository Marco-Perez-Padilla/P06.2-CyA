/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 6: Autómatas Finitos
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 18/10/2024

** Archivo p06_finite_automaton.cc: programa cliente.
**      Contiene la funcion main del proyecto que usa las clases estado, NFA, cadena y símbolo para 
**      crear un simulador de NFA's funcional en base a un fichero de entrada .fa y  otro .txt  que 
**      que contienen la codificación de un NFA y una lista de cadenas, respectivamente.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      19/10/2024 - Creación del simulador
**      21/10/2024 - Modificación para aceptar una cadena por línea de comando
**/

#include <iostream>

#include "check_functions.h"
#include "NFA.h"

int main (int argc, char* argv[]) {
  ValidateCommand(argc, argv);
  NFA nfa(argv[1]);
  if (argc == 3 && (std::string(argv[2]).find('.') == std::string::npos)) {
    nfa.SingleStringSimulateAutomaton(std::string(argv[2]));
  } else {
    nfa.SimulateAutomaton(argv[2]);
  }
  return 0;
}