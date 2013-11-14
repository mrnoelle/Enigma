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
  pb = new Plugboard(pbFile);
  rf = new Reflector(rfFile);
}

Enigma::~Enigma()
{
  delete pb;
  delete rf;
  for( unsigned int i=0; i < rotors.size(); i++)
    delete rotors[i];

}


/*
int Enigma::pb_checkError(char* pbFile)
{
  ifstream file;
  file.open(pbFile); 
  int i=0;
  int pb[52];
  int pb_length;
  file >> pb[i];
  while (!file.fail()){
    i++;   
    file>>pb[i];
   
  }  
  pb_length = i;
  file.close();
  //error 3: invalid index
  for(int i=0; i < pb_length; i++){
  if(pb[i] < 0 || pb[i] >25)
    return INVALID_INDEX;  
  }
  //error 4: non-numerical character
  for(int i=0; i < pb_length; i++){
  if(!isdigit(pb[i]))
    return NON_NUMERIC_CHARACTER;
  }
 
  //error 5: impossible plugboard configuration?????????????
  for(int index_1 = 0; index_1 <= pb_length; index_1 ++){
    for(int index_2 =0; index_2 <= pb_length; index_2 ++){
      if(pb[index_1] == pb[index_2])
      	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    } 
  }
 
  //error 6: incorrect number of parameters
  if(pb_length%2 != 0)
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

}

int Enigma::rf_checkError(char* rfFile)
{
  ifstream file;
  file.open(rfFile); 
  int i=0;
  int rf[52];
  int rf_length;
  file >> rf[i];
  while (!file.fail()){
    i++;   
    file>>rf[i];
   
  }  
  rf_length = i;

  file.close();

  //error 3: invalid index
  for(int i=0; i < rf_length; i++){
  if(rf[i] < 0 || rf[i] >25)
    return INVALID_INDEX;  
  }
  //error 4: non-numerical character
  for(int i=0; i < rf_length; i++){
  if(!isdigit(rf[i]))
    return NON_NUMERIC_CHARACTER;
  }
 
  //error 9: invalid reflector mapping
  for(int index_1 = 0; index_1 <= rf_length; index_1 ++){
    for(int index_2 =0; index_2 <= rf_length; index_2 ++){
      if(rf[index_1] == rf[index_2])
      	return INVALID_REFLECTOR_MAPPING;
    } 
  }
 
  //error 10: incorrect number of parameters
  if(rf_length != 26)
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
}

int Enigma::rot_checkError(char* rotFile)
{
  ifstream file;
  file.open(rotFile);
  int rot_map[52], rot_config_size = 0;
  int rot_notch[26], notch_size = 0;
  int i = 0;
  file>>rot_map[i];
  if(!file.fail()){
    for(int i=0; i<52; i++){
      file>>rot_map[i];
      rot_config_size=i;
    }
    while(!file.fail()){
      int j=0;
      file>>rot_notch[j];
      j++;
      notch_size=j;
    } 
  } 
  file.close();
  //error 3: invalid index
 for (int i=0; i < rot_config_size; i++){
    if (rot_map[i] < 0 || rot_map[i] > 25)
      return INVALID_INDEX;
  }

  //error 4: non-numerical character  
 for(int i=0; i < rot_config_size; i++){
   if(!isdigit(rot_map[i]))
     return NON_NUMERIC_CHARACTER;
 }

  //error 7: invalid rotor mapping
  for (int j=i-1; j>=0; j--) {
    if (rot_map[i] == rot_map[j])
      return INVALID_ROTOR_MAPPING;
  }


}

*/ 
//create new rotors

void Enigma::addRotor(char* rotFile) 
{
  
  rotors.push_back(new Rotor(rotFile));
   
}

//setting start position

int Enigma::set_startPos(char* posFile)
{
  cout<<"rotors_.size() = "<<rotors.size() << endl;

  ifstream file;
  int i = 0;
  int start_pos[26], startPos_size = 0;
  /*set start_pos*/
  file.open(posFile);
  file>>start_pos[i];
  while(!file.fail()){
    i++;
    file>>start_pos[i];
  }
  startPos_size = i;
  file.close();
  
  //error 3: invlid index
  for (int i=0; i < startPos_size; i++){
    if (start_pos[i] < 0 || start_pos[i] > 25)
      return INVALID_INDEX;
  }

  //error 8: no rotor start position
  if (startPos_size < rotors.size())
    return NO_ROTOR_STARTING_POSITION; 
 
  cout<<"start_pos[0] = "<<start_pos[0]<<endl;
  cout<<"start_pos[1] = "<<start_pos[1]<<endl;
 
  for(unsigned int count =0; count < rotors.size(); count++){
    rotors[count]->set_offset(start_pos[count]);
  }
  return 0;
}


//enigma machine encrypt 

char Enigma::encrypt(char letter)
{

  int input = letter - 'A';
  // Map through plugboard
  input = pb->connect(input);

  cout<<endl;
  cout<<endl;
  cout<<"pb output = "<<input<<endl;

  // Map through rotors forwards

  rotors[rotors.size()-1]->rotate();

  for( int i = (rotors.size()-1); i > -1; i--){
   
    if(rotors[i]->isNotch(input))
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
