arm-none-linux-gnueabi-gcc -I../../zeromq-4.1.4/include/ -o hwclient hwclient.c -L../../zeromq-4.1.4/.libs/ -lzmq
cp libzmq.so.5  /usr/lib/
