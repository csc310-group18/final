INCLUDE_DIR 	:=  $(shell pwd | sed 's/ /\\ /g') # path to current dir
CC				:=	g++
CFLAGS			:= -I$(INCLUDE_DIR)

OBJS			:= binaryFile.o customErrorClass.o list.o

excBinaryFile: main.cpp ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

binaryFile.o: binaryFile.cpp binaryFile.h
	${CC} -c -o $@ $< ${CFLAGS}

list.o: list.cpp list.h
	${CC} -c -o $@ $< ${CFLAGS}

customErrorClass.o: customErrorClass.cpp customErrorClass.h
	${CC} -c -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm *.o *_binary.txt excBinaryFile