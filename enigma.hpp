#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "vector"


class Enigma {

private:
  Plugboard* pb;
  vector<Rotor*> rotors;
  Reflector* rf;
 
public:
  
  int rotor_nb;
  
  Enigma(char* pbFile, char* rfFile);
  ~Enigma();
  int pb_checkError(char* pbFile);
  int rf_checkError(char* rfFile);
  int rot_checkError(char* rotFile);
  void addRotor(char* rotFile);
  int set_startPos(char* posFile);
  char encrypt(char letter);

};

#endif

