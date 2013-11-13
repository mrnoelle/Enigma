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
  ifstream in_stream;
  in_stream.open(pbFile);
  int i=0;
  int pb_length=0;
  in_stream >> pb[i];
  while (!in_stream.fail()){
    i++;   
    in_stream>>pb[i];
  }  
  // cout<<"pb = "<<pb[0]<<" "<<pb[1]<<endl;
  pb_length=i;
  cout<<"pb length = "<<i<<endl;

  in_stream.close();
 
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


