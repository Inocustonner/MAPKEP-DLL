# MARKER DLL
This is dll extension to MARKER, pretty old program, that adds to message boxes when user presses "Active Joystick" button. It was made in the first place because missclick on this button may cause many undesirable things.
# How to use 
- **If you have installed program and don't want to compile yourself** <br />
In folder with the MAPKEP copy and paste files from [my google drive](https://drive.google.com/file/d/1ePTIyM6ETHxKHlF3fDtcp1RIwTtQaXwx/view?usp=sharing) and also you have to install [x86 Redistributable](https://aka.ms/vs/16/release/vc_redist.x86.exe)
- **Otherwise** <br />
Download and compile my repo in `Release x86`, and then add compiled dll to the IAT of the MARKER, for example via *CFF Explorer*.
# Flags
This dll extension enables a little logging when **-debugDLL* is passed to the program(the only way to use logging on xp is to compile a new version of the program)