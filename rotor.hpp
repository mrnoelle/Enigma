class Rotor
{

 private:
  
  int rot_map[26];
  int rot_notch[26];
  int rot_pos[26];

  int no_of_rotation;
  int offset;

 


public:
  Rotor();
  Rotor(char* file);
  void rotate();
  int R_connect_L(int input);
  int L_connect_R(int input);


};
