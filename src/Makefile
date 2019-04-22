CC	=	g++
FLAGS	=	-g	-O2	-Wall	-Wextra

a:	sattothreesat.cpp	parser.cpp	printer.cpp	reductions.h
	${CC}	${FLAGS}	sattothreesat.cpp	parser.cpp	printer.cpp	-o	sattothreesat

all:	a

clean:
	rm	-f	sattothreesat
