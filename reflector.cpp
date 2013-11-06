#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "reflector.hpp"

int Reflector::set(char *file)
{
  ifstream in_stream;
  in_stream.open(file);
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
  for (int i=0; i<=25; i++){
    if(input==rf[i]){
      if(i%2==0)
	return rf[i+1];
      else if(i%2==1)
	return rf[i-1];
    }
  }
  return input;
}
