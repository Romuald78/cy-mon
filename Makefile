#-----------------------------------------
# VARIABLES
#-----------------------------------------
CC       = gcc
LIBDIR   = lib/
LIBS     = -lGameRGR -lm 
BUILDIR  = build/
SRCDIR   = sources/
OBJDIR   = $(BUILDIR)obj/
BINDIR   = $(BUILDIR)bin/

EXEC     = $(BINDIR)main
INC      = $(sort $(wildcard sources/*/*.h))
SRC      = $(sort $(wildcard sources/*/*.c))
OBJ     := $(subst $(SRCDIR),$(OBJDIR),$(SRC:.c=.o))
INCLUDE  = $(addprefix -I, $(dir $(INC)))
INCLUDE := -I. $(INCLUDE)

#-----------------------------------------
# DEFAULT
#-----------------------------------------
all : $(EXEC)

#-----------------------------------------
# OBJECTS
#-----------------------------------------
$(OBJDIR)%.o : $(SRCDIR)%.c $(INC)
	@echo "Creating object [$@]..."
	@mkdir -p $(dir $@)
	@$(CC) $(INCLUDE) -c $< -o $@
#	@echo "\n"

#-----------------------------------------
# MAIN
#-----------------------------------------
$(EXEC) : $(OBJ)
	@echo "Creating executable [$@]..."
	@mkdir -p $(dir $@)
	@$(CC) $^ -o $@ -L$(LIBDIR) $(LIBS)
    
#-----------------------------------------
# CLEAN
#-----------------------------------------
# clean all
clean  : 
	@echo "Removing all output directories..."
	@rm -r -f $(BUILDIR)

# clean anything but bin
cleanObj :
	@echo "Removing object directory..."
	@rm -r -f $(OBJDIR)
	@rm -f *.log

# clean bin only
cleanBin :
	@echo "Removing executable directory..."
	@rm -r -f $(BINDIR)

#-----------------------------------------
# REBUILD
#-----------------------------------------
.PHONY  : rebuild
rebuild : clean $(EXEC)

#-----------------------------------------
# DEBUG
#-----------------------------------------
debug :
	clear
	@echo "SRC=\n$(SRC) \n"
	@echo "INC=\n$(INC) \n"
	@echo "OBJ=\n$(OBJ) \n"
	@echo "INCLUDE=\n$(INCLUDE) \n"

