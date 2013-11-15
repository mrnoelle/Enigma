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

  rf = new Reflector(rfFile);
 
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

 
//create new rotors

void Enigma::addRotor(char* rotFile) 
{
  
  rotors.push_back(new Rotor(rotFile));
  int rot_result = rotors.back()->check_status();
  if(rot_result>0){
    status = rot_result;
    return ;
  }
  
}

//setting start position

int Enigma::set_startPos(char* posFile)
{

  ifstream in_stream;

  /*set start_pos*/
  in_stream.open(posFile);
  if(in_stream.fail())
    return ERROR_OPENING_CONFIGURATION_FILE;
  int i = 0;
  int next;
  in_stream >> next;
  while(!in_stream.eof()){
      start_pos[i]=next;
      in_stream >> next;
      i++;
  }
  startPos_size = i;
  in_stream.close();

  /*
  int rotor_nb = static_cast<int>(rotors.size())
    if (rotor_nb > startPos_size)
      return NO_ROTOR_STARTING_POSITION;
  */

  for(unsigned int count =0; count < rotors.size(); count++){
    rotors[count]->set_offset(start_pos[count]);
  }

  return NO_ERROR;
}

/* check error for no rotor starting position 
int Enigma::error_no_startPos(int argc, int satrtPos_size){
  int rotor_nb = argc-4;
rotor_nb = static_cast<int>(rotors.size())
  if (rotor_nb > startPos_size)
    return NO_ROTOR_STARTING_POSITION;
}
*/

//enigma machine encrypt 

char Enigma::encrypt(char letter)
{

  int input = letter - 'A';
  // Map through plugboard
  input = pb->connect(input);


  // Map through rotors forwards

  rotors[rotors.size()-1]->rotate();

  for( int i = (rotors.size()-1); i > -1; i--){
  
    if(rotors[i]->isNotch())
      rotors[i-1]->rotate();

  }

  for( int i = (rotors.size()-1); i > -1; i--){
    input = rotors[i]->connect_forwards(input);
  }

  cout<<"rotor output= "<<input<<endl;


  // Map through reflector
  input = rf->connect(input);

  cout<<"rf output= "<<input<<endl;

  // Map through rotors backwards
  for( unsigned int i=0; i < rotors.size(); i++){
 
    input = rotors[i]->connect_backwards(input);
  }

  cout<<"rotor backwards output= "<<input<<endl;

  // Map through plugboard
  input = pb->connect(input);

  char result= input + 'A';

  cout<<"result= "<<result<<endl;

  return result ;
  cout<< endl;

}




