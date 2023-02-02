# Uncomment lines below if you have problems with $PATH
#SHELL := /bin/bash
#PATH := /usr/local/bin:$(PATH)

build :
		pio run

upload :
		pio run --target upload

clean :
		pio run --target clean

size :
		pio run --target size

erase :
		pio run --target elase

cleanall :
		pio run --target cleanall

program :
		pio run --target program

buildfs :
		pio run --target buildfs

uploadfs :
		pio run --target uploadfs

update :
		pio pkg update

list-targets :
		pio run --list-targets
