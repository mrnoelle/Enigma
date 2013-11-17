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


Enigma::Enigma()
{

  for(int i=0; i < 104; i++)
    start_pos[i] = 0;
}


Enigma::Enigma(char* pbFile, char* rfFile): pb(NULL), rf(NULL)
{
  status = 0;

  pb = new Plugboard(pbFile);
  int pb_result = 0;
  pb_result = pb->check_status();
  if(pb_result>0){
    status = pb_result;
    return ;
  }

  int rf_result = 0;
  rf = new Reflector(rfFile);
  rf_result = rf->check_status();
  if(rf_result>0){
    status = rf_result;
    return ;
  } 
}

Enigma::~Enigma()
{
  if(pb)
    delete pb;
  if(rf)
    delete rf;
  
  for( unsigned int i=0; i < rotors.size(); i++)
    delete rotors[i];
}


int Enigma::check_status()
{

  return status;
}

 
/* create new rotors */
void Enigma::addRotor(char* rotFile) 
{  
  rotors.push_back(new Rotor(rotFile));
  int rot_result = rotors.back()->check_status();
  if(rot_result>0){
    status = rot_result;
    return ;
  } 
}

/* Set start position and check error */
int Enigma::set_startPos(char* posFile)
{
  int i=0;
  int next;
  ifstream in_stream(posFile);

  /* Check [ERROR 11]: open configuration file failed */
  if(in_stream.fail())
    return ERROR_OPENING_CONFIGURATION_FILE;

  in_stream >> next;
  while (!in_stream.eof()){ 
    /* Check [ERROR 4]: read in something that is not an integer */
    if(in_stream.fail())
      return NON_NUMERIC_CHARACTER; 

    /* Check [ERROR 3]: the number is not between 0 and 25 */
    if(next < 0 || next > 25)
      return INVALID_INDEX; 

    start_pos[i] = next;
    in_stream >> next;
    i++;

  }   
  startPos_size = i;
  in_stream.close();

  /* Check [ERROR 8]: do not contain enough rotor position */
  rotor_nb = static_cast<int>(rotors.size());
  if (rotor_nb > startPos_size)
    return NO_ROTOR_STARTING_POSITION;

  /* Finish error check, set start position for each rotor */
  for(unsigned int count =0; count < rotors.size(); count++){
    rotors[count]->set_offset(start_pos[count]);
  }

  return NO_ERROR;
}


/* Enigma machine encrypt */ 
char Enigma::encrypt(char letter)
{

  int input = letter - 'A';
  /* Map through plugboard */
  input = pb->connect(input);

  if ( rotors.size() > 0){
    /* Always rotate the last rotor */
    rotors[rotors.size()-1]->rotate();

    /*Check notch position*/
    for( int i = (rotors.size()-1); i > -1; i--){ 
   
      if(rotors[i]->isNotch()){
	rotors[i-1]->rotate();
      }
    
    }


    /* Map through rotors forwards */
    for( int i = (rotors.size()-1); i > -1; i--){
  
      input = rotors[i]->connect_forwards(input);
    }
  }

  /* Map through reflector */
  
  input = rf->connect(input);
 
 
  if ( rotors.size() > 0){
    /* Map through rotors backwards */
    for( unsigned int i=0; i < rotors.size(); i++){
 
      input = rotors[i]->connect_backwards(input);
    }
  }

  /* Map through plugboard */
  input = pb->connect(input);

  char result= input + 'A';

  return result ;

  cout << endl;

}




