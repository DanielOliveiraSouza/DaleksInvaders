all:
	g++  lib/Model_OBJ.cpp lib/particules.cpp src/dalek.cpp   -o dalek  --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL -I include/
#	#g++  Model_OBJ.cpp nave.cpp -o nave --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL -I include/

debug:
	g++   lib/Model_OBJ.cpp lib/particules.cpp src/dalek.cpp  -o dalek  -g --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL  -I include/
#	#g++  Model_OBJ.cpp nave.cpp -o nave  -g --std=c++11 -lGL -lGLU -lGLEW -lglut -lSOIL -I include/
 

clean:
	if test -f dalek ; 	then rm dalek ;  fi
	if test -f nave  ; 	then rm nave  ;  fi
	if test -f bala  ; 	then rm bala  ;  fi

bala:
	g++ lib/Model_OBJ.cpp   lib/particules.cpp src/Bala.cpp -o bala  -lGL -lGLU -lGLEW -lglut -lSOIL -I include/

tardis:
	g++ lib/Model_OBJ.cpp   lib/particules.cpp src/nave.cpp -o nave  -lGL -lGLU -lGLEW -lglut -lSOIL -I include/	
	
