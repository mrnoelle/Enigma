#include <iostream>
#include <fstream>

using namespace std;

#include "enigma.hpp"
#include "plugboard.hpp"
#include "errors.h"


Plugboard::Plugboard()
{

  for( int i=0; i < 104; i++)
    pb[i] = 0;
}

/* Plugboard constructor: record the status, that is error code of plugboard configuration */
Plugboard::Plugboard(char* pbFile)
{
  pb_status = readfile(pbFile);

}

/* Read plugboard configuration file and check error */
int Plugboard::readfile(char* pbFile)
{
  int i=0;
  int next;
  ifstream in_stream(pbFile);

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

    pb[i] = next;
    in_stream >> next;
    i++;

  }   
  pb_length=i;
  in_stream.close();

  /* Check [ERROR 5]: try to connect with itself or with more than one contact */
  for(int index_1 = 0; index_1 < pb_length; index_1++){
    for(int index_2 =0; index_2 < index_1; index_2++){
      if(pb[index_1] == pb[index_2])
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
  }

  /* Check [ERROR 6]: the number of parameters is not even and larger than 26 */
  if(pb_length % 2 != 0 || pb_length > 26)
    return  INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

  return NO_ERROR;
}

/* Helper function to return the error code to main */
int Plugboard::check_status(){

  return pb_status;
}

/* Mapping process in plugboard:  find the corresponding match */
int Plugboard::connect(int input)
{
  
  for (int index = 0; index < pb_length; index++){
    if(input == pb[index]){
      if(index%2 == 0)
	return pb[index + 1];
      else if(index%2 == 1)
	return pb[index - 1];
    }
  }
  return input;
}


