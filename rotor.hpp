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
  int start_pos[26];

  int no_of_rotation;
  int offset;


public:
  Rotor();
  Rotor(char* rotFile, char* posFile, int rotor_nb); 
 
  void rotate();
  int connect_forwards(int input);
  int connect_backwards(int input);
  int set_notch(int input);

};

#endif
