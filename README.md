Simple 1vs1 C++ Checkers with Command Line Interface aka "Fun with Pointers and References"

This is the final project of my first programming course at the HTWK Leipzig from WS20/21. I had no previous experience in programming that was worth noting. Thus understanding C++ compiler warnings, header files, pointers and references was not easy for me and I guess that is visible in the code. I am still not sure, if pointers and references are handled the way, they are supposed to here. Feedback is very welcome!

Besides removing some WIP comments, minor refactoring and fixing a potential memory leak this is what I handed in when the given time of two weeks was up.

How to Run on Unix Systems (Linux, MacOs):
1. Install a c++ compiler (clang or gcc for example)
2. Open terminal, go to a convenient directory and run: ```git clone git@github.com:FranziskusZillmann/cpp-checkers.git```
3. Go to src directory ```cd cpp-checkers/src```
4. run: ```clang++ main.cpp Spielbrett.cpp -o cppcheckers -std=c++14 -Weverything -Wno-c++98-compat -Wno-align -Wno-padded```
5. run: ```./cppcheckers``` (or another name of your choosing for the binary in the line above)
6. Follow the ingame instructions

PS: All the outputs, variables, classes, functions and comments are in german. I am sorry if that causes inconveniences and I might refactor that once I find the time. For now a little dictionary:

|german|english|
|---|---|
|Spiel|Game|
|Spieler|Player|
|Zug|Turn|
|Brett|Board|
|Spielbrett|(here:) game state|
|anwenden|apply|
|ungültig|invalid|
|laufen|walk|
|schlagen|(here:) capture|
