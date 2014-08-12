AC_PREREQ(2.57)
AC_INIT(libudnspp, 0.4.1, info@ossapp.com)
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE(foreign tar-pax)
AC_CONFIG_SRCDIR([src/udnspp/dnsresolver.cpp])
AM_CONFIG_HEADER([src/config.h])
AC_PROG_LIBTOOL
AC_CHECK_LIB(boost_thread, main, [BOOST_LIBS=" -lboost_system -lboost_thread "],
    [AC_CHECK_LIB(boost_thread-mt, main,
    [BOOST_LIBS=" -lboost_system-mt -lboost_thread-mt "],
    [AC_MSG_ERROR("no boost thread found")])])
    
   
AC_SUBST(BOOST_LIBS)
AC_PATH_PROG([BASH], [bash])
AC_PROG_CXX
AX_COMPILER_VENDOR
AC_PROG_CC

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  include/Makefile
])

AC_OUTPUT
