DIRS = src

INSTALL_DIR = /mnt/local/updator/

all:
	for i in $(DIRS); do make -C $$i; done

clean:
	for i in $(DIRS); do cd $$i;make clean;cd ..; done

install: all
	#mkdir for tsar
	mkdir -p $(INSTALL_DIR)bin
	#copy bin file
	cp src/updator $(INSTALL_DIR)bin/updator

tags:
	ctags -R
	cscope -Rbq

.PHONY: all clean install
