all: library

examples: 
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
