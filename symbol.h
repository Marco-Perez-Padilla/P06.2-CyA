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

** Archivo symbol.h: Declaración de la clase símbolo
**      Contiene las declaraciones de la clase símbolo
**      
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      20/09/2024 - Creacion (primera version) del codigo
**      24/09/2024 - Tratamiento especial de la cadena vacía como longitud 0
**/

#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol {
 private:
  char character_;

 public:
  Symbol (char character) : character_(character) {}; //Constructor for class symbol
  char getSymbol () const {return character_;} //Getter

  //Operators
  bool operator< (const Symbol&) const;
  bool operator== (const Symbol&) const;
};
std::ostream& operator<<(std::ostream& os, const Symbol&); //Overload of out stream operator for symbol class

#endif