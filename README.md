SQLite
======

SQLite running bare metal on the Raspberry Pi using the [circle-stdlib](https://github.com/smuehlst/circle-stdlib) project.

See the discussion [here](https://github.com/rsta2/circle/issues/328)!

Getting
-------

	git clone https://github.com/rsta2/sqlite.git
	git submodule update --init circle-stdlib
	cd circle-stdlib/
	git submodule update --init libs/circle
	git submodule update --init libs/circle-newlib
	cd libs/circle/
	git submodule update --init addon/wlan/hostap

Building
--------

From project root:

	cd circle-stdlib/
	configure -r 4 -p aarch64-none-elf-	# for Raspberry Pi 4 64-bit
	make -j
	cd ../src/
	make -j

Installation
------------

Like all Circle apps. Copy the file src/kernel*.img along with the firmware files to an SD card. Create a directory /sqlite on the SD card.
