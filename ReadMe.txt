The following instructions are for compiling in a linux terminal 
Insure all dependancies are installed ("SelfOrganizingList.h" amd "SelfOrganizingList.cpp") in same directory as source file, in order to run source file (main.cpp)

change directory to
jovyan@jupyter-yourcuid:~$ cd SelfOrganizingList

Build code
jovyan@jupyter-yourcuid:~$ g++ -o main main.cpp SelfOrganizingList.cpp 

Run executable
jovyan@jupyter-yourcuid:~$ ./main