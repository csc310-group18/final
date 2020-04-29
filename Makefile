CURR_DIR 			:=  $(shell pwd | sed 's/ /\\ /g') # path to current dir
CLASSES_DIR_NAME	:= classes
DATA_DIR_NAME		:= data
CLASSES_DIR			:= $(strip $(CURR_DIR))/$(CLASSES_DIR_NAME) # strip removes trailing white space
CC					:=	g++
CFLAGS				:= -I$(CURR_DIR) -I$(CLASSES_DIR)

OBJS			:= binaryFile.o customErrorClass.o list.o

excBinaryFile: main.cpp ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}

binaryFile.o: $(strip $(CLASSES_DIR_NAME))/binaryFile.cpp $(strip $(CLASSES_DIR_NAME))/binaryFile.h
	${CC} -c -o $@ $< ${CFLAGS}

list.o: $(strip $(CLASSES_DIR_NAME))/list.cpp $(strip $(CLASSES_DIR_NAME))/list.h
	${CC} -c -o $@ $< ${CFLAGS}

customErrorClass.o: $(strip $(CLASSES_DIR_NAME))/customErrorClass.cpp $(strip $(CLASSES_DIR_NAME))/customErrorClass.h
	${CC} -c -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm *.o $(strip $(CURR_DIR))/$(DATA_DIR_NAME)/*_binary.txt excBinaryFile