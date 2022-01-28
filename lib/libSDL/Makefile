# --------------------------------
# CONSTANTS
# --------------------------------
EXEC=launcher
CC=gcc
LIB=GameRGR
OUTDIR=GameRGR
BINDIR=$(OUTDIR)/bin
APIDIR=$(OUTDIR)/includes
INCDIR=$(OUTDIR)/include
LIBDIR=$(OUTDIR)/libs
FONTDIR=$(OUTDIR)/fonts


# -----------------------------
# Default target (library)
# -----------------------------
all : $(EXEC)

# -----------------------------
# Objects
# -----------------------------
%.o : %.c $(APIDIR)/lib$(LIB).h
	$(CC) -c -fPIC -I$(OUTDIR)/includes -Iinclude $< -o $@    

# -----------------------------
# Shared Library
# -----------------------------
lib$(LIB).so: lib$(LIB).o  
	$(CC) -shared $^ -o $(LIBDIR)/$@
	
# -----------------------------
# User executable
# -----------------------------
$(EXEC) : main.c lib$(LIB).so
	gcc -I$(APIDIR) main.c -L$(LIBDIR) -l$(LIB) -lSDL2 -lSDL2_ttf -o $@
	export LD_LIBRARY_PATH=$(LIBDIR)

.PHONY: deploy
deploy: 
	rm -f *.o
	

clean : deploy
	rm -f $(LIBDIR)/lib$(LIB).so
	
    	
	
	



	
