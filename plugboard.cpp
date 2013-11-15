#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <cstdlib>

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
  if(in_stream.fail())
    return ERROR_OPENING_CONFIGURATION_FILE;

  int i=0;
  int size = 3;
  int next;
 
  in_stream >> next  ;
  if(in_stream.fail()) //you read in something that is not int;
  while (!in_stream.eof()){ 
  
    cout << next <<endl;
    /*error 4: non-numerical character*/
    if(!isdigit(next))
      return NON_NUMERIC_CHARACTER; 
    a[j]=next;
    in_stream >> next ;

    /*convert to integer*/
    int num
;

    /*error 3: invalid index*/
    if(num < 0 || num > 25)
      return INVALID_INDEX; 

    pb[i] = num;
    i++;

    in_stream.getline(next, size, " ");

  }   
  pb_length=i;
  in_stream.close();

  /*error 5: impossible plugboard configuration*/
  for(int index_1 = 0; index_1 < pb_length; index_1 ++){
    for(int index_2 =0; index_2 < index_1; index_2 ++){
      if(pb[index_1] == pb[index_2])
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
  }
  /*error 6: incorrect number of parameters*/
  if(pb_length % 2 != 0)
    return  INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

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


