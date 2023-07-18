#!/bin/bash
# Read from the file file.txt and output the tenth line to stdout.
for i in {1..10}; do
  if ! read line; then
    line=""
  fi
done <file.txt
echo ${line}
