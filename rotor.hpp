#ifndef ROTOR_H
#define ROTOR_H


class Rotor
{
private:
  
  int rot_map[512];
  int rot_notch[512];
  int offset;
  int notch_size;
  bool notch_checked;
  
public:
  
  int rotor_nb;
  int rot_status;
  
 
  Rotor();
  Rotor(char* rotFile);  
  int readfile(char* rotFile); 
  int check_status();
  void rotate();
  bool is_notch_check();
  void set_offset(int position);
  int connect_forwards(int input);
  int connect_backwards(int input);
  
 
};

#endif
