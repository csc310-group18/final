INCLUDE_DIR 	:=  /home/user/Desktop/FinalProject
CC				:=	g++
CFLAGS			:= -I$(INCLUDE_DIR)

OBJS			:= binaryFile.o customErrorClass.o

excBinaryFile: main.cpp ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

binaryFile.o: binaryFile.cpp binaryFile.h
	${CC} -c -o $@ $< ${CFLAGS}

customErrorClass.o: customErrorClass.cpp customErrorClass.h
	${CC} -c -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm *.o excBinaryFile