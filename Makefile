###############################################################################
#   University of Hawaii, College of Engineering
#   readelf - SRE - Spring 2024
#
### Build and test an ELF parser
###
### @see     https://www.gnu.org/software/make/manual/make.html
###
### @file    Makefile
### @author  Mark Nelson <marknels@hawaii.edu>
###############################################################################

CC     = gcc
CFLAGS = -Wall -Wextra $(DEBUG_FLAGS)

TARGET1=readelf_h
TARGET2=readelf_s

SOURCES=main.c readelf-h.c

OBJECTS1=$(SOURCES:.c=_h.o)
OBJECTS2=$(SOURCES:.c=_s.o)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^

debug: DEBUG_FLAGS = -g -DDEBUG
debug: clean all

# Compile object files for TARGET1
%_h.o: %.c
	$(CC) $(CFLAGS) -DREAD_ELF_HEADER -c $< -o $@

# Compile object files for TARGET2
%_s.o: %.c
	$(CC) $(CFLAGS) -DREAD_ELF_SYMBOLS -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJECTS1) $(OBJECTS2)