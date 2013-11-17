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
  int start_pos[104];
  int startPos_size;
  int status;
  int rotor_nb;
  
  Enigma();
  Enigma(char* pbFile, char* rfFile);
  ~Enigma();
  int check_status();
  void addRotor(char* rotFile);
  int set_startPos(char* posFile);
  char encrypt(char letter);

};

#endif

