#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard
{
private:
  
  int pb[512];
  int pb_length;

public:
  int pb_status;

  Plugboard();
  Plugboard(char* pbFile);
  int readfile(char* pbFile);
  int check_status();
  int connect(int input);

};

#endif
