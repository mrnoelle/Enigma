#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
using namespace std;

#include "enigma.hpp"
#include "plugboard.hpp"
#include "errors.h"


Plugboard::Plugboard(char* pbFile)
{
  pb_status = readfile(pbFile);

}


int Plugboard::readfile(char* pbFile)
{
  ifstream in_stream;
  in_stream.open(pbFile);
 
  int i=0;
  in_stream >> pb[i];
  while (!in_stream.fail()){
    i++;   
    in_stream>>pb[i];


  }  
 
  pb_length=i;
  in_stream.close();
  
  //error 4: non-numerical character
  for(int index=0; index < pb_length; index++){
    if(!isdigit(pb[index]))
      return NON_NUMERIC_CHARACTER;
  }
  
  //error 3: invalid index
  for(int index=0; index < pb_length; index++){
    if(pb[index] < 0 || pb[index] >25)
      return INVALID_INDEX; 
  }
  //error 5: impossible plugboard configuration
  for(int index_1 = 0; index_1 < pb_length; index_1 ++){
    for(int index_2 =0; index_2 < index_1; index_2 ++){
      if(pb[index_1] == pb[index_2])
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
  }
  return NO_ERROR;
}

int Plugboard::check_status(){

  return pb_status;
}



int Plugboard::connect(int input)
{
  
  for (int index=0; index <= pb_length; index++){
    if(input==pb[index]){
      if(index%2==0)
	return pb[index+1];
      else if(index%2==1)
	return pb[index-1];
    }
  }
  return input;
}


