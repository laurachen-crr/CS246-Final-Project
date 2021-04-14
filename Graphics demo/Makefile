CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla 
OBJECTS = window.o graphicsdemo.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = graphics

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
