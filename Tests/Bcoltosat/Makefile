all: syntaxbad syntaxyes solutions nonsols

SYNTAXBAD=duplicates noedgeline toomanyedges nocolline notenoughedges badedgeline
SYNTAXYES=fourcol threecol
SOLVABLE=fourcol threecol
UNSOLVABLE=threecol twocol
SYNTAXBAD_FILES=${patsubst %,test-syntaxbad-%.sh,${SYNTAXBAD}}
SYNTAXYES_FILES=${patsubst %,test-syntaxyes-%.sh,${SYNTAXYES}}
SOLUTION_FILES=${patsubst %,test-solution-%.sh,${SOLVABLE}}
NONSOL_FILES=${patsubst %,test-unsolvable-%.sh,${UNSOLVABLE}}

test-syntaxbad-%.sh: syntaxbad-%.col
	echo "#!/bin/bash" > $@
	echo 'bash $${TESTDIR}/metatest-syntaxbad.sh $*' >> $@
	chmod a+x $@

syntaxbad: ${SYNTAXBAD_FILES}

test-syntaxyes-%.sh: syntaxyes-%.col
	echo "#!/bin/bash" > $@
	echo 'bash $${TESTDIR}/metatest-syntaxyes.sh $*' >> $@
	chmod a+x $@

syntaxyes: ${SYNTAXYES_FILES}

test-solution-%.sh: solution-%.col
	echo "#!/bin/bash" > $@
	echo 'bash $${TESTDIR}/metatest-solution.sh $*' >> $@
	chmod a+x $@

solutions: ${SOLUTION_FILES}

test-unsolvable-%.sh: unsolvable-%.col
	echo "#!/bin/bash" > $@
	echo 'bash $${TESTDIR}/metatest-unsolvable.sh $*' >> $@
	chmod a+x $@

nonsols: ${NONSOL_FILES}

