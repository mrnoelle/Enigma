#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard
{
private:
  
  int pb[52];
  int pb_length;

public:
  
  Plugboard(char* pbFile);
  int connect(int input);

};

#endif
