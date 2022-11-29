TARGET = test

PREV_OBJ = ./obj/

SRC = $(filter-out ../Visualization.cpp ../main.cpp ../Graph.cpp, $(wildcard ../*.cpp))
OBJ = $(patsubst ../%.cpp, $(PREV_OBJ)%.o, $(SRC))

${TARGET} : Test.o ${OBJ}
	echo $(OBJ)
	g++ Test.o ${OBJ} -o ${TARGET} -lgtest -lgtest_main -lpthread

Test.o : Test.cpp
	g++ -c Test.cpp -o  Test.o

$(PREV_OBJ)%.o : ../%.cpp
	g++ -c  $< -o $@

clean : 
	rm $(TARGET) $(PREV_OBJ)*.o Test.o