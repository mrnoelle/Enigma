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
  int start_pos[26];
  int status;
  int rotor_nb;
  
  Enigma(char* pbFile, char* rfFile);
  ~Enigma();
  int check_status();
  void addRotor(char* rotFile);
  void set_startPos(char* posFile);
  char encrypt(char letter);

};

#endif

