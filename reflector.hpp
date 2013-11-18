#ifndef REFLECTOR_H
#define REFLECTOR_H


class Reflector 
{ 
private:
  
  int rf[512];
  int rf_length;


public:
  int rf_status;

  Reflector(char* rfFile);
  int readfile(char* rfFile);
  int check_status();
  int connect(int input);

};

#endif
