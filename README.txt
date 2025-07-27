GreenLauncher - An application/game manager for Windows 9x+ systems,
written in C++.

VERSION: 0.1 RC4 (Jul 26, 2025)
AUTHOR: Francisco Iturrieta (Lazin3ss)
LICENSE: GPL-3

WEBSITES:
https://lazin3ss.github.io/GreenLauncher/
http://github.com/Lazin3ss/GreenLauncher

This is an application manager/launcher with support for
Windows 9x-based systems, all the way up to Windows 11. I started this
project because I wasn't able to find something native for Win9x that
suited my needs. It's heavily inspired by Steam, MAME32, D-Fend
Reloaded and AmpShell. It uses wxWidgets as its main library, and the
database is handled through SQLite3 (3.50.2). I tried to make it as
lightweight as possible, a first run should use only 2MB of RAM. In the
future, it might be even possible to run it on GNU/Linux and MacOS.

REQUIREMENTS:
- A 386DX processor or higher
- 8MB of RAM
- A Microsoft Windows-based system (95/98/NT/2000/XP+)
- COMCTL32.DLL 5.80 or greater (you can run 50comupd.exe in Win 95)
- UNICOWS.DLL

(As you can see, these are just the minimum requirements for running
Windows 95)

------------------------------
------ RELEASE HISTORY -------
------------------------------

0.1 - 2025.07.26

- Inital release
- Basic game add/update/delete features
- Basic filtering
- Multiple launch configurations (actions) functionality
- Support for multiple metadata values
- Add support various metadata (Favorite, Categories, Source, Date,
Platform, Developer, Publisher, Genre, Series, Region, Language,
License Model)