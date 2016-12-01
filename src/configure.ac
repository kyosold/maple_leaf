#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([maple_leaf], [1.0], [kyosold@qq.com])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Set package name
AC_SUBST([PACKAGENAME], ["maple_leaf"])

# Checks for programs.
AC_PROG_CC

# Create dynamic libraries.
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strcasecmp])

AC_OUTPUT([
    Makefile
    ml_string/Makefile
    ml_hash/Makefile
    ml_hashmap/Makefile
    ml_dictionary/Makefile
    ml_log/Makefile
    ml_standard/Makefile
        ])
