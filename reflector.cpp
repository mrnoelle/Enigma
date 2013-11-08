#include <iostream>
#include <fstream>


using namespace std;


#include "enigma.hpp"
#include "reflector.hpp"
#include "errors.h"

int Reflector::set(char *rfFile)
{
  ifstream in_stream;
  in_stream.open(rfFile);
  int next;
  if(!in_stream.fail()){
    for(int i=0; i<=25; i++){
      in_stream>>next;
      rf[i]=next;
    }
  }  
  in_stream.close();
  return 0;
}

int Reflector::connect(int input)
{
  for (int index=0; index < 26; index++){
    if(input==rf[index]){
      if(index%2==0)
	return rf[index+1];
      else if(index%2==1)
	return rf[index-1];
    }
  }
  return input;
}
