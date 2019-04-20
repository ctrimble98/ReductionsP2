#! /bin/bash 
./threesattothreecol < ${TESTDIR}/syntaxbad-${1}.cnf
export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 0
else
	exit 1
fi

