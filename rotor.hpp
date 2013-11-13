#ifndef ROTOR_H
#define ROTOR_H

/*
class Rotor : public Component {
        int map_[26];
        bool isBackwards_;
        int rotateCount_;
        void printRotor();
        int mapForwards(int c);
        int mapBackwards(int c);

        public:
                Rotor(char* rotFile);
                int map(int c);
                bool rotate();
};

*/

class Rotor
{
private:
  
  int rot_map[26];
  int rot_notch[26];
 
  
  int offset;


public:
  int notch_size;
  int rot_status;
  Rotor();
  Rotor(char* rotFile); 
 
  int readfile(char* rotFile); 
  int check_status();

  void rotate();
  void set_offset(int position);
  bool isNotch(int input);
  int connect_forwards(int input);
  int connect_backwards(int input);
  
 
};

#endif
