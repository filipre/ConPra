#!/bin/bash

if [ -n "$1" ]; then
    mkdir $1
    for i in A B C D E; do
        mkdir $1/problem$i
        cp prototype.cpp $1/problem$i/problem$i.cpp
        touch $1/problem$i/input$i.txt
    done
else
    echo "Specify week in arguments"
    exit 1
fi


