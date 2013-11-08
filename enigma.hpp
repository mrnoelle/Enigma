#ifndef ENIGMA_H
#define ENIGMA_H

#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "vector"


class Enigma {

private:
  Plugboard* pb_;
  vector<Rotor*> rotors_;
  Reflector* rf_;
 
public:
  int status;
  Enigma(char* pbFile, char* rfFile);
  ~Enigma();
  int check_status();
  void addRotor(char* rotFile, char* posFile, int rotor_n);
  char encrypt(char letter);

};

#endif

/*
class Enigma
{

private:
  Plugboard &pb;
  Reflector &rf;
  Rotor &rot[MAX];

  int status;

public:
  Enigma(int no_of_rotors);
  char encrypt(char input);


};
*/
