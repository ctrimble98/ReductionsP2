#! /bin/bash 
export SOLVER=kColSolve/kColSolve

# First check that the formula is translated to a valid output

./threesattocol < ${TESTDIR}/unsolvable-${1}.cnf | ${TESTDIR}/../bin/checkcol 

export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 1
fi

# Now check that output has right result

./threesattocol < ${TESTDIR}/unsolvable-${1}.cnf | ${TESTDIR}/../bin/${SOLVER} | grep "^SolverSolutionsFound:0"

export RESULT=$?

# Result type 0 means text occurred

if [[ $RESULT == 0 ]]; then 
	exit 0
else
	exit 1
fi

