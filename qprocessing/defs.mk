include ../project.mk

CFLAGS = -std=c++2a -I includes
DEBUGFLAGS = -g -D DEBUG
RELEASECFLAGS = -O3 -D RELEASE

SRCFOLDER = src
LIBFOLDER = build/lib

OBJFOLDER = build/obj
SRC := qprocessing.cpp color.cpp renderer.cpp shader.cpp index_buffer.cpp vertex_buffer.cpp

LIB = libqprocessing.a
