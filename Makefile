CXX=g++
FLAGS= -std=c++0x
C_FLAGS= -c
LIBS= -lGL -lGLU -lglut -lGLEW

OBJS += \
./bin/main.o \
./bin/textfile.o

USER_OBJS += \
./src/main.cpp \
./src/textfile.cpp

./bin/%.o: ./src/%.cpp
	$(CXX) $(C_FLAGS) -o "$@" "$<"

Main: $(OBJS) $(USER_OBJS)
	$(CXX) $(FLAGS) -o ./bin/main $(OBJS) $(LIBS)
	
all: Main clean
	
clean:
	@echo 'Cleaning workspace'
	rm ./bin/*.o
	
.PHONY= all clean