CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla 
OBJECTS = piece.o grid.o textdisplay.o main.o cell.o utils.o computer.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
