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

** Archivo NFA.cc: Implementación de la clase NFA
**      Contiene los métodos de la clase NFA
**      
** Referencias:
**      Enlaces de interes:
**          https://www.geeksforgeeks.org/multimap-equal_range-in-c-stl/ 

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      19/10/2024 - Adición de operador []
**      19/10/2024 - Adición de método simulador de Autómatas
**      20/10/2024 - Adición de método para calcular la épsilon-clausura
**      21/10/2024 - Mayor manejo de errores 
**      21/10/2024 - Manejo de cadenas con símbolos no pertenecientes al alfabeto
**      21/10/2024 - Adición de método simulador de Autómata para una sola cadena
**      21/10/2024 - Modificación de simulador de Autómata para archivo
**/

#include <sstream>
#include <set>

#include "NFA.h"
#include "state.h"
#include "chain.h"
#include "check_functions.h"


/**
 * @brief Constructor for NFA
 * @param Input file
 */
NFA::NFA (const std::string& file_fa){
  if (ProcessAutomaton(file_fa) == true) {}
  else {
    exit(EXIT_FAILURE);
  }
}


/**
 * @brief Reads given file and processes the NFA
 * @param Input file
 */
bool NFA::ProcessAutomaton (const std::string& file_fa) {
  std::ifstream input_fa(file_fa);
  if (!input_fa.is_open()) {
    std::cerr << "Error: File couldn't be opened " << file_fa << ". Try \"./p06_automata_simulator --help\" for further information " << std::endl;
    return false;
  }

  std::string line;

  //initialization of variables for later uses.
  long unsigned int states {0};
  long unsigned int start {0};
  long unsigned int id {0};
  long unsigned int num_transitions {0};
  bool non_accept;
  Alphabet alphabet;

  //Reading the alphabet  
  if (std::getline(input_fa, line)) {
    for (char chr : line) {
      if (chr != ' ' && chr != '&' ) {
        alphabet.AddSymbol(Symbol(chr));
      }
    }
  }

  //Checking the alphabet
  if (alphabet.Empty()) {
    std::cerr << "Incorrect input format in line 1: Alphabet cannot be empty." << std::endl;
    return false;
  }

  alphabet_ = alphabet;

  //Reading number of total states
  if (std::getline(input_fa, line)) {
    if (ValidateNumber(line)) {
      states = std::stoi(line);
      if (states <= 0) {
        std::cerr << "Error: Number of states cannot be negative nor 0.\n"
                  << "Try './p06_automata_simulator --help' for further information\n";
        return false;
      }
    } else {
      std::cerr << "Error: Incorrect format in total state numbers line.\n"
                << "Try './p06_automata_simulator --help' for further information\n";
      return false; 
    }
  }

  //Reading Start State
  if (std::getline(input_fa, line)) {
    if (ValidateNumber(line)) {
      start = std::stoi(line);
      if (start < 0) {
        std::cerr << "Error: Start state cannot be negative.\n"
                  << "Try './p06_automata_simulator --help' for further information\n";
        return false;
      }
    } else {
      std::cerr << "Error: Incorrect format in Start state line.\n"
                << "Try './p06_automata_simulator --help' for further information\n";
      return false; 
    }
    if (start >= states) {
      std::cerr << "Error: Start state must be between range: [0-" << states - 1 << "] "<< std::endl;
      return false;
    } 
  }

  long unsigned int iteration_counter {3};
  bool start_initialitation = false;

  //Reading each state
  for (long unsigned int i {0}; i < states; ++i) {
    if (std::getline(input_fa, line)) {
      std::istringstream single_line (line);
      single_line >> id >> non_accept >> num_transitions;

      //Checks range errors in id.
      if (id >= states) {
        std::cerr << "Error in line " << iteration_counter + 1 <<  ": Current state must be between range: [0-" << states - 1 << "] "<< std::endl;
        return false;
      }

      State state(id, non_accept, num_transitions);

      //Procceses each transition
      for (long unsigned int j {0}; j < state.getNumberTransitions(); ++j) {
        char symbol;
        long unsigned dest_state;
        if (single_line >> symbol >> dest_state) {
          Symbol trans_symbol (symbol);

          //Deals with errors in symbols
          if (!alphabet.Find(trans_symbol) && trans_symbol.getSymbol() != '&') {
            std::cerr << "Fatal error in line "<< iteration_counter + 1 << ": Transition symbol does not belong to described alphabet." << std::endl;
            return false;
          }

          //Deals with range errors
          if (dest_state >= states) {
            std::cerr << "Error in line " << iteration_counter + 1 <<  ": Destiny state must be between range: [0-" << states - 1 << "] "<< std::endl;
            return false;
          }

          //Adds transitions to the state
          state.UploadTransition(trans_symbol, dest_state);
          
          //Deals with format errors in transitions
        } else {
          std::cerr << "Error in line " << iteration_counter + 1 << ": Incorrect format in transitions.\n"
                    << "Try './p06_automata_simulator --help' for further information\n";
          return false;
        }
      }

      ++iteration_counter;
      if (start == id) {
        start_ = state;
        start_initialitation = true;
      } 
      AddState(state);
    }
  }

  if (start_initialitation == false) {
    std::cerr << "Error: There is no start state" << std::endl;
    return false;
  }
  if (iteration_counter - 3 != states) {
    std::cerr << "Error: Number of states do not match number of states described" << std::endl;
    return false;
  }
  return true;
}


/**
 * @brief Method that calculates epsilon closure from a start state
 * @param Set which stores start state and is modified to include epsilon closure
 * @return Set with epsilon closure
 */
