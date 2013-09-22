#!/bin/sh

while true ; do

  msg="`date +%H:%M`목말라요.물주세요ㅜㅜ"
  
  dir="$(pwd)"
  hum=`$dir/rpiADC 0`
  tem=`$dir/rpiADC 1`
  moi=`$dir/rpiADC 2`

  data="습도:$hum온도:$tem수분:$moi"
  echo $data

  if [ $moi -lt 100 ] ; then
    echo $msg$data
    `python tweeter.py $msg$data`
  fi

  sleep 5

done
