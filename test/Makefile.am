# Test suite for library

check_PROGRAMS=test-inspector-lib-array

TESTS=$(check_PROGRAMS)

test_inspector_lib_array_SOURCES=  \
	test-suite.c     \
	lib/test-array.c

test_inspector_lib_array_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_array_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_array_CFLAGS= -g -Wall -Werror -std=c99 -O0 # -pedantic
