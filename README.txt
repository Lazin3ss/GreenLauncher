GreenLauncher - An application/game manager for Windows 95/98.

VERSION: 0.2 (Nov 28, 2024)
AUTHOR: Francisco Iturrieta (Lazin3ss)
ATTRIBUTIONS: See source code

WEBSITES:
https://lazin3ss.github.io/GreenLauncher/
http://github.com/Lazin3ss/GreenLauncher

This is an application manager/launcher intended for Windows 9x-based 
systems, though it should also work on Windows 10/11. I started this 
project because I wasn't able to find something native for Win9x that 
suited my needs. It's heavily inspired by Steam, MAME32, D-Fend Reloaded 
and AmpShell, and it's coded in AutoIt3 scripting language, targeting 
version 3.2.12.1. It also makes use of SQLite 3.7.11, latest version to 
work with Windows 98 (at least).

REQUIREMENTS:
- 64MB of RAM (the launcher might use at least 10MB)
- A Microsoft Windows-based system (95/98/NT/2000/XP+)
- SQLite 3.5.4 or higher (3.7.11 is recommended)

FAQ:
Q: Where do I get older versions of SQLite?
A: Here are some links:
3.7.11: http://www.sqlite.org/sqlite-dll-win32-x86-3071100.zip
3.5.4: http://www.sqlite.org/sqlitedll-3_5_4.zip

------------------------------
------ RELEASE HISTORY -------
------------------------------

------------------------------

0.2 - 2024.11.28

- Improved database
- New fields: Developer, Publisher, Genre, Category, Favorite
- Added a status bar

------------------------------

0.1 - 2024.11.21

- Inital release
- Basic game add/update/delete features