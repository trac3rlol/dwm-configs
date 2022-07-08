#!/bin/bash

echo "DWM SETUP"
pacman -S nitrogen libxft picom ttf-font-awesome ttf-hack ttf-nerd-fonts-symbols terminus-font
sleep 2s
mkdir /usr/share/xsessions/
mv dwm/dwm.desktop /usr/share/xsessions/
mv dwm /usr/local/
mv dmenu /usr/local/
mv slock /usr/local/
mv slstatus /usr/local/
cd /usr/local/dwm && make clean install && cd ..
cd dmenu && make clean install && cd ..
cd slstatus && make clean install && cd ..
cd slock && make clean install && cd ..
sleep 2s
echo "DWM setup finished"
