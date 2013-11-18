#include <iostream>
#include <fstream>

using namespace std;

#include "enigma.hpp"
#include "reflector.hpp"
#include "errors.h"


/*Reflector constructor: record the status, that is error code of reflector configuration*/
Reflector::Reflector(char* rfFile)
{

  rf_status = readfile(rfFile); 
}

/*Read reflector configuration file and check error*/
int Reflector::readfile(char* rfFile)
{
  int i=0;
  int next;
  ifstream in_stream(rfFile);

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
    
    rf[i] = next;
    in_stream >> next;
    i++;

  }   
  rf_length=i;
  in_stream.close();

  /*Check [ERROR 10]: the number of parameters is not 26*/
  if(rf_length != 26)
    return  INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;

  /*Check [ERROR 9]: try to map to itself or with more than one other*/
  for(int index_1 = 0; index_1 < 26; index_1++){
    for(int index_2 =0; index_2 < index_1; index_2++){
      if(rf[index_1] == rf[index_2])
	return INVALID_REFLECTOR_MAPPING;
    }
  }

  return NO_ERROR;
}

/*Helper function to return the error code to main*/
int Reflector:: check_status()
{

  return rf_status;
}

/*Mapping process in reflector: find the corresponding match*/
int Reflector::connect(int input)
{
  for (int index=0; index < rf_length; index++){
    if(input==rf[index]){
      if(index%2==0)
	return rf[index+1];
      else if(index%2==1)
	return rf[index-1];
    }
  }
  return input;
}
