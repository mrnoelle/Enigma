#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "enigma.hpp"
#include "rotor.hpp"
#include "errors.h"


Rotor::Rotor()
{
  no_of_rotation=0;
  offset=0;
}

Rotor:: Rotor(char* rotFile, char* posFile, int rotor_nb) 
{
  /*set rotor configuration and notch position*/
  int next;
  ifstream in_stream;
  in_stream.open(rotFile);

  if(!in_stream.fail()){
    for(int i=0; i<26; i++){
      in_stream>>next;
      rot_map[i]=next;
      int rot_config_size=i;
    }
  
    while(!in_stream.fail()){
      int j=0;
      in_stream >> next;
      rot_notch[j]=next;
      j++;
      int notch_size=j;
    }
   
  } 

 
 
  //cout<< notch_size <<endl;
  // cout << "notch "<< rot_notch[0] << endl; 
  in_stream.close();

  /*set start_pos*/
  in_stream.open(posFile);
  if(!in_stream.fail()){
    for(int count = 0; count < rotor_nb; count++){
      in_stream >> next;
      start_pos[count]=next;
    }
    in_stream.close();

}

void Rotor::rotate()
{
  no_of_rotation++;

  offset=no_of_rotation%26;
  cout<<"offset="<< offset <<endl;
}


int Rotor::set_notch(int input)
{
  for(int index=0; index <= notch_size; index++){
    if (  input+offset == notch[index] )
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
