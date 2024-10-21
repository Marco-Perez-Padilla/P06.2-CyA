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

** Archivo check_functions.h: Declaracion de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      18/10/2024 - Creación de funciones de validación de formatos y de ValidateNumber
**/

#include <iostream>

bool ValidateFile (const std::string& name);
bool ValidateAutomatanFile (const std::string& name);
bool ValidateNumber (const std::string& line);
void CheckFileError (const std::string& name);
void ValidateCommand(int argc, char* argv[]);
void Help ();
void Usage();