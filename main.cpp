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

//const char *error_description(int code);


int main(int argc, char **argv) 
{
  if (argc < 3) {
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  //check error
  

  //set plugboard and reflector configuration
  Enigma e(argv[1], argv[2]);
  
/*
  int result=e.check_status();
  if (result>0){
    cout << error_description(result)<<endl;
    return 0; 
  }
*/

  //set rotors configuration
  for (int i = 3; i < argc - 1; i++) {
    e.addRotor(argv[i]);
  }
  e.set_startPos(argv[argc-1]);

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


/*
const char *error_description(int code)
{

  switch(code) {
  case 0:
    return "NO_ERROR";

  case 1: 
    return "INSUFFICIENT_NUMBER_OF_PARAMETERS";
   
  case 2:
    return  "INVALID_INPUT_CHARACTER";
    
  case 3:
    return "INVALID_INDEX";
 
  case 4:
    return "NON_NUMERIC_CHARACTER";
    
  case 5:
    return "IMPOSSIBLE_PLUGBOARD_CONFIGURATION";
    
  case 6:
    return "INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS";

  case 7:
    return "INVALID_ROTOR_MAPPING"; 
   
  case 8:
    return "NO_ROTOR_STARTING_POSITION";
   
  case 9:
    return "INVALID_REFLECTOR_MAPPING";
  
  case 10:
    return "ERROR_OPENING_CONFIGURATION_FILE";
  
 
  }
  return "UNKNOW_ERROR";
}
*/
