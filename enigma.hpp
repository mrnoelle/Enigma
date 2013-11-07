class Enigma
{

private:
  Plugboard &pb;
  Reflector &rf;
  Rotor &rot[MAX];

  int status;

public:
  Enigma(int no_of_rotors);
  char encrypt(char input);


};
