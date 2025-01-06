CC = gcc
INCDIR = -Iinclude
LIBDIR = -Llib -L"/c/msys64/mingw64/x86_64-w64-mingw32/lib" -L"/c/msys64/mingw64/lib" 
CFLAGS += -O2 -Wall -std=c99

LDFLAGS += -ltmx -lxml2 -lz -lraylib -lopengl32 -lgdi32  -lws2_32 -lwinmm

.PHONY: all clean

all:
	$(CC) src/gameTB.c -o  taou.exe $(CFLAGS) $(INCDIR) $(LIBDIR) $(LDFLAGS)

clean:
	rm *.o
	rm *.a
	rm *.exe