#!/bin/bash
if [ $# = 0 ]
then
	kaba huibui.kaba
fi
if [ $# = 1 ]
then
	kaba huibui.kaba "$1"
fi
if [ $# = 2 ]
then
	kaba huibui.kaba "$1" "$2"
fi
if [ $# = 3 ]
then
	kaba huibui.kaba "$1" "$2" "$3"
fi
