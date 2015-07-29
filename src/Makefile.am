#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libjsonrpcc.la libjsonrpcccli.la

#######################################
# Build information for each library

# library jsonrpcc
# Sources for jsonrpcc
libjsonrpcc_la_SOURCES = cJSON.c jsonrpc-c.c

# Linker options libTestProgram
libjsonrpcc_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libjsonrpcc_la_CPPFLAGS = $(LIBEV_CFLAGS) -I$(top_srcdir)/include

# libev
libjsonrpcc_la_LIBADD = $(LIBEV_LIBS)

# library jsonrpccli
# Sources for jsonrpcc
libjsonrpcccli_la_SOURCES = cJSON.c jsonrpc-ccli.c

# Linker options libTestProgram
libjsonrpcccli_la_LDFLAGS = -lm

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libjsonrpcccli_la_CPPFLAGS = $(LIBEV_CFLAGS) -I$(top_srcdir)/include

# libev
libjsonrpcccli_la_LIBADD = $(LIBEV_LIBS)
