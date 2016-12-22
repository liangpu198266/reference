obj-m +=whovisit.o
all:
	make -C /lib/modules/`uname -r`/build/ M=`pwd` 
clean:
	make -C /lib/modules/`uname -r`/build/ M=`pwd` clean
install:
	/sbin/insmod whoVisit.ko
remove:
	/sbin/rmmod whoVisit
