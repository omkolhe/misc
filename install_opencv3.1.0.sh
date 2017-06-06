#!/bin/bash

echo "This installs cmake and then opencv"
echo "install git before"
echo "Do you want yo continue ? [y/n]"
read check

if(check == y)
{
	echo "installing cmake"

	sudo apt-get install build-essential
	wget http://www.cmake.org/files/v3.2/cmake-3.2.2.tar.gz
	tar xf cmake-3.2.2.tar.gz
	cd cmake-3.2.2
	./configure
	make

	sudo make install


	echo "Installing opencv and other packages"

	sudo apt-get install build-essential
	sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
	sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
	cd ~/
	git clone https://github.com/Itseez/opencv.git
	git clone https://github.com/Itseez/opencv_contrib.git
	cd ~/opencv
	mkdir build
	cd make

	cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..

	make -j7 # runs 7 jobs in parallel

	cd ~/opencv/build/doc/
	make -j7 html_docs

	sudo make install 

	echo "Done"

	sleep 5 

	cd
	clear
	

}

else
{
	echo "Mission aborted :P"

	sleep 5
	clear
}
