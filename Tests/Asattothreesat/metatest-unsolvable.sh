#! /bin/bash 
export SOLVER=MiniSat_v1.14_linux

# First check that the formula is translated to a valid output

./sattothreesat < ${TESTDIR}/unsolvable-${1}.cnf | ${TESTDIR}/../bin/check3sat 

export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 1
fi


# Now check that output has right result

./sattothreesat < ${TESTDIR}/unsolvable-${1}.cnf | ${TESTDIR}/../bin/${SOLVER} | grep "^UNSATISFIABLE"


export RESULT=$?

# Result type 0 means text occurred

if [[ $RESULT == 0 ]]; then 
	exit 0
else
	exit 1
fi

