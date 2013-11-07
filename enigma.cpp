#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

#include "enigma.hpp"
#include "errors.h"

Enigma::Enigma(int no_of_rotors, char* pbFile) : pb(pbFile)
{
  //error 1: insufficient number of parameters
  reflector rf;
  int MAX=10;
  rotor rot[MAX];
  

  // pb.set(pbFile);
  rf.set(argv[2]);
  /*
    for(int number=0; number <= no_of_rotors; number++){
    rot[number].set(argv[]);
    }
  */

  if (error) status = error
}

Enigma::status() {

  return status;

}

char Enigma::encrypt(char input)
{
  cin >> input;
  if(isupper(input)){
    int integer = input - 'A';
    integer = pb.connect(integer);
    //rotor encrypt
    
    integer = rf.connect(integer);
    integer = pb.connet(integer);
    char letter = integer + 'A';
    return letter;
  }
  else return INVALID_INPUT_CHARACTER;
}


void link_rotor(int no_of_rotors, int set_notch)
