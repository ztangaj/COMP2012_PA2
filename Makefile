all: pa2.exe

pa2.exe: main.o buddy.o dining.o workout.o
	g++ -o pa2.exe main.o buddy.o dining.o workout.o

main.o: main.cpp buddy.h dining.h workout.h schedule.h
	g++ -c main.cpp

buddy.o: buddy.cpp buddy.h dining.h workout.h schedule.h
	g++ -c buddy.cpp 
	
dining.o: dining.cpp dining.h
	g++ -c dining.cpp

workout.o: workout.cpp workout.h
	g++ -c workout.cpp 

clean:
	rm -rf *.o
	rm -rf *.exe