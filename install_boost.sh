#!/bin/sh
set -ex

wget -q http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.gz
tar xf boost_1_60_0.tar.gz 
mv boost_1_60_0/boost src/.
