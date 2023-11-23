# Bug fix history
v2023.11.13-- support you to write compress path with folder-name


# Huffman-Compress
Huffman Compress Project based on terminal instead of Gui

## Introduction
If you just want to try this program,you can download main.exe .
main.exe should be run in the fold that you want to place your compress data,it will save compressed file in current directory


after Compile,command list will guide  you to use this small but Inefficient tool. This program is only a practice during school time.you can import it
for study or secondary development.**But please not c-v it and submitted in your homework!**

After compress and decompress it will make an folder to storage output file.

There are also some flaw in this program.
you can **not** compress a file not exist in current directory with Absolute Path or Relative path.

## Compress.h-Compress.cpp
Compressor class,finish the Compress progress

## Decompress.h-Dcompress.cpp
Decompressor class, finish the Decompress progress

## Huffman.h- Huffman.cpp
Huffman tree templet

## main.cpp
Start program from hear.

## Notice
This program no Cmake file structrue,you should run it with command:  

g++ Compress.cpp Compress.h Dcompress.cpp Decompress.h main.cpp -o output.exe  

to launch this program!  

you can also open it with vscode,then write tasks.json by yourself
