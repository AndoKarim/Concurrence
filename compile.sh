#!/bin/bash
###############################################################
# Team 22
# Authors: Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
###############################################################
path=$(dirname $0)
rm -rf $path/bin
mkdir $path/bin
make -C $path/src

