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

** Archivo check_functions.cc: Implementación de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      18/10/2024 - Creación de funciones de validación de formatos y de ValidateNumber
**      19/10/2024 - Adición de aclaración en Help. & como símbolo reservado a cadena vacía
**/

#include <regex>
#include <iostream>
#include "check_functions.h"

/**
 * @brief Validates the extension of the input text file
 * @param string  
 * @return bool-type. True if the file is accepted. False otherwise
 */
bool ValidateFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(txt)$)");
  return std::regex_match(name, pattern);
}


/**
 * @brief Validates the extension of the input automatan file
 * @param string  
 * @return bool-type. True if the file is accepted. False otherwise
 */
bool ValidateAutomatanFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(fa)$)");
  return std::regex_match(name, pattern);
}


/**
 * @brief Checks if a given string is made out of (only) numbers or not
 * @param string
 * @return bool
 */
bool ValidateNumber (const std::string& line) {
  if (!line.empty()) {
    for (char chr : line) {
      if (!std::isdigit(chr)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Uses ValidateFile function. Acts in consequence of the returned type
 * @param string  
 */
void CheckFileError (const std::string& name) {
  if (ValidateFile(name)) return;
  std::cerr << "Error in input file: Wrong extension. Please, try \"./p06_automata_simulator --help\" for further information" << std::endl;
  exit(EXIT_FAILURE);
}


/**
 * @brief Uses ValidateFile function. Acts in consequence of the returned type
 * @param string  
 */
void CheckAutomataError (const std::string& name) {
  if (ValidateAutomatanFile(name)) return;
  std::cerr << "Error in input file: Wrong extension. Please, try \"./p06_automata_simulator --help\" for further information" << std::endl;
  exit(EXIT_FAILURE);
}


/**
 * @brief Validates the line of commands and uses Help, Usage and CheckFileError functions
 * @param int argc  
 * @param char* argv[]
 */
void ValidateCommand(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    Help();
    exit(EXIT_SUCCESS);
  }
  if (argc != 3) {
    Usage();
    exit(EXIT_FAILURE);
  }
  if (argc == 3 && (std::string(argv[2]).find('.') != std::string::npos)) {
    CheckAutomataError(std::string(argv[1]));
    CheckFileError(std::string(argv[2]));
  }
  if (argc == 3 && (std::string(argv[2]).find('.') == std::string::npos)) {
    return;
  }
}


/**
 * @brief Prints Help to the user
 */
void Help () {
    std::cout << "./p06_automata_simulator -- Code analyzer\n"
              << "Usage:          ./p06_automata_simulator input.fa <input.txt|string>\n"
              << "\n"
              << "input.fa:        Input file with extension fa. Codificates the information of the automaton such as:\n"
              << "                       Line 1: Alphabet simbols separated by one blank space.\n"
              << "                                      - '&' cannot be part of alphabet. Reserved symbol for empty string.\n"
              << "                       Line 2: Total of states the automaton has got.\n"
              << "                       Line 3: Start state.\n"
              << "                       Line 4 and on: For each line, separated by one blank space:\n"
              << "                                      - Identification number of the state.\n"
              << "                                      - 1 if acceptation State. 0 otherwise.\n"
              << "                                      - Number of transitions the state has got. And for each transition:\n"
              << "                                               - Required symbol so the transition is executed.\n"
              << "                                               - Destiny state in the transition.\n"
              << "input.txt:       Input file with extension txt. It has a string belonging to the given alphabet in each line.\n"
              << "string:          String to be analyzed."
              << "\n";
}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "How to use: ./p06_automata_simulator input.fa <input.txt|string>\n"
            << "Try './p06_automata_simulator --help' for further information\n";
}