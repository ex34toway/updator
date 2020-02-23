DIRS = src

INSTALL_DIR = /mnt/local/updator/

all:
	for i in $(DIRS); do make -C $$i; done

clean:
	for i in $(DIRS); do cd $$i;make clean;cd ..; done

install: all
	mkdir -p $(INSTALL_DIR)bin
	mkdir -p $(INSTALL_DIR)logs
	cp src/updator $(INSTALL_DIR)bin/updator
	cp -r conf $(INSTALL_DIR)


.PHONY: all clean install
