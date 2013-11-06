#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "plugboard.hpp"

int Plugboard::set(char* file)
{
  ifstream in_stream;
  in_stream.open(file);
 
  int i=0;
  in_stream >> pb[i];
  while (!in_stream.fail()){
    i++;   
    in_stream>>pb[i];
     
   
      // Check that there has been no error
      // If we find an error
      //   return ERROR_CODE
  }  
  //cout<<pb[1];
  pb_length=i;
  cout<<"pb length = "<<i<<endl;
  in_stream.close();
  return 0;
}

int Plugboard::connect(int input)
{
  cout<<input<<endl;
  for (int j=0; j <= pb_length; j++){
    if(input==pb[j]){
      if(j%2==0)
	return pb[j+1];
      else if(j%2==1)
	return pb[j-1];
    }
  }
  return input;
}


