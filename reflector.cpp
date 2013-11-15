#include <iostream>
#include <fstream>


using namespace std;


#include "enigma.hpp"
#include "reflector.hpp"
#include "errors.h"


Reflector::Reflector(char* rfFile)
{
  rf_status = readfile(rfFile);
 
}

int Reflector::readfile(char* rfFile)
{

  ifstream in_stream;
  in_stream.open(rfFile);
  if(in_stream.fail())
    return ERROR_OPENING_CONFIGURATION_FILE;
  int i=0;
  in_stream >> rf[i];
  while (!in_stream.fail()){
    i++;   
    in_stream>>rf[i];


  }  
 
  rf_length=i;
  in_stream.close();
  return NO_ERROR;
}

int Reflector:: check_status(){

  return rf_status;
}

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
