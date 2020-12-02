#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libvsgpt/.libs/libvsgpt.1.dylib && test -f ./pyvsgpt/.libs/pyvsgpt.so;
then
	install_name_tool -change /usr/local/lib/libvsgpt.1.dylib ${PWD}/libvsgpt/.libs/libvsgpt.1.dylib ./pyvsgpt/.libs/pyvsgpt.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

