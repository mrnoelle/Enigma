#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

#include "enigma.hpp"
#include "errors.h"

Enigma::Enigma(int no_of_rotors)
{
  //error 1: insufficient number of parameters
    plugboard pb;
    reflector rf;
    int MAX=10;
    rotor rot[MAX];
    pb.set(argv[1]);
    rf.set(argv[2]);
    /*
    for(int number=0; number <= no_of_rotors; number++){
    rot[number].set(argv[]);
    }
    */
}

char Enigma::encrypt(char input)
{
    ifstream in_stream;
    in_stream.open(argv[argc-1]);
    cin >> ws;
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
