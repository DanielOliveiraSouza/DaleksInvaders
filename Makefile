all:
	g++  Model_OBJ.cpp dalek.cpp  particules.cpp -o dalek  --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL -I include/
#	#g++  Model_OBJ.cpp nave.cpp -o nave --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL -I include/

debug:
	g++  Model_OBJ.cpp dalek.cpp  -o dalek particules.cpp  -g --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL  -I include/
#	#g++  Model_OBJ.cpp nave.cpp -o nave  -g --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL -I include/
 

clean:
	if test -d dalek ; 	then rm dalek ;  fi
	if test -d nave  ; 	then rm nave  ;  fi
	if test -d bala  ; 	then rm bala  ;  fi

bala:
	g++ Model_OBJ.cpp   particules.cpp Bala.cpp -o bala  -lGL -lGLU -lGLEW -lglut -lSOIL -I include/

tardis:
	g++ Model_OBJ.cpp   particules.cpp nave.cpp -o nave  -lGL -lGLU -lGLEW -lglut -lSOIL -I include/	
	
