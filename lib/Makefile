# --------------------------------
# CONSTANTS
# --------------------------------
VERSION=1.0.5
EXEC=launcher
CC=gcc
LIB=GameRGR
OUTDIR=GameRGR
TESTDIR=tests
INC=$(wildcard $(TESTDIR)/*.h)
SRC=$(wildcard $(TESTDIR)/*.c)
OBJ=$(SRC:.c=.o)

BINDIR=$(OUTDIR)/bin
APIDIR=$(OUTDIR)/includes
SRCDIR=$(OUTDIR)/sources
INCDIR=$(OUTDIR)/include
LIBDIR=$(OUTDIR)/libs
FONTDIR=$(OUTDIR)/fonts
DELIVERDIR=$(OUTDIR)/delivery
ARCHDIR=$(OUTDIR)/archives
TARGET_SO=$(LIBDIR)/lib$(LIB)-$(VERSION).so

# -----------------------------
# Default target (library)
# -----------------------------
all : $(TARGET_SO)

# -----------------------------
# Objects
# -----------------------------
lib$(LIB).o : $(SRCDIR)/lib$(LIB).c $(APIDIR)/lib$(LIB).h
	@echo "Generating game lib objects ..." 
	@$(CC) -c -fPIC -I$(OUTDIR)/includes -Iinclude $< -o $@    

# -----------------------------
# Shared Library
# -----------------------------
$(TARGET_SO): lib$(LIB).o  
	@echo "Generating game share library ..." 
	@$(CC) -shared -o $@ -fPIC $^ -LGameRGR/libs -lSDL2 -lSDL2_ttf -lSDL2_image   

# -----------------------------
# User objects
# -----------------------------
$(OBJ) : $(SRC)
	@echo "Generating Test Objects ..."
	@for cfile in $(SRC); do \
	    ofile=`echo $$cfile | sed 's/\.c/\.o/g'` ; \
	    $(CC) -c -I$(APIDIR) -I$(TESTDIR) "$$cfile" -o "$$ofile"; \
    done
	
# -----------------------------
# User executable
# -----------------------------
$(BINDIR)/$(EXEC) : $(TARGET_SO) $(OBJ) 
	@echo "Generating Test Executable ..."
	@rm -f -r $(BINDIR)
	@mkdir $(BINDIR)	        
	gcc -I$(APIDIR) $(OBJ) -L$(LIBDIR) -l$(LIB)-$(VERSION) -o $@
#	@gcc -I$(APIDIR) $(OBJ) -L$(LIBDIR) -l$(LIB)-$(VERSION) -lSDL2 -lSDL2_ttf -lSDL2_image -o $@
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
	@cp $(LIBDIR)/lib$(LIB)-$(VERSION).so    $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libSDL2-2.0.so.0.18.3      $(DELIVERDIR)/libs/libSDL2.so
	@cp $(LIBDIR)/libSDL2_image-2.0.so.0.2.3 $(DELIVERDIR)/libs/libSDL2_image.so
	@cp $(LIBDIR)/libSDL2_ttf-2.0.so.0.18.0  $(DELIVERDIR)/libs/libSDL2_ttf.so
	@cp $(LIBDIR)/libjpeg.so.8.2.2           $(DELIVERDIR)/libs/libjpeg.so
	@cp $(LIBDIR)/libc-2.31.so               $(DELIVERDIR)/libs/libc.so
	@cp $(APIDIR)/*                          $(DELIVERDIR)/includes
	@cp $(FONTDIR)/emoji.png                 $(DELIVERDIR)/atlas
	@cp $(BINDIR)/$(EXEC)                    $(DELIVERDIR)/
	@ln -sr $(DELIVERDIR)/libs/lib$(LIB)-$(VERSION).so  $(DELIVERDIR)/libs/lib$(LIB).so
	@ln -sr $(DELIVERDIR)/libs/libSDL2.so               $(DELIVERDIR)/libs/libSDL2-2.0.so.0
	@ln -sr $(DELIVERDIR)/libs/libSDL2_ttf.so           $(DELIVERDIR)/libs/libSDL2_ttf-2.0.so.0
	@ln -sr $(DELIVERDIR)/libs/libSDL2_image.so         $(DELIVERDIR)/libs/libSDL2_image-2.0.so.0
	@ln -sr $(DELIVERDIR)/libs/libjpeg.so               $(DELIVERDIR)/libs/libjpeg.so.8
	@ln -sr $(DELIVERDIR)/libs/libc.so                  $(DELIVERDIR)/libs/libc.so.6
	@cd $(DELIVERDIR); \
	  tar czpf "GameRGR-$(VERSION).tar" "./atlas" "./includes" "./libs"; \
	  mv "GameRGR-$(VERSION).tar" ../../$(ARCHDIR)
        
# -----------------------------
# Clean
# -----------------------------
clean : 
	rm -f *.o
	rm -f $(TESTDIR)/*.o
	rm -f $(LIBDIR)/lib$(LIB).so
	rm -f $(LIBDIR)/lib$(LIB)-$(VERSION).so
	rm -f -r $(BINDIR)
	rm -f -r $(DELIVERDIR)

