#!/bin/bash

sudo mkdir /spool

for var in "$@"
do
    sudo chmod 4711 "$var"
    full_path=$(readlink -f "$var")
    echo "Creating symlink to " $full_path
    sudo ln -s $full_path  /bin/
done
