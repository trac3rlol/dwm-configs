#! /bin/bash
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
picom --experimental-backends &
wmname LG3D
dunst -conf $HOME/.config/dunst/dunstrc &
slstatus &
nitrogen --restore &
xrandr --rate 60
$HOME/scripts/tray.sh &
