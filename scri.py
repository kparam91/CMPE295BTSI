import os
import subprocess

path=os.getcwd()


firstlines="cmake_minimum_required(VERSION 2.8)\n\
project( test )\n\
find_package( OpenCV REQUIRED )\n\
include_directories( ${OpenCV_INCLUDE_DIRS} )\n"

f=open("CMakeLists.txt",'w')
f.write(firstlines)
for a in os.listdir(path):
    if ".cpp" in a and "~" not in a:
        print a
        f.write("add_executable("+a[:-4]+" "+a+")\n")
        f.write("target_link_libraries("+a[:-4]+" "+"${OpenCV_LIBS})\n")
f.close()
subprocess.call("cmake .", shell=True)
subprocess.call("make", shell=True)
