#!/bin/sh

printf "\n Building in 'dist' ..\n"
mkdir bin
mkdir dist
cd bin
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j4
printf "Copying Executable 'retroclysm'\n"
cp ./retroclysm ../dist/retroclysm

printf "\nCopying Assets ..\n"
cp -R ../assets/* ../dist

printf "\nCreate Saves Directory ..\n"
mkdir ../dist/save

printf "\nDone\n"
