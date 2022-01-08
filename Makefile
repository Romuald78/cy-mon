#-----------------------------------------
# VARIABLES
#-----------------------------------------
LIBDIR = ../libRGR/
SRCDIR = ./src/
INCDIR = ./inc/
BUILDIR= ./build/
OBJDIR = $(BUILDIR)obj/
BINDIR = $(BUILDIR)bin/
EXEC   = main

SRC  = $(wildcard $(SRCDIR)*.c)
INC  = $(wildcard $(INCDIR)*.h)
OBJ  = $(subst $(SRCDIR),$(OBJDIR),$(SRC))
OBJ := $(OBJ:.c=.o)

#-----------------------------------------
# DEFAULT
#-----------------------------------------
all    : $(OBJDIR) $(BINDIR) $(BINDIR)$(EXEC)

#-----------------------------------------
# OBJECTS
#-----------------------------------------
$(OBJDIR)%.o : $(SRCDIR)%.c $(INC) $(LIBDIR)libGameRGR.a $(LIBDIR)emoticons.h
	gcc -I. -c $< -o $@

#-----------------------------------------
# MAIN
#-----------------------------------------
$(BINDIR)$(EXEC) : $(OBJ)
	@echo "Regenerating [$@]..."
	gcc $^ -o $@ -L$(LIBDIR) -lGameRGR -lm

#-----------------------------------------
# CLEAN
#-----------------------------------------
# clean all
.PHONY : clean
clean  : cleanObj cleanBin
	rm -r -f $(BUILDIR)

# clean anything but bin
.PHONY : cleanObj
cleanObj  :
	rm -f $(OBJDIR)*.o
	rm -r -f $(OBJDIR)
	# remove logs
	rm -f *.log

# clean bin only
.PHONY : cleanBin
cleanBin  :	
	rm -f $(BINDIR)$(EXEC)
	rm -r -f $(BINDIR)

#-----------------------------------------
# PREPARE folders
#-----------------------------------------
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

#-----------------------------------------
# REBUILD
#-----------------------------------------
.PHONY  : rebuild
rebuild : clean $(OBJDIR) $(BINDIR) $(BINDIR)$(EXEC)

