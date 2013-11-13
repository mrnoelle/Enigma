#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

#include "enigma.hpp"
#include "errors.h"
#include "rotor.hpp"
#include "plugboard.hpp"
#include "reflector.hpp"


Enigma::Enigma(char* pbFile, char* rfFile)
{
  status = 0;
  pb = new Plugboard(pbFile);
  int pb_result = pb->check_status();
  if(pb_result>0){
    status = pb_result;
  }

  else if (rf = new Reflector(rfFile)){
    int rf_result = rf->check_status();
    if(rf_result>0){
      status = rf_result;
    }
  }
}





Enigma::~Enigma()
{
  delete pb;
  delete rf;
  
 
  for( int i=0; i < rotors.size(); i++)
    delete rotors[i];

}


int Enigma::check_status()
{

  return status;
}

 
//create new rotors

void Enigma::addRotor(char* rotFile) 
{
  
  rotors.push_back(new Rotor(rotFile));
  //int result = rot
 

  
}

//setting start position

void Enigma::set_startPos(char* posFile)
{
  cout<<"rotors_.size() = "<<rotors.size() << endl;

  ifstream in_stream;
  int next;
  int startPos_size;
  /*set start_pos*/
  in_stream.open(posFile);
  if(!in_stream.fail()){
    for(int count = 0; count < 26; count++){
      in_stream >> next;
      start_pos[count]=next;
      startPos_size = count;
    }
  
  }
  /*
  //check that index is valid
  for (int i=0; i < 26; i++){

    if (start_pos[i] < 0 || start_pos[i] > 25)
      status(3);
  }
  //check starting positions for rotors
  if (startPos_size < rotors_.size())
    status(8); 
*/
  cout<<"start_pos[0] = "<<start_pos[0]<<endl;
  cout<<"start_pos[1] = "<<start_pos[1]<<endl;

  in_stream.close();

  for(int count =0; count < rotors.size(); count++){
    rotors[count]->set_offset(start_pos[count]);
  }

}


//enigma machine encrypt 

char Enigma::encrypt(char letter)
{

  int input = letter - 'A';
  // Map through plugboard
  input = pb->connect(input);

  cout<<endl;
  cout<<endl;
  cout<<"pb output = "<<input<<endl;

  // Map through rotors forwards

  rotors[rotors.size()-1]->rotate();

  cout<<"rotors.size() ="<<rotors.size()<<endl;

  for( int i = (rotors.size()-1); i > -1; i--){
   
    cout<<"notch loop "<<rotors[i]->isNotch(input)<<endl; 
   
    if(rotors[i]->isNotch(input))
      rotors[i-1]->rotate();

  }

  cout<<"isNotch = "<<rotors[0]->isNotch(input)<<endl;

  for( int i = (rotors.size()-1); i > -1; i--){
    input = rotors[i]->connect_forwards(input);
  }

  cout<<"rotor output= "<<input<<endl;


  // Map through reflector
  input = rf->connect(input);

  cout<<"rf output= "<<input<<endl;

  // Map through rotors backwards
  for( int i=0; i < rotors.size(); i++){
 
    input = rotors[i]->connect_backwards(input);
  }

  cout<<"rotor backwards output= "<<input<<endl;

  // Map through plugboard
  input = pb->connect(input);

  char result= input + 'A';

  cout<<"result= "<<result<<endl;

  return result ;
  cout<< endl;

}








/*
Enigma::Enigma(int no_of_rotors, char* pbFile) : pb(pbFile)
{
  //error 1: insufficient number of parameters
  reflector rf;
  int MAX=10;
  rotor rot[MAX];
  

  // pb.set(pbFile);
  rf.set(argv[2]);

    for(int number=0; number <= no_of_rotors; number++){
    rot[number].set(argv[]);
    }
 

  if (error) status = error
}

char Enigma::encrypt(char input)
{
  cin >> input;
  if(isupper(input)){
    int integer = input - 'A';
    integer = pb.connect(integer);
    //rotor encrypt
    
    integer = rf.connect(integer);
    integer = pb.connet(integer);
    char letter = integer + 'A';
    return letter;
  }
  else return INVALID_INPUT_CHARACTER;
}


void link_rotor(int no_of_rotors, int set_notch)
*/
