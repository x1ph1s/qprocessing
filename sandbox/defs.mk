include ../project.mk

CFLAGS = -std=c++2a -I includes
DEBUGFLAGS = -g -D DEBUG
RELEASECFLAGS = -O3 -D RELEASE

LDFLAGS = -lqprocessing -lGL -lGLEW -lglfw
DEBUGLDFLAGS = -L build/lib/debug
RELEASELDFLAGS = -L build/lib/release

DEBUGDEPEND = build/lib/debug/libqprocessing.a
RELEASEDEPEND = build/lib/release/libqprocessing.a

SRCFOLDER = src
BINFOLDER = build/bin
OBJFOLDER = build/obj
SRC := main.cpp

BIN = qprocessing_sandbox
