#/bin/sh

mex mexdyn.cpp
matlab -nojvm -r call_mexdyn
