CC	=	g++
FLAGS	=	-g	-O2	-Wall	-Wextra

sattothreesat:	sattothreesat.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	sattothreesat.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	sattothreesat

coltosat:	coltosat.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	coltosat.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	coltosat

threesattocol:	threesattocol.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	threesattocol.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	threesattocol


all:	sattothreesat	coltosat	threesattocol

clean:
	rm	-f	sattothreesat	coltosat	threesattocol
