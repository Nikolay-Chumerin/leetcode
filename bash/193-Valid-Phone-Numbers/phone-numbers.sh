#!/bin/bash
# Read from the file file.txt and output all valid phone numbers to stdout.
grep '^[0-9][0-9][0-9]-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]$\|^([0-9][0-9][0-9]) [0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]$' file.txt
