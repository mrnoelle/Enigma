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


const char *error_description(int code);


int main(int argc, char **argv) 
{
  if (argc < 3) {
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  //set plugboard and reflector configuration
  Enigma e(argv[1], argv[2]);
  

  int result=e.check_status();
  if (result>0){
    cerr << error_description(result)<<endl;
    return result; 
  }


  //set rotors configuration
  for (int i = 3; i < argc - 1; i++) {
    e.addRotor(argv[i]);
  }
  e.set_startPos(argv[argc-1]);

  
/*
  int result=e.check_status();
  if (result>0){
    cerr << error_description(result)<<endl;
    return result; 
  }
*/

 
  //encryption
  char input;
  cin>>ws;
  cin>>input;
  cout<<"input = "<<input<<endl;
  while(!cin.eof()){

  //check input is an upper case letter
  if (isupper(input)) {
    cout << e.encrypt(input);
  } 
  else {
    cerr << "main: invalid input character " << input << ". Terminating." << endl;
    return  INVALID_INPUT_CHARACTER;
  }

  cin>>ws;
  cin>>input;
  }
 
  return NO_ERROR;

}



const char *error_description(int code)
{

  switch(code) {
  case NO_ERROR:
    return "NO_ERROR";

  case INSUFFICIENT_NUMBER_OF_PARAMETERS: 
    return "INSUFFICIENT_NUMBER_OF_PARAMETERS";
   
  case INVALID_INPUT_CHARACTER:
    return  "INVALID_INPUT_CHARACTER";
    
  case INVALID_INDEX:
    return "INVALID_INDEX";
 
  case NON_NUMERIC_CHARACTER:
    return "NON_NUMERIC_CHARACTER";
    
  case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
    return "IMPOSSIBLE_PLUGBOARD_CONFIGURATION";
    
  case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
    return "INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS";

  case INVALID_ROTOR_MAPPING:
    return "INVALID_ROTOR_MAPPING"; 
   
  case NO_ROTOR_STARTING_POSITION:
    return "NO_ROTOR_STARTING_POSITION";
   
  case INVALID_REFLECTOR_MAPPING:
    return "INVALID_REFLECTOR_MAPPING";
  
  case ERROR_OPENING_CONFIGURATION_FILE:
    return "ERROR_OPENING_CONFIGURATION_FILE";
  
  default:
    return "UNKNOW_ERROR";
  }
 
}
