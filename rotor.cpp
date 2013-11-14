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


Rotor:: Rotor(char* rotFile) {

  rot_status =  readfile(rotFile);

}


int Rotor:: readfile(char* rotFile) 
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

  in_stream.close();
  //error 3: invalid index
  for (int i=0; i < rot_config_size; i++){
    if (rot_map[i] < 0 || rot_map[i] > 25)
      return INVALID_INDEX;
  }

}



int Rotor::check_status(){

  return rot_status;
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

bool Rotor::isNotch()
{
  cout<<"notch_size = "<< notch_size <<endl;
  for(int index=0; index <= notch_size; index++){
    if (  offset == rot_notch[index] )
      return true;
  }

  return false;

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
