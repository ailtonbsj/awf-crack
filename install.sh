#!/bin/bash

sudo apt-get update
sudo apt-get install curl gcc
gcc awf-crack.c -o awf-crack
sudo cp awf-crack /bin/awf-crack
