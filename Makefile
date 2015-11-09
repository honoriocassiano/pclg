CXX=g++
FLAGS= -std=c++11
C_FLAGS= -c
LIBS= -lGL -lGLU -lglut -lGLEW

OBJS += \
./bin/main.o \
./bin/textfile.o \
./bin/shader/ShaderManager.o \
./bin/noise/Perlin.o

USER_OBJS += \
./src/main.cpp \
./src/textfile.cpp \
./src/shader/ShaderManager.cpp \
./src/noise/Perlin.cpp

./bin/%.o: ./src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $(C_FLAGS) -o "$@" "$<"

Main: $(OBJS) $(USER_OBJS)
	$(CXX) $(FLAGS) -o ./bin/main $(OBJS) $(LIBS)
	
all: Main clean
	
clean:
	@echo 'Cleaning workspace'
	rm ./bin/*.o
	
.PHONY= all clean