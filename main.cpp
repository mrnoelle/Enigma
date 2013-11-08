#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

#include "errors.h"

#include "enigma.hpp"
#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"



int main(int argc, char **argv) 
{
  if (argc == 1) {
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  int rotor_nb = argc - 4;
/*
  Enigma e(argv[1], argv[2]);


  for (int i = 3; i < argc - 1; ++i) {
    e.addRotor(argv[i]);
  }

  char input;
  if (isupper(input)) {
    cin>>ws;
    cin>>input;
    cout << e.encrypt(input);
  } 
  else {
  cerr << "main: invalid input character " << input << ". Terminating." << endl;
	return EXIT_FAILURE;
  }
 
  return EXIT_SUCCESS;

*/

  return 0;
  /*
  Plugboard pb;
  pb.set(argv[1]);
  //int result = pb.set(argv[1]);
  // if (result != NO_ERROR)
  //  return result;
  //Reflector rf;
  //rf.set(argv[2]);

  Enigma e(3, argv[1]); 

  // is e valid?
  e.status() 

  if (error) return ERROR_CODE;


  Rotor rot1;
  Rotor rot2;
  Rotor rot3;
  // for(int i=3; i<=argc-1; i++)
  rot1.set(argv[3]);
  rot2.set(argv[4]);
  rot3.set(argv[5]);

  int integer=0;
  integer=pb.connect(integer);
  cout <<"output of pb = "<< integer  << endl;
 
  rot1.rotate(); // rotate method should increment offset attribute in rot1
  if (rot1.inTurnoverPosition())
  // rotate other rotors if necessary

  integer = rot1.R_connect_L(integer);
  cout <<"output of rot1 " << integer << endl;
  integer = rot2.R_connect_L(integer);
  cout<< "output of rot2 " << integer << endl;
  integer = rot3.R_connect_L(integer);
  cout<< "output of rot3 " << integer << endl;
  integer = rf.connect(integer);
  cout << "output after rf " << integer << endl;

  integer = rot3.L_connect_R(integer);
  cout << "output after rot3 "<<integer << endl; 
  integer = rot2.L_connect_R(integer);
  cout << "output after rot2 "<< integer << endl;
  integer = rot1.L_connect_R(integer);
  cout << "output afetr rot1 "<< integer << endl;
  integer =pb.connect(integer);
  cout<<"result= "<<integer<<endl;
  

  */

}
