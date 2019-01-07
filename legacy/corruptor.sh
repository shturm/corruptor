#!/bin/bash


for f in $1/*; do
  echo `ls -lsa $f | gawk '{ print "dd if=/dev/zero of=" $10 " count="$6%512 }'`
done