std::set<long unsigned int> NFA::EpsilonClosure(const std::set<long unsigned int>& current_states) {
  std::set<long unsigned int> epsilon_closure = current_states;
  //Flag to iterate until there is no available next state
  bool found = true;
  while (found) {
    found = false;
    std::set<long unsigned int> epsilon_iterations = epsilon_closure; 

    for (const long unsigned int id : epsilon_iterations) {
      auto all_states = getStates().equal_range(id); //all_states.first has got first State coinciding with id. all_states.second the first one that doesn't coincidence
      for (auto identification = all_states.first; identification != all_states.second; ++identification) {   //For each id according to a same state
        const State& state = identification->second;   //Next state
        const std::multimap<Symbol, long unsigned int>& transitions = state.getTransitions(); //We get next state transitions
        for (const std::pair<const Symbol, long unsigned int>& transition : transitions) {   //For each transition in transitions
          if (transition.first.getSymbol() == '&') {   //If symbol is &
            long unsigned int next = transition.second;   //We insert that next state in our border
            if (epsilon_closure.find(next) == epsilon_closure.end()) {  //If not found in epsilon closure, then add and continue the loop
              epsilon_closure.insert(next);
              found = true;
            }
          }
        }
      }
    }
  }
  return epsilon_closure;
}


/**
 * @brief NFA simulator for a single string
 * @param string
 * @param iteration. Used to detect the line if it's used to analyze a file
 */
void NFA::SingleStringSimulateAutomaton (const std::string& string, long unsigned int iteration) {
  Chain input_chain (string);

  std::set<long unsigned int> current_states;    //Set for states NFA is in.
  current_states.insert(getStart().getId());
  current_states = EpsilonClosure(current_states); //Doing epsilon closure

  bool correct = true; //Flag to check if all symbols of string belong to the alphabet

  if (!input_chain.Empty()) {
      
    for (long unsigned int i {0}; i < input_chain.ChainSize(); ++i) {
      bool found = false;

      for (const Symbol& symbol : getAlphabet().getSymbols()) {
        if (input_chain[i] == symbol.getSymbol() || input_chain[i] == '&') {
          found = true;
          break;
        } else {
          break;
        }
      }
      if (found == false) {
        correct = false;
        break;
      }      
    }

    bool multiple_string = false;
    for (const Symbol& symbol : input_chain.getChain()) {   //For each symbol:
      if (symbol.getSymbol() == ' ') {
        std::cerr << "Error in line " << iteration << ": More than one string in same line" << std::endl;
        multiple_string = true;
        break;
      }

      std::set <long unsigned int> border_states;           //Set for next accesible states from each symbol

      for (long unsigned int id : current_states) {    //From each state of our set
        auto all_states = getStates().equal_range(id); //all_states.first has got first State coinciding with id. all_states.second the first one that doesn't coincidence
        for (auto identification = all_states.first; identification != all_states.second; ++identification) {   //For each id according to a same state
          const State& state = identification->second;   //Next state
          const std::multimap<Symbol, long unsigned int>& transitions = state.getTransitions(); //We get next state transitions
          for (const std::pair<const Symbol, long unsigned int>& transition : transitions) {   //For each transition in transitions
            if (transition.first == symbol) {   //If symbol is a transition symbol
              border_states.insert(transition.second);   //We insert that next state in our border
            }
          }
        }
      }

      //We get final states. To process them, they'll be current states, and we clear border states, liberating memory
      current_states = border_states;
      border_states.clear();
    }

    if (multiple_string == true) {
      return;
    }

    //Flag to finish as soon as we find it is accepted
    bool accepted = false;

    for (long unsigned int id : current_states) {
      const State& state = getStates().find(id)->second; //We have unique states this time
      if (state.getNonAcceptation() == 1) {   //If any of the states in our set is acceptation state, we accept the chain
        accepted = true;
        correct = true;
        break;
      }
      correct = true;
    }

    if (input_chain.getChain()[0].getSymbol() == '&' && getStart().getNonAcceptation() == 1) { //Special case
      correct = true;
      accepted = true;
    }
      
    if (accepted) {
      std::cout << input_chain << " --- Accepted" << std::endl; 
    } else if (!correct) {
      std::cout << input_chain << " --- Rejected: String has at least one symbol that does not belong to alphabet" << std::endl; 
    } else {
      std::cout << input_chain << " --- Rejected" << std::endl; 
    }

  } else {
    std::cerr << "Error in line " << iteration << ": There is no string" << std::endl;
  }
  return;
}


/**
 * @brief Simulates the behaviour of an NFA, accepting or rejecting input strings
 * @param Input file
 */
void NFA::SimulateAutomaton (const std::string& file_txt) {
  std::ifstream input_txt(file_txt);

  if (!input_txt.is_open()) {
    std::cerr << "Error: File couldn't be opened " << file_txt << ". Try \"./p06_automata_simulator --help\" for further information " << std::endl;
    return;
  }

  std::string line;
  long unsigned int iteration_counter {1};
  
  while (std::getline(input_txt, line)) {
    SingleStringSimulateAutomaton(line, iteration_counter);
    
    ++iteration_counter;
  }
  return;
}


/**
 * @brief Gets states given a determined ID
 * @param INT ID
 * @return Vector of States 
 */
std::vector<State> NFA::operator[](const long unsigned int id) const {
  std::vector<State> results;

  if (id < 0 || id >= getStates().size()) {
    std::cerr << "Error: Cannot access " << id << " state. It must be in range [0-" << getStates().size() - 1 << "]" << std::endl;
    exit (EXIT_FAILURE);
  }

  for (const std::pair<long unsigned int, State> state : getStates()) {
    if (state.first == id) {
      results.push_back(state.second);
    }
  }

  if (!results.empty()) {
    return results;
  } else {
    std::cerr << "Error: There is no state associated to the ID: " << id << std::endl;
    exit (EXIT_FAILURE);
  }
}