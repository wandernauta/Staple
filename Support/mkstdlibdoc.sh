#!/bin/bash

# Distill standard library documentation from the stdops.c file.

cat Interpreter/stdops.c | grep '//' | sed -r 's/\/\/ ?//' | tail -n +10 > Documentation/Standard\ Library.mkd
