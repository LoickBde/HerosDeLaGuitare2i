all: library main

main : 
	cd src/view && $(MAKE)

rpi : library
	cd src/view && $(MAKE) rpi

ubuntu : library
	cd src/view && $(MAKE) ubuntu

examples: library
	cd libs/lib_segments/examples && $(MAKE)
	cd libs/lib_matrix/examples && $(MAKE)
	cd libs/lib_music/examples && $(MAKE)

library : 
	cd libs/lib_segments && $(MAKE)
	cd libs/lib_music && $(MAKE)
	cd libs/lib_matrix && $(MAKE)

clean : 
	cd libs/lib_segments && $(MAKE) clean
	cd libs/lib_music && $(MAKE) clean
	cd libs/lib_matrix && $(MAKE) clean 
	cd libs/lib_segments/examples && $(MAKE) clean
	cd libs/lib_matrix/examples && $(MAKE) clean
	cd libs/lib_music/examples && $(MAKE) clean
	cd src/view && $(MAKE) clean