#! /bin/bash 
export SOLVER=MiniSat_v1.14_linux

# First check that the formula is translated to a valid output

./coltosat < ${TESTDIR}/unsolvable-${1}.col | ${TESTDIR}/../bin/checksat 

export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 1
fi

# Now check that output has right result

./coltosat < ${TESTDIR}/unsolvable-${1}.col | ${TESTDIR}/../bin/${SOLVER} | grep "^UNSATISFIABLE"


export RESULT=$?

# Result type 0 means text occurred

if [[ $RESULT == 0 ]]; then 
	exit 0
else
	exit 1
fi

