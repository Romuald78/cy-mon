# --------------------------------
# CONSTANTS
# --------------------------------
VERSION=1.0.7
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
	@export LD_LIBRARY_PATH=$(LIBDIR) ; \
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
		
	@cp $(APIDIR)/*                          $(DELIVERDIR)/includes
	@cp $(FONTDIR)/emoji.png                 $(DELIVERDIR)/atlas
	@cp $(BINDIR)/$(EXEC)                    $(DELIVERDIR)/
	
#	@elements2=`ls $(LIBDIR) -l | grep -v lrwx | tr -s ' ' | tr ' ' ';' | cut -d';' -f9,11`	
	@cp $(LIBDIR)/ld-2.31.so                    $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libc-2.31.so                  $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libdl-2.31.so                 $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/lib$(LIB)-$(VERSION).so       $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libjbig.so.0                  $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libjpeg.so.8.2.2              $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/liblzma.so.5.2.4              $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libm-2.31.so                  $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libpng16.so.16.37.0           $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libpthread-2.31.so            $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libSDL2-2.0.so.0.18.3         $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libSDL2_image-2.0.so.0.2.3    $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libSDL2_ttf-2.0.so.0.18.0     $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libtiff.so.5.5.0              $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libwebp.so.6.0.2              $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libz.so.1.2.11                $(DELIVERDIR)/libs/
	@cp $(LIBDIR)/libzstd.so.1.4.4              $(DELIVERDIR)/libs/

	@ln -sr $(DELIVERDIR)/ld-2.31.so                 $(DELIVERDIR)/ld-linux-x86-64.so.2
	@ln -sr $(DELIVERDIR)/libc-2.31.so               $(DELIVERDIR)/libc.so.6
	@ln -sr $(DELIVERDIR)/libdl-2.31.so              $(DELIVERDIR)/libdl.so.2
	@ln -sr $(DELIVERDIR)/libjpeg.so.8.2.2           $(DELIVERDIR)/libjpeg.so
	@ln -sr $(DELIVERDIR)/libjpeg.so.8.2.2           $(DELIVERDIR)/libjpeg.so.8
	@ln -sr $(DELIVERDIR)/liblzma.so.5.2.4           $(DELIVERDIR)/liblzma.so.5
	@ln -sr $(DELIVERDIR)/libm-2.31.so               $(DELIVERDIR)/libm.so.6
	@ln -sr $(DELIVERDIR)/libpng16.so.16.37.0        $(DELIVERDIR)/libpng16.so.16
	@ln -sr $(DELIVERDIR)/libpthread-2.31.so         $(DELIVERDIR)/libpthread.so.0
	@ln -sr $(DELIVERDIR)/libSDL2-2.0.so.0.18.3      $(DELIVERDIR)/libSDL2-2.0.so.0
	@ln -sr $(DELIVERDIR)/libSDL2_image-2.0.so.0.2.3 $(DELIVERDIR)/libSDL2_image-2.0.so.0
	@ln -sr $(DELIVERDIR)/libSDL2_image-2.0.so.0.2.3 $(DELIVERDIR)/libSDL2_image.so
	@ln -sr $(DELIVERDIR)/libSDL2-2.0.so.0.18.3      $(DELIVERDIR)/libSDL2.so
	@ln -sr $(DELIVERDIR)/libSDL2_ttf-2.0.so.0.18.0  $(DELIVERDIR)/libSDL2_ttf-2.0.so.0
	@ln -sr $(DELIVERDIR)/libSDL2_ttf-2.0.so.0.18.0  $(DELIVERDIR)/libSDL2_ttf.so
	@ln -sr $(DELIVERDIR)/libtiff.so.5.5.0           $(DELIVERDIR)/libtiff.so.5
	@ln -sr $(DELIVERDIR)/libwebp.so.6.0.2           $(DELIVERDIR)/libwebp.so.6
	@ln -sr $(DELIVERDIR)/libz.so.1.2.11             $(DELIVERDIR)/libz.so.1
	@ln -sr $(DELIVERDIR)/libzstd.so.1.4.4           $(DELIVERDIR)/libzstd.so.1

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

