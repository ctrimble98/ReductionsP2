#! /bin/bash 
./fourcoltothreecol < ${TESTDIR}/syntaxbad-${1}.col
export RESULT=$?
if [[ $RESULT != 0 ]]; then 
	exit 0
else
	exit 1
fi

