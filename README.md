# dwm - dynamic window manager

## About dwm

dwm is an extremely fast, small, and dynamic window manager for X.

## Requirements


In order to build dwm you need:

-   Xlib header files

## Patches and features
The folowing features have been added:

-   [status2d](https://dwm.suckless.org/patches/status2d/) with [systemtray](https://dwm.suckless.org/patches/systray/)
-   [gaps](https://dwm.suckless.org/patches/vanitygaps/) across all layouts
-   Reads [xresources](https://dwm.suckless.org/patches/xrdb/) - pywall compatible :)
    - dwm.color4 = selfgcolor
    - dwm.color14 = selbordercolor
-   automaticaly [hides unused tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
-   cycle tags via [shiftview](https://lists.suckless.org/dev/1104/7590.html)

## Installation

Edit config.mk to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):

``` sh
    make clean install
```

## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

``` sh
    exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

``` sh
    DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

``` sh
    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
        sleep 1
    done &
    exec dwm
```

## Configuration

The configuration of dwm is done by creating a custom config.h and (re)compiling the source code.

