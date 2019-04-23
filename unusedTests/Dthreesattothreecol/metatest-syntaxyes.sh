#! /bin/bash 
./threesattothreecol < ${TESTDIR}/syntaxyes-${1}.cnf
export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 1
else
	exit 0
fi

