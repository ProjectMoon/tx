#The compiler to use
CC=gcc
#Name of executable to generate
EXE=tx
#Source directory and object directory
SRC=src/
OBJ=obj/
#INSTALLDIR should always have its trailing / on the end.
INSTALLDIR=/usr/local/bin/

all: obj
	${CC} -o bin/${EXE} obj/*.o
	
dir:
	mkdir bin/
	mkdir obj/
	
obj: dir
	cd ${SRC}
	${CC} -c src/*.c
	mv *.o ${OBJ}
	
install:
	mkdir -p ${INSTALLDIR}
	install -o root -g root bin/${EXE} ${INSTALLDIR}
		
uninstall:
	rm -f ${INSTALLDIR}${EXE}
	
clean:
	rm -rf bin/ obj/
