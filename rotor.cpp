#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "rotor.hpp"

Rotor::Rotor()
{
  no_of_rotation=0;
  offset=0;
}

int Rotor::set(char* file)
{
  int next;
  ifstream in_stream;
  in_stream.open(file);

  if(!in_stream.fail()){
    for(int i=0; i<26; i++){
      in_stream>>next;
      rot_map[i]=next;
     
    }
    while(!in_stream.fail()){
      int j=0;
      in_stream >> next;
      rot_pos[j]=next;
      j++;
    }

    // Check that there has been no error
    // If we find an error
    //   return ERROR_CODE
  }  
  in_stream.close();
  return 0;
}

void Rotor::rotate()
{
  no_of_rotation++;

  offset=no_of_rotation%26;
  cout<<"offset="<< offset <<endl;
}


int Rotor::R_connect_L(int input)
{
  int result=( rot_map[(input+offset)%26]-offset )%26;
  while(result < 0){
    return result+26;
  }
  return result;
}

 
int Rotor::L_connect_R(int input)
{
  //cout<<"input+offset= "<< input+offset<<endl;
  for(int i=0; i<26; i++){
    if( rot_map[i]==(input+offset)%26 ){
     
      int result=i-offset;
      while(result < 0){
	return result+26;
      }
      return result; 
    }
  }
  return 0;
} 
