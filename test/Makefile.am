# Test suite for library

TEST_CFLAGS= -g -Wall -Werror -std=c99

check_PROGRAMS=test-inspector-lib-array \
	       test-inspector-lib-file-creation \
	       test-inspector-lib-file-container \
	       test-inspector-lib-file-manager \
	       test-inspector-lib-list-traversing \
	       test-inspector-lib-conflict-list-iteration \
	       test-inspector-lib-conjoined-string \
	       test-inspector-lib-util-string

TESTS=$(check_PROGRAMS)

## Array tests
test_inspector_lib_array_SOURCES=  \
	test-suite.c     \
	lib/test-array.c 

test_inspector_lib_array_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_array_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_array_CFLAGS=$(TEST_CFLAGS)

## List tests
test_inspector_lib_list_traversing_SOURCES=  \
	test-suite.c     \
	lib/test-list-iteration.c 

test_inspector_lib_list_traversing_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_list_traversing_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_list_traversing_CFLAGS=$(TEST_CFLAGS)

## File container tests
test_inspector_lib_file_creation_SOURCES=  \
	test-suite.c     \
	lib/test-file-creation.c 

test_inspector_lib_file_creation_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_creation_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_creation_CFLAGS=$(TEST_CFLAGS)
## 
test_inspector_lib_file_container_SOURCES=  \
	test-suite.c     \
	lib/test-file-container.c 

test_inspector_lib_file_container_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_container_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_container_CFLAGS=$(TEST_CFLAGS)

## Strings function unit tests
test_inspector_lib_util_string_SOURCES=  \
	test-suite.c     \
	lib/test-util-string.c 

test_inspector_lib_util_string_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_util_string_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_util_string_CFLAGS=$(TEST_CFLAGS)

## Extended Strings function unit tests
test_inspector_lib_conjoined_string_SOURCES=  \
	test-suite.c     \
	lib/test-conjoined-string.c 

test_inspector_lib_conjoined_string_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_conjoined_string_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_conjoined_string_CFLAGS=$(TEST_CFLAGS)

## File manager
test_inspector_lib_file_manager_SOURCES=  \
	test-suite.c     \
	lib/test-file-manager.c 

test_inspector_lib_file_manager_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_file_manager_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_file_manager_CFLAGS=$(TEST_CFLAGS)

## File conflict unit tests
test_inspector_lib_conflict_list_iteration_SOURCES=  \
	test-suite.c     \
	lib/test-conflict-list-iteration.c 

test_inspector_lib_conflict_list_iteration_LDADD= $(top_builddir)/lib/libdetector.la
test_inspector_lib_conflict_list_iteration_CPPFLAGS=$(FI_DEPS_CFLAGS)
test_inspector_lib_conflict_list_iteration_CFLAGS=$(TEST_CFLAGS)
