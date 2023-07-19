#!/bin/bash
# Read from the file file.txt and print its transposed content to stdout.
readarray f < file.txt
rows_num=${#f[@]}
cols_num=$(echo "${f[0]}" | wc -w)
declare -A matrix

for ((row_idx=0; row_idx<rows_num; row_idx++)) do
  line=${f[$row_idx]}
  col_idx=0
  for word in ${line}; do
    matrix[${row_idx},${col_idx}]=${word}
    let col_idx++
    if [ "${col_idx}" -eq "${cols_num}" ]; then
      break
    fi
  done
done

for ((col_idx=0; col_idx<cols_num; col_idx++)) do
  line=""
  for ((row_idx=0; row_idx<rows_num; row_idx++)) do
    line="${line} ${matrix[${row_idx},${col_idx}]}"
  done
  echo "${line## }"
done

