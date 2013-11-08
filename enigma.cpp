#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

#include "enigma.hpp"
#include "errors.h"
#include "rotor.hpp"
#include "plugboard.hpp"
#include "reflector.hpp"


Enigma::Enigma(char* pbFile, char* rfFile)
{
  pb_ = new Plugboard(pbFile);
  rf_ = new Reflector(rfFile);
}

Enigma::~Enigma() {
  delete pb_, rf_;

  // delet vector<Rotor*>!!!

}


int Enigma::check_status() {

  return status;
}

void Enigma::addRotor(char* rotFile, char* posFile, int rotor_nb) {
  rotors_.push_back(new Rotor(rotFile, posFile, rotor_nb));
}

char Enigma::encrypt(char letter) {

  int input = letter - 'A';
  // Map through plugboard
  input = pb_->connect(input);

  /*
  // Rotate rotors, breaking out of the loop unless a rotor completes a full rotation
  for (vector<Rotor*>::iterator it = rotors_.begin(); it != rotors_.end(); ++it) {
    if (!(*it)->rotate()) break;
    ｝

  
    // Map through rotors forwards
    for (vector<Rotor*>::iterator it = rotors_.begin(); it != rotors_.end(); ++it) {
      input = (*it)->connect_forwards(input);
    }
  */

    // Map through reflector
    input = rf_->connect(input);
    /*
    // Map through rotors backwards
    for (vector<Rotor*>::reverse_iterator it = rotors_.rbegin(); it != rotors_.rend(); ++it) {
      input = (*it)->connect_backwards(input);
    }
    */

    // Map through plugboard
    input = pb_->connect(input);

    char result= input + 'A';

    return result ;
}


/*
Enigma::Enigma(int no_of_rotors, char* pbFile) : pb(pbFile)
{
  //error 1: insufficient number of parameters
  reflector rf;
  int MAX=10;
  rotor rot[MAX];
  

  // pb.set(pbFile);
  rf.set(argv[2]);

    for(int number=0; number <= no_of_rotors; number++){
    rot[number].set(argv[]);
    }
 

  if (error) status = error
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
*/
