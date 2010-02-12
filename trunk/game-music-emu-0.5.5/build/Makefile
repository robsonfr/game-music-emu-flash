#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
TOPDIR ?= $(CURDIR)/..

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX		:=	

export CC	:=	$(PREFIX)gcc
export CXX	:=	$(PREFIX)g++
export AS	:=	$(PREFIX)as
export AR	:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

#---------------------------------------------------------------------------------
%.o: %.cpp
	@echo $(notdir $<)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
#---------------------------------------------------------------------------------
%.o: %.c
	@echo $(notdir $<)
	$(CC) $(CFLAGS) -c $< -o $@


#---------------------------------------------------------------------------------
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# DATA is a list of directories containing binary files
# LIB is where the built library will be placed
# all directories are relative to this makefile
#---------------------------------------------------------------------------------
#BUILD		?=	release
SOURCES		:=	../gme
INCLUDES	:=	
DATA		:=
LIB		:=	$(TOPDIR)/lib

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	

CFLAGS	:=	-g -Wall -O3\
		-ffast-math -fno-rtti -fno-exceptions \
		$(ARCH)

CFLAGS	+=	$(INCLUDE) 
CXXFLAGS	:=	$(CFLAGS)

ASFLAGS	:=	-g $(ARCH)

ifneq ($(BUILD),debug)
export OUTBIN	:=	libgme.swc
else
export OUTBIN	:=	libgmed.swc
endif

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(LIBNDS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------


export DEPSDIR := $(CURDIR)/$(BUILD)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))


export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr debug release $(LIB)

all: $(OUTBIN)

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTBIN)	:	$(OFILES) $(LIB)
	rm -f "$(OUTBIN)"
	$(CC) $(OFILES) -swc -o "$(OUTBIN)"
	#$(AR) rcs "$(OUTBIN)" $(OFILES)
	cp "$(OUTBIN)" "../../lib"
	echo built ... $(notdir $@)


-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------

$(LIB):
	mkdir $(LIB)
