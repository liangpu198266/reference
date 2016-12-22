obj-m +=droplo.o
all:
	make -C /lib/modules/`uname -r`/build M=`pwd`
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
install:
	/sbin/insmod droplo.ko
remove:
	/sbin/rmmod droplo
