#!/bin/bash

# disable CPU scaling (get rid of warning thrown by google benchmark
sudo cpupower frequency-set --governor performance

../build-fuzzychains-Desktop_Qt_6_2_2_GCC_64bit-Release/fuzzychains

# enable CPU scaling again
sudo cpupower frequency-set --governor powersave

