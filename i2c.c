/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_i2c.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/* If you declare any globals in php_i2c.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(i2c)
*/

/* True global resources - no need for thread safety here */
static int le_i2c;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("i2c.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_i2c_globals, i2c_globals)
    STD_PHP_INI_ENTRY("i2c.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_i2c_globals, i2c_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ proto long i2cget(int i2cbus, int chip_address, int data_address)
   Get a value from the chip.  */
PHP_FUNCTION(i2cget)
{
    long i2cbus;
    long chip_address;
    long data_address;
    char filename[20];
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &i2cbus, &chip_address, &data_address) != SUCCESS ) {
        return;
    }
    
    sprintf(filename, "/dev/i2c-%d", i2cbus);		
    int fd = open(filename, O_RDWR);
    
    int set_slave = ioctl(fd,I2C_SLAVE,chip_address);
    int res = i2c_smbus_read_word_data(fd, data_address);
    close(fd);        
    RETURN_LONG(res);
}
/* }}} */

/* {{{ proto long i2cset(int i2cbus, int chip_address, int data_address, int value)
   Send a value to the chip.  */
PHP_FUNCTION(i2cset)
{
    long i2cbus;
    long chip_address;
    long data_address;
    long value;
    char filename[20];
    
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "llll", &i2cbus, &chip_address, &data_address, &value) != SUCCESS ) {
        return;
    }
       
    sprintf(filename, "/dev/i2c-%d", i2cbus);		
    int fd = open(filename, O_RDWR);    
        
    int set_slave = ioctl(fd,I2C_SLAVE,chip_address);
    int res = i2c_smbus_write_word_data(fd,data_address,value); 
    close(fd);        
    RETURN_LONG(res);
}
/* }}} */

/* {{{ php_i2c_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_i2c_init_globals(zend_i2c_globals *i2c_globals)
{
	i2c_globals->global_value = 0;
	i2c_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(i2c)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(i2c)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(i2c)
{
#if defined(COMPILE_DL_I2C) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(i2c)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(i2c)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "i2c support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ i2c_functions[]
 *
 * Every user visible function must have an entry in i2c_functions[].
 */
const zend_function_entry i2c_functions[] = {	
        PHP_FE(i2cget, NULL) 
	PHP_FE(i2cset, NULL)   
        PHP_FE_END	/* Must be the last line in i2c_functions[] */
};
/* }}} */

/* {{{ i2c_module_entry
 */
zend_module_entry i2c_module_entry = {
	STANDARD_MODULE_HEADER,
	"i2c",
	i2c_functions,
	PHP_MINIT(i2c),
	PHP_MSHUTDOWN(i2c),
	PHP_RINIT(i2c),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(i2c),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(i2c),
	PHP_I2C_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_I2C
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(i2c)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
