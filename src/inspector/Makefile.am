##
## Copyright (c) Yinka Ashon 2016
##
bin_PROGRAMS=$(top_builddir)/bin/inspector

__top_builddir__bin_inspector_SOURCES= \
	file-inspector.c	    		   

#__top_builddir__bin_inspector_LDADD= $(FI_DEPS_LIBS) $(top_builddir)/lib/libdetector.la
__top_builddir__bin_inspector_LDADD= $(top_builddir)/lib/libdetector.la
__top_builddir__bin_inspector_CPPFLAGS=$(FI_DEPS_CFLAGS)
__top_builddir__bin_inspector_CFLAGS= -g -Wall -Werror -std=c99 -O0 # -pedantic
