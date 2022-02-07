# --------------------------------
# CONSTANTS
# --------------------------------
VERSION=0.9.0
EXEC=launcher
CC=gcc
LIB=GameRGR
OUTDIR=GameRGR
BINDIR=$(OUTDIR)/bin
APIDIR=$(OUTDIR)/includes
INCDIR=$(OUTDIR)/include
LIBDIR=$(OUTDIR)/libs
FONTDIR=$(OUTDIR)/fonts
DELIVERDIR=$(OUTDIR)/delivery


# -----------------------------
# Default target (library)
# -----------------------------
all : $(BINDIR)/$(EXEC)

# -----------------------------
# Objects
# -----------------------------
%.o : %.c $(APIDIR)/lib$(LIB).h
	$(CC) -c -fPIC -I$(OUTDIR)/includes -Iinclude $< -o $@    

# -----------------------------
# Shared Library
# -----------------------------
$(LIBDIR)/lib$(LIB).so: lib$(LIB).o  
	$(CC) -shared $^ -o $@

# -----------------------------
# User executable
# -----------------------------
$(BINDIR)/$(EXEC) : main.c $(LIBDIR)/lib$(LIB).so
	rm -f -r $(BINDIR)
	mkdir $(BINDIR)	        
	gcc -I$(APIDIR) main.c -L$(LIBDIR) -l$(LIB) -lSDL2 -lSDL2_ttf -lSDL2_image -o $@
	export LD_LIBRARY_PATH=$(LIBDIR)

# -----------------------------
# Delivery package
# -----------------------------
.PHONY: deploy $(BINDIR)/$EXEC
deploy: $(LIBDIR)/lib$(LIB).so
	rm -f -r $(DELIVERDIR)
	mkdir $(DELIVERDIR)	    
	mkdir $(DELIVERDIR)/libs
	mkdir $(DELIVERDIR)/includes
	mkdir $(DELIVERDIR)/atlas
	cp $(LIBDIR)/libGameRGR.so              $(DELIVERDIR)/libs/libGameRGR.so
	cp $(LIBDIR)/libSDL2-2.0.so.0.18.3      $(DELIVERDIR)/libs/libSDL2.so
	cp $(LIBDIR)/libSDL2_image-2.0.so.0.2.3 $(DELIVERDIR)/libs/libSDL2_image.so
	cp $(LIBDIR)/libSDL2_ttf-2.0.so.0.18.0  $(DELIVERDIR)/libs/libSDL2_ttf.so
	cp $(APIDIR)/* $(DELIVERDIR)/includes
	cp $(FONTDIR)/emoji.png $(DELIVERDIR)/atlas
	cp $(BINDIR)/$(EXEC) $(DELIVERDIR)/
	cd $(DELIVERDIR)/libs
	ln -sr $(DELIVERDIR)/libs/libSDL2.so       $(DELIVERDIR)/libs/libSDL2-2.0.so.0
	ln -sr $(DELIVERDIR)/libs/libSDL2_ttf.so   $(DELIVERDIR)/libs/libSDL2_ttf-2.0.so.0
	ln -sr $(DELIVERDIR)/libs/libSDL2_image.so $(DELIVERDIR)/libs/libSDL2_image-2.0.so.0
	cd $(DELIVERDIR); \
	  tar czpvf "GameRGR-$(VERSION).tar" "./atlas" "./includes" "./libs"
        
# -----------------------------
# Clean
# -----------------------------
clean : 
	rm -f *.o
	rm -f $(LIBDIR)/lib$(LIB).so
	rm -f -r $(BINDIR)
	rm -f -r $(DELIVERDIR)
    	
    	
	
	



	
