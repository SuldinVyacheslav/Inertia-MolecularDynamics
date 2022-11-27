TARGET = simulation
COMPILER = g++

PREV_OBJ = ./obj/

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(PREV_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(COMPILER) $(OBJ) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

$(PREV_OBJ)%.o : %.cpp
	$(COMPILER) -c $< -o $@

clean : 
	rm $(TARGET) $(PREV_OBJ)*.o