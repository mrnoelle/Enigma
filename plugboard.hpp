class Plugboard
{
private:
  
  int pb[52];
  int pb_length;

public:

  Plugboard(char* file);

  int set(char* file);
  int connect(int input);

};

