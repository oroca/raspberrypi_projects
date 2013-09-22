#!/bin/sh

STREAMER=mjpg_streamer
DEVICE=/dev/video0
RESOLUTION=320x240
FRAMERATE=25
PORT=8001

PLUGINPATH=/usr/local/lib

$STREAMER -i "input_uvc.so -n -d $DEVICE -r $RESOLUTION -f $FRAMERATE" -o "output_http.so -n -p $PORT"
