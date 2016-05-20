obj-m +=netMonitor.o
all:
	make -C /lib/modules/`uname -r`/build M=`pwd`
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
install:
	/sbin/insmod netMonitor.ko
remove:
	/sbin/rmmod netMonitor
