#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "enigma.hpp"
#include "rotor.hpp"
#include "errors.h"


Rotor::Rotor()
{
  
  offset=0;
}


Rotor:: Rotor(char* rotFile) 
{

  /*set rotor configuration and notch position*/
  int next;
  ifstream in_stream;
  in_stream.open(rotFile);
  int rot_config_size=0;
  notch_size=0;
  if(!in_stream.fail()){
    for(int i=0; i<26; i++){
      in_stream>>next;
      rot_map[i]=next;
      rot_config_size=i;
    }
   

    while(!in_stream.fail()){
      int j=0;
      in_stream >> next;
      rot_notch[j]=next;
      j++;
      notch_size=j;
    }
   
 
  } 
  /*
  //check that index is valid
  for (int i=0; i < 26; i++){

    if (rot_map[i] < 0 || rot_map[i] > 25)
      return INVALID_INDEX;
  }

  //check no two identical entries
  for (int j=i-1; j>=0; j--) {
    if (rot_map[i] == rot_map[j])
      return INVALID_ROTOR_MAPPING;
  }
  */
  cout<<"rot_config_size = "<<rot_config_size<<endl;
 
  cout<<"notch_size = "<< notch_size <<endl;
  
  cout<<"rot_notch[0]= "<<rot_notch[0]<<endl; 

  in_stream.close();

}



void Rotor::rotate()
{
  offset++;

  offset=offset%26;

  cout<<"offset= "<< offset <<endl;
}



//set start position
void Rotor::set_offset(int position)
{
  ;  offset=position;

}

bool Rotor::isNotch(int input)
{
  cout<<"notch_size = "<< notch_size <<endl;
  for(int index=0; index <= notch_size; index++){
    if (  input+offset == rot_notch[index] )
      return 1;
  }

  return 0;

}


int Rotor::connect_forwards(int input)
{

  int result=( rot_map[(input+offset)%26]-offset )%26;
  while(result < 0){
    return result+26;
  }
  return result;
}

 
int Rotor::connect_backwards(int input)
{
  //cout<<"input+offset= "<< input+offset<<endl;
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
