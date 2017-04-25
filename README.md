# i2c
I created this extension so that PHP on a Raspberry Pi can directly interact with a microcontroller using I2C.  It is not a complete extension, it just implements the methods that I need in my project.  

I have created this by using the source code from https://github.com/groeck/i2c-tools .  If you want extra functionality it's a relatively straight forward task to adapt code from there.

To use this you will need a copy of the PHP source code.  You also need autoconf, bison, libxml2-dev and libi2c-dev installed.

The most basic steps to get this installed are:

git clone git://github.com/php/php-src
cd php-src/ext
git clone git://gtihub.com/samjking/i2c
cd ..
./buildconf --force
./configure --enable-i2c
make
make install

or to install it as an add on extension to PHP

cd php-src/ext/i2c
phpize
./configure
make
make install

Then add : extension=i2c.so to your php.ini file

Run "php -m" to see if i2c is listed as an installed module
