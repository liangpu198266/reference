obj-m +=filterPort.o
all:
	make -C /lib/modules/`uname -r`/build M=`pwd`
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
install:
	/sbin/insmod filterPort.ko
remove:
	/sbin/rmmod filterPort
