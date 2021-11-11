# CTimer
A timer write by C. Used for scheduled execution,such as State examination.
## How to use
### 1.run this cmd in console with --cmd [...] --times [...]
--dir will push the command to the Timer;  
--times will push the time points of the command execution to the Timer;  
After you execute it successfully,the Timer will do it every day,also will occupy a terminal window.
### 2.compiler
we use cmake to generate the makefile,so you need 'make' and 'cmake' to compiler it.  
~~~shell/bash
cmake CMakeLists.txt;
make;
~~~
### 3.download the compiled program
Windows x64:[CTimer.exe](https://github.com/sketchdee/CTimer/blob/main/CTimer)  
Linux x64:[CTimer](https://github.com/sketchdee/CTimer/blob/main/CTimer.exe)  
