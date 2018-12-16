objects = Book.o Main.o
book : $(objects)
	g++ --std=c++11 -o book $(objects)
Book.o : Book.h Book.cpp
Main.o : Main.cpp Book.h
clean :
	rm book $(objects)
