
CC     = gcc
INCDIR = -I../lua/src
LIB    = 
LIBDIR =  -L. -L../lua/src
CFLAGS = -Os -Wall -c #-g

# generic platform specific rules:
ARCH            = $(shell uname -s)
ifeq ($(ARCH),Linux)
  CFLAGS += -fPIC
  LFLAGS =  -fPIC -shared
  LIBS          = $(LIBDIR) $(LIB) -llua -ldl
  EXESUFFIX =
  SHLIBSUFFIX = .so

else  
  ifeq ($(ARCH),Darwin) # MacOSX
    LFLAGS = -bundle 
    LIBS          = $(LIBDIR) -L/usr/local/lib $(LIB) -llua
    EXESUFFIX = .app
    SHLIBSUFFIX = .so
    
  else  # windows, MinGW
    LFLAGS =  -shared
    LIBS          = $(LIBDIR) $(LIB) -llua51 -mconsole -s
    EXESUFFIX = .exe
    SHLIBSUFFIX = .dll

  endif
endif

all: LuaSVG_lib$(SHLIBSUFFIX)

LuaSVG_lib$(SHLIBSUFFIX): LuaSVG_lib.o nanosvg.o
	$(CC) -o $@ $(LFLAGS) $^ $(LIBS)

# project specific dependencies:
LuaSVG_lib.o:  LuaSVG_lib.c

nanosvg.o: nanosvg.c

.c.o:
	$(CC) $(CFLAGS) $(INCDIR) $<

clean:
	rm *.o *.dll
