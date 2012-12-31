# ============================================================================
# Makefile
#
# Author: 
# ============================================================================
#
# Project Info
# -----------------------------------------------------------------------------
PROJECT		= avarice
AUTHOR		= 
#
# Helpers
# -----------------------------------------------------------------------------
GIT_REV		:= $(shell git describe --tags --dirty)
#FIXME
MAJ_REV		:= 1
DATE		:= $(shell date +%y%m%d)
HERE		:= $(shell pwd)
#
# Sources
# -----------------------------------------------------------------------------
SRC		= $(addprefix src/, main.c)
RES		= $(addprefix res/, build_desc.res)
CFG_FILES	= 
MODS_DIR	= /usr/local/modules
MODS		:= $(shell ls -p mod/ | grep /)
# Objects
# -----------------------------------------------------------------------------
OBJ		= $(SRC:.c=.o)
REL_OBJ		= $(addprefix .rel/, $(notdir $(OBJ)))
DBG_OBJ		= $(addprefix .dbg/, $(notdir $(OBJ)))
RES_OBJ		= $(addprefix .res/, $(notdir $(RES:.res=.o)))
#
# Binaries
# -----------------------------------------------------------------------------
BIN_DIR		= /usr/local/bin
REL_BIN		= $(BIN_DIR)/$(PROJECT)
DBG_BIN	 	= $(BIN_DIR)/$(PROJECT)_debug
BIN_FMT		= elf64-x86-64
#
# Etc.
# -----------------------------------------------------------------------------
ARC_DIR		= ~/archive
PKG_DIR		= ~/pkg
#
# Compiler Settings
# -----------------------------------------------------------------------------
CC		= gcc
STD_CFLAGS	= -c -Iinclude -I/usr/local/include -Wall -pedantic -std=gnu99
CDEFS		= -D GIT_REV=$(GIT_REV) -D MOD_PATH=$(MODS_DIR)
REL_CFLAGS	= -O2
DBG_CFLAGS	= -g -D BUILD_DEBUG
#
# Linker Settings
# -----------------------------------------------------------------------------
LDFLAGS		= -L/usr/local/lib64
#
# Make
# -----------------------------------------------------------------------------
all: debug release

debug: CFLAGS = $(STD_CFLAGS) $(DBG_CFLAGS)
debug: $(src) $(DBG_BIN) $(CFG_FILES)

release: CFLAGS = $(STD_CFLAGS) $(REL_CFLAGS)
release: $(src) $(REL_BIN) $(CFG_FILES)

export: release
	gpg -s $(REL_BIN)
export: package

.PHONY: modules
modules:
	@cd mod;\
	for DIR in $(MODS); do\
		echo -e "\nMaking $$DIR\n------------------------------------";\
		cd $$DIR;\
		$(MAKE) clean all;\
		cd ..;\
	done;\
	echo "";\
	
clean:
	rm -rf $(REL_OBJ) $(DBG_OBJ) $(RES_OBJ) $(DBG_BIN) $(REL_BIN)

.PHONY: archive
archive:
	mkdir -p $(ARC_DIR)
	tar -cvvJf $(ARC_DIR)/$(PROJECT)_$(GIT_REV)_$(DATE).pkg.tar.xz \
		../$(PROJECT)

package: debug release
	mkdir -p $(PKG_DIR)
	tar -cvvpJf $(PKG_DIR)/$(PROJECT)_$(GIT_REV)_$(DATE).tar.xz \
		$(REL_BIN) $(DBG_BIN) $(CFG_FILES) $(MODS_DIR)

todo:
	@grep -n FIXME $(SRC) 2> /dev/null || true
	@grep -n HACK $(SRC) 2> /dev/null || true
	@grep -n TODO $(SRC) 2> /dev/null || true

info:
	@wc -l $(SRC) 2> /dev/null || true

$(CFG_FILES): $(addprefix skel/, $(notdir $(CFG_FILES)))
	@if [ -a $@ ]; then \
		mv $@ $@.save; \
	fi;
	cp skel/$(notdir $<) $@

$(DBG_BIN): $(DBG_OBJ) $(RES_OBJ)
	$(CC) $(DBG_OBJ) $(RES_OBJ) $(LDFLAGS) -o $@

$(REL_BIN): $(REL_OBJ) $(RES_OBJ)
	$(CC) $(REL_OBJ) $(RES_OBJ) $(LDFLAGS) -o $@

.dbg/%.o: src/%.c
	@mkdir -p .dbg
	$(CC) $(CFLAGS) $(CDEFS) $< -o $@

.rel/%.o: src/%.c
	@mkdir -p .rel
	$(CC) $(CFLAGS) $(CDEFS) $< -o $@

.PHONY: res/build_desc.res
res/build_desc.res:
	@echo -ne "Project: \t" > $@
	@echo $(PROJECT) >> $@
	@echo -ne "Author: \t" >> $@
	@echo $(AUTHOR) >> $@
	@echo -ne "Revision: \t" >> $@
	@echo $(GIT_REV) >> $@
	@echo -ne "Date: \t\t" >> $@
	@echo $(shell date) >> $@
	@echo -ne "CFLAGS: \t" >> $@
	@echo $(CFLAGS) >> $@
	@echo -ne "LDFLAGS: \t" >> $@
	@echo $(LDFLAGS) >> $@
	@echo -ne "User: \t\t" >> $@
	@echo $(shell whoami) >> $@
	@echo -ne "System: \t" >> $@
	@echo -n $(shell uname -mn) >> $@


.res/%.o: res/%.res
	@mkdir -p .res
	objcopy --input binary --output $(BIN_FMT) --binary-architecture i386 $< $@


