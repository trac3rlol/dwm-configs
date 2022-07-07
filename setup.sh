#!/bin/bash

echo "Would you like to continue with the setup? (y/n)"

read choice

if [[ $choice = "y" ]]; then
    echo "Starting Dwm setup..."
    mkdir -p $HOME/.dwm
    cp -r dwm/ $HOME/.dwm
    cd $HOME/.dwm/ && sudo make clean install && cd ..
    echo "Dwm config setup completed"
    sleep 1s
    echo "Starting Dmenu setup..."
    mkdir -p $HOME/.config/dmenu
    cp -r dmenu/ $HOME/.config/dmenu
    cd $HOME/.config/dmenu/ && sudo make clean install && cd ..
    echo "Dmenu config setup completed"
    sleep 1s
    echo "Starting Slock setup..."
    mkdir -p $HOME/.config/slock
    cp -r slock/ $HOME/.config/slock
    cd $HOME/.config/slock/ && sudo make clean install && cd ..
    echo "Slock config setup completed"
    sleep 1s
    echo "Starting Slstatus setup..."
    mkdir -p $HOME/.config/slstatus
    cp -r slstatus/ $HOME/.config/slstatus
    cd $HOME/.config/slstatus/ && sudo make clean install && cd ..
    echo "Slstatus config setup completed"
    sleep 1s
    echo "Installing Dependencies"
    sudo pacman -S dwm dmenu st libxft ttf-joypixels ttf-hack terminus-font ttf-nerd-font-symbols
    sleep 1s
    echo "Do you want to reboot? (y/n)"
    read reboot
    if [[ $reboot = "y" ]]; then
        sudo reboot
    elif [[ $reboot = "n" ]]; then
        echo "Exiting Script in 2 seconds"
        sleep 2s
        exit
    fi
elif [[ $choice = "n" ]]; then
    echo "Exiting now"
    sleep 3s
    exit
fi
