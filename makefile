all: tlcc tlcc_o

tlcc: main.o
		gcc -o ./workdir/tlcc main.o
tlcc_o:	main_optimized.o
		gcc -o ./workdir/tlcc_o main_optimized.o
main.o: main.c
		gcc -c main.c
main_optimized.o:	main_optimized.c
		gcc -c main_optimized.c

clean:	
		rm ./workdir/tlcc
		rm ./workdir/tlcc_o
