# Test suite for library

check_PROGRAMS=test-inspector-lib-array \
	       test-inspector-lib-file-creation \
	       test-inspector-lib-file-container

TESTS=$(check_PROGRAMS)

## Array tests
test_inspector_lib_array_SOURCES=  \
	test-suite.c     \
	lib/test-array.c 

test_inspector_lib_array_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_array_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_array_CFLAGS= -g -Wall -Werror -std=c99 -O0 # -pedantic

## File container tests
test_inspector_lib_file_creation_SOURCES=  \
	test-suite.c     \
	lib/test-file-creation.c 

test_inspector_lib_file_creation_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_creation_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_creation_CFLAGS= -g -Wall -Werror -std=c99 -O0 # -pedantic
## 
test_inspector_lib_file_container_SOURCES=  \
	test-suite.c     \
	lib/test-file-container.c 

test_inspector_lib_file_container_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_container_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_container_CFLAGS= -g -Wall -Werror -std=c99 -O0 # -pedantic
