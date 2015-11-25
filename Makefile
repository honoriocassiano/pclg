CXX=g++
FLAGS= -std=c++11 -Wall
C_FLAGS= -c
LIBS= -lGL -lGLU -lglut -lGLEW -lm

OBJS += \
./bin/main.o \
./bin/textfile.o \
./bin/shader/ShaderManager.o \
./bin/noise/Perlin.o \
./bin/sky/Surface.o \
./bin/sky/SkyDome.o \
./bin/camera/Camera.o


USER_OBJS += \
./src/main.cpp \
./src/textfile.cpp \
./src/shader/ShaderManager.cpp \
./src/noise/Perlin.cpp \
./src/sky/Surface.cpp \
./src/sky/SkyDome.cpp \
./src/camera/Camera.cpp

./bin/%.o: ./src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) $(C_FLAGS) -o "$@" "$<"

Main: $(OBJS) $(USER_OBJS)
	$(CXX) $(FLAGS) -o ./pclg $(OBJS) $(LIBS)
	
all: Main
	
clean: $(OBJS)
	@echo 'Cleaning workspace'
	rm $(OBJS)
	
.PHONY= all clean