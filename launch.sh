#!/bin/bash

# --------------------------------------------------------
# launch the game in a new terminal (using 2 arguments for WIDTH and HEIGHT)
# --------------------------------------------------------
if [ $# -eq 2 ]
then
    W=$1
    H=$2
    DIR1=`pwd`
    DIR2=`dirname $0`
    FULLDIR=$DIR1/$DIR2/
    gnome-terminal --geometry=${W}x${H} -- $FULLDIR/launch.sh $FULLDIR
    exit
fi

# --------------------------------------------------------
# Store #1 argument, that shall be the full directory path
# when launched in a new terminal
# --------------------------------------------------------
if [ $# -ge 1 ]
then
    FULLPATH=$1
fi

# --------------------------------------------------------
# set the game in the current terminal/current folder
# --------------------------------------------------------
if [ $# -eq 0 ]
then
    FULLPATH="."
fi

# --------------------------------------------------------
# Launch the game according to the previous arguments 
# --------------------------------------------------------   
FPS=20
SHOW=0
KEYBOARD=/dev/input/event3
MOUSE=/dev/input/mice

stty -echo
tput civis
resize
clear

sudo $FULLPATH/build/bin/main 2>'error.log' $COLUMNS $LINES $KEYBOARD $MOUSE $FPS $SHOW

RET=$?
if [ $RET -ne 0 ]
then
    echo "Program returned with code = $RET"
fi
tput cnorm
stty echo

