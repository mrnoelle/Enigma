#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "enigma.hpp"
#include "rotor.hpp"
#include "errors.h"

/*Default constructor: set the start position at 'A'*/
Rotor::Rotor()
{ 
  offset=0;

}


/*Rotor constuctor: record the status, that is the error code of rotor configuration*/
Rotor:: Rotor(char* rotFile) 
{
  rot_status =  readfile(rotFile);

}

/*Read rotor configuration file, set up for both mapping and notch position, and check error*/
int Rotor:: readfile(char* rotFile) 
{ 

  int i=0;
  int j=0;
  int next;
  ifstream in_stream(rotFile);

  /*Check [ERROR 11]: open configuration file failed*/
  if(in_stream.fail())
    return ERROR_OPENING_CONFIGURATION_FILE;

  in_stream >> next;
  while (!in_stream.eof()){ 
    /*Check [ERROR 4]: read in something that is not an integer*/
    if(in_stream.fail())
      return NON_NUMERIC_CHARACTER; 

    /*Check [ERROR 3]: the number is not between 0 and 25*/
    if(next < 0 || next > 25)
      return INVALID_INDEX; 

    rot_map[i] = next;
    in_stream >> next;
    i++;
  }   
  rot_length=i;
  in_stream.close();

  /*Check [ERROR 7]: do not provide enough mapping*/
  if( rot_length < 26 )
    return INVALID_ROTOR_MAPPING;
 
  /*Check [ERROR 7]: try to connect with itself or with more than one contact, only check the number between rot_map[0] and rot_map[25], since the remaing are notch positions*/
  for(int index_1 = 0; index_1 < 26; index_1++){
    for(int index_2 =0; index_2 < index_1; index_2++){
      if(rot_map[index_1] == rot_map[index_2])
	return INVALID_ROTOR_MAPPING;
    }
  }

  /*Store the notch posion into another array*/ 
  for(j=0; j+26 < rot_length; j++){
    rot_notch[j] = rot_map[j+26];
  }
  notch_size = j;
  

  return NO_ERROR;

}



int Rotor::check_status(){

  return rot_status;
}


void Rotor::rotate()
{
  offset++;
  offset = offset%26;
  cout <<"   offset   "<<offset<<endl;

}



//set start position
void Rotor::set_offset(int position)
{

  offset=position;
}

bool Rotor::isNotch()
{
  
  for(int index=0; index < notch_size; index++){
    if (  offset == rot_notch[index] ){
      cout << "is notch" << endl;
    return true;
   
    }
  }

  return false;

}


int Rotor::connect_forwards(int input)
{
  
  int result= ( rot_map[(input+offset)%26]-offset )%26;
  if(result < 0){
    return result+26;
  }
  return result;
}

 
int Rotor::connect_backwards(int input)
{
  
  for(int index = 0; index < 26; index++){
    if( rot_map[index]==(input+offset)%26 ){
     
      int result=index-offset;
      while(result < 0){
	return result+26;
      }
      return result; 
    }
  }
  return 0;
} 
