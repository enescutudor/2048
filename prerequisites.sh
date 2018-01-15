#!/bin/bash

sudo apt-get install libncurses-dev
#install the ncurses graphic library
if ! [ -f savegame ]
then
	touch savegame
	echo "0" > savegame
fi
#check for the existance of the savegame file, and creates it,
#if it is the case
