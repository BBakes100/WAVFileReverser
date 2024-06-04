CL = clang -Wall -g
O = main.o wav.o file_lib.o

output: main.o wav.o file_lib.o
	$(CL) $(O) -o output

main.o: main.c
	$(CL) -c main.c

wav.o: wav.c wav.h
	$(CL) -c wav.c

file_lib.o: file_lib.c file_lib.h
	$(CL) -c file_lib.c

clean: 
	rm *.o output 
