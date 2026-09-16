#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libvsgpt/.libs/libvsgpt.1.dylib" ] && [ -f ./pyvsgpt/.libs/pyvsgpt.so ]
then
    install_name_tool -change /usr/local/lib/libvsgpt.1.dylib "${PWD}/libvsgpt/.libs/libvsgpt.1.dylib" ./pyvsgpt/.libs/pyvsgpt.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

