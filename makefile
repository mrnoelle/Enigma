enigma: main.o plugboard.o rotor.o reflector.o
	g++ -g -Wall main.o plugboard.o rotor.o reflector.o -o enigma

main.o: main.cpp plugboard.hpp rotor.hpp reflector.hpp
	g++ -g -Wall -c main.cpp

plugboard.o: plugboard.cpp plugboard.hpp
	g++ -g -Wall -c plugboard.cpp

rotor.o: rotor.cpp rotor.hpp
	g++ -g -Wall -c rotor.cpp

reflector.o: reflector.cpp reflector.hpp
	g++ -g -Wall -c reflector.cpp
