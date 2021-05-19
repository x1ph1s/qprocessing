include ../project.mk

CFLAGS = -std=c++2a -I include
DEBUGCFLAGS = -g -D DEBUG
RELEASECFLAGS = -O3 -D RELEASE

SRCFOLDER = src
LIBFOLDER = build/lib

OBJFOLDER = build/obj
SRC := qprocessing.cpp color.cpp \
	renderer/renderer.cpp renderer/shader.cpp renderer/batch.cpp

LIB = libqprocessing.a
