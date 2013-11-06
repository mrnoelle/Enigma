#include <iostream>
#include <fstream>
#include <cctype>


using namespace std;

#include "plugboard.hpp"
#include "errors.h"

int Plugboard::set(char* file)
{
  ifstream in_stream;
  in_stream.open(file);
 
  int i=0;
  in_stream >> pb[i];
  while (!in_stream.fail()){
    i++;   
    in_stream>>pb[i];
  //error 3: invalid index
  if(pb[i] < 0 || pb[i] >25)
    return INVALID_INDEX;  

//error 4: non-numerical character
if(!isdigit(pb[i]))
  return NON_NUMERIC_CHARACTER;
 
      // Check that there has been no error
      // If we find an error
      //   return ERROR_CODE
  }  
  //cout<<pb[1];
  pb_length=i;
  cout<<"pb length = "<<i<<endl;


//error 5: impossible plugboard configuration?????????????
for(int index=0; index <= pb_length; index++){

if(pb[index] == pb[index])
  return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
}

//error 6: incorrect number of parameter
if(pb_length%2 != 0)
  return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;

  in_stream.close();
  return NO_ERROR;
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


