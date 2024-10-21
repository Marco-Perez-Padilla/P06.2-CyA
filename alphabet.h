/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 2: Cadenas y lenguajes
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 20/09/2024

** Archivo alphabet.h: Declaración de la clase alfabeto.
**      Contiene las declaraciones de la clase alfabeto.
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      20/09/2024 - Creacion (primera version) del codigo
**      23/09/2024 - Adición del método empty
**      18/10/2024 - Adición del método find
**/

#ifndef ALPHABET_H
#define ALPHABET_H

#include <set>

#include "symbol.h"
#include "chain.h"

class Alphabet {
 private:
  std::set<Symbol>symbols_; 

 public:
  Alphabet() = default;
  Alphabet (const std::set<Symbol>& symbols) : symbols_(symbols) {}  //Constructor
  const std::set<Symbol>& getSymbols () const {return symbols_;} //Getter

  bool Empty() const;
  void AddSymbol (const Symbol&); //Function to add symbols to the alphabet
  bool Find (const Symbol&); //Function to check if a certain symbol is part of alphabet
};
std::ostream& operator<<(std::ostream& os, const Alphabet&); //Overload of out stream operator for alphabet class

#endif