CC	=	g++
FLAGS	=	-g	-O2	-Wextra

all:	sattothreesat	coltosat	threesattocol	circularreduction

sattothreesat:	sattothreesat.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	sattothreesat.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	sattothreesat

coltosat:	coltosat.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	coltosat.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	coltosat

threesattocol:	threesattocol.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	threesattocol.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	threesattocol

circularreduction:	circularreduction.cpp	parser.cpp	printer.cpp	reductions.cpp	reductions.h
	${CC}	${FLAGS}	circularreduction.cpp	reductions.cpp	parser.cpp	printer.cpp	-o	circularreduction

clean:
	rm	-f	sattothreesat	coltosat	threesattocol
