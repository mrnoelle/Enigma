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
  int next;
  if(!in_stream.fail()){
    for(int i=0; i<=25; i++){
      in_stream>>next;
      rf[i]=next;
     
    }
   
  }  
  //cout<<"rf[25]= "<<rf[25]<<endl;
  in_stream.close();
  
}

int Reflector:: check_status(){

  return rf_status;

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
