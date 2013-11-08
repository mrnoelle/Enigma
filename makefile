enigma: main.o plugboard.o rotor.o reflector.o enigma.o errors.h
	g++ -g -Wall main.o plugboard.o rotor.o reflector.o enigma.o -o enigma

main.o: main.cpp plugboard.hpp rotor.hpp reflector.hpp enigma.hpp errors.h
	g++ -g -Wall -c main.cpp

plugboard.o: plugboard.cpp plugboard.hpp errors.h enigma.hpp
	g++ -g -Wall -c plugboard.cpp

rotor.o: rotor.cpp rotor.hpp errors.h enigma.hpp
	g++ -g -Wall -c rotor.cpp

reflector.o: reflector.cpp reflector.hpp errors.h enigma.hpp
	g++ -g -Wall -c reflector.cpp

enigma.o: enigma.cpp plugboard.hpp rotor.hpp reflector.hpp errors.h 
	g++ -g -Wall -c enigma.cpp

