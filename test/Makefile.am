# Test suite for library

check_PROGRAMS=test-inspector-lib-array \
	       test-inspector-lib-file-creation \
	       test-inspector-lib-file-container \
	       test-inspector-lib-util-string

TESTS=$(check_PROGRAMS)

## Array tests
test_inspector_lib_array_SOURCES=  \
	test-suite.c     \
	lib/test-array.c 

test_inspector_lib_array_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_array_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_array_CFLAGS= -g -Wall -Werror -std=c99

## File container tests
test_inspector_lib_file_creation_SOURCES=  \
	test-suite.c     \
	lib/test-file-creation.c 

test_inspector_lib_file_creation_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_creation_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_creation_CFLAGS= -g -Wall -Werror -std=c99
## 
test_inspector_lib_file_container_SOURCES=  \
	test-suite.c     \
	lib/test-file-container.c 

test_inspector_lib_file_container_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_container_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_container_CFLAGS= -g -Wall -Werror -std=c99

## Strings function unit tests
test_inspector_lib_util_string_SOURCES=  \
	test-suite.c     \
	lib/test-util-string.c 

test_inspector_lib_util_string_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_util_string_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_util_string_CFLAGS= -g -Wall -Werror -std=c99
