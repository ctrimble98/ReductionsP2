#! /bin/bash 
./coltosat < ${TESTDIR}/syntaxyes-${1}.col
export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 1
else
	exit 0
fi

