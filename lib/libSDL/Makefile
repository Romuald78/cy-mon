# --------------------------------
# CONSTANTS
# --------------------------------
VERSION=1.0.1
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
ARCHDIR=$(OUTDIR)/archives

# -----------------------------
# Default target (library)
# -----------------------------
all : deploy

# -----------------------------
# Objects
# -----------------------------
%.o : %.c $(APIDIR)/lib$(LIB).h
	@echo "Generating game lib objects ..." 
	@$(CC) -c -fPIC -I$(OUTDIR)/includes -Iinclude $< -o $@    

# -----------------------------
# Shared Library
# -----------------------------
$(LIBDIR)/lib$(LIB).so: lib$(LIB).o  
	@echo "Generating game share library ..." 
	@$(CC) -shared $^ -o $@

# -----------------------------
# User executable
# -----------------------------
$(BINDIR)/$(EXEC) : main.c $(LIBDIR)/lib$(LIB).so
	@echo "Generating Test Executable ..."
	@rm -f -r $(BINDIR)
	@mkdir $(BINDIR)	        
	@gcc -I$(APIDIR) main.c -L$(LIBDIR) -l$(LIB) -lSDL2 -lSDL2_ttf -lSDL2_image -o $@
	@rm -f *.o
    
# -----------------------------
# Delivery package
# -----------------------------
.PHONY: deploy 
deploy: $(BINDIR)/$(EXEC)
	@echo "Creating Delivery Folder ..."
	@rm -f -r $(ARCHDIR)
	@mkdir $(ARCHDIR)	    
	@rm -f -r $(DELIVERDIR)
	@mkdir $(DELIVERDIR)	    
	@mkdir $(DELIVERDIR)/libs
	@mkdir $(DELIVERDIR)/includes
	@mkdir $(DELIVERDIR)/atlas
	@echo "Filling Delivery Folder ..."
	@echo "Creating Delivery Archive ..."
	@cp $(LIBDIR)/libGameRGR.so              $(DELIVERDIR)/libs/libGameRGR.so
	@cp $(LIBDIR)/libSDL2-2.0.so.0.18.3      $(DELIVERDIR)/libs/libSDL2.so
	@cp $(LIBDIR)/libSDL2_image-2.0.so.0.2.3 $(DELIVERDIR)/libs/libSDL2_image.so
	@cp $(LIBDIR)/libSDL2_ttf-2.0.so.0.18.0  $(DELIVERDIR)/libs/libSDL2_ttf.so
	@cp $(APIDIR)/* $(DELIVERDIR)/includes
	@cp $(FONTDIR)/emoji.png $(DELIVERDIR)/atlas
	@cp $(BINDIR)/$(EXEC) $(DELIVERDIR)/
	@cd $(DELIVERDIR)/libs
	@ln -sr $(DELIVERDIR)/libs/libSDL2.so       $(DELIVERDIR)/libs/libSDL2-2.0.so.0
	@ln -sr $(DELIVERDIR)/libs/libSDL2_ttf.so   $(DELIVERDIR)/libs/libSDL2_ttf-2.0.so.0
	@ln -sr $(DELIVERDIR)/libs/libSDL2_image.so $(DELIVERDIR)/libs/libSDL2_image-2.0.so.0
	@cd $(DELIVERDIR); \
	  tar czpf "GameRGR-$(VERSION).tar" "./atlas" "./includes" "./libs"; \
	  mv "GameRGR-$(VERSION).tar" ../../$(ARCHDIR)
        
# -----------------------------
# Clean
# -----------------------------
clean : 
	rm -f *.o
	rm -f $(LIBDIR)/lib$(LIB).so
	rm -f -r $(BINDIR)
	rm -f -r $(DELIVERDIR)

