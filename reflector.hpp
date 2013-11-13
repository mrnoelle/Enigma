#ifndef REFLECTOR_H
#define REFLECTOR_H


class Reflector 
{ 
private:
  
  int rf[26];
  int rf_length;


public:
 
  Reflector(char* rfFile);
 
  int connect(int input);

};

#endif
