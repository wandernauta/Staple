#!/bin/bash

# Distill standard library documentation from the stdops.c file.

cat Interpreter/stdops.c | grep '//' | colrm 1 3 | tail -n +10 > Documentation/Standard\ Library.mkd
