dnl $Id$
dnl config.m4 for extension i2c

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(i2c, for i2c support,
dnl Make sure that the comment is aligned:
dnl [  --with-i2c             Include i2c support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(i2c, whether to enable i2c support,
dnl Make sure that the comment is aligned:
[  --enable-i2c           Enable i2c support])

if test "$PHP_I2C" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-i2c -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/i2c.h"  # you most likely want to change this
  dnl if test -r $PHP_I2C/$SEARCH_FOR; then # path given as parameter
  dnl   I2C_DIR=$PHP_I2C
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for i2c files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       I2C_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$I2C_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the i2c distribution])
  dnl fi

  dnl # --with-i2c -> add include path
  dnl PHP_ADD_INCLUDE($I2C_DIR/include)

  dnl # --with-i2c -> check for lib and symbol presence
  dnl LIBNAME=i2c # you may want to change this
  dnl LIBSYMBOL=i2c # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $I2C_DIR/$PHP_LIBDIR, I2C_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_I2CLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong i2c lib version or lib not found])
  dnl ],[
  dnl   -L$I2C_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(I2C_SHARED_LIBADD)

  PHP_NEW_EXTENSION(i2c, i2c.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
