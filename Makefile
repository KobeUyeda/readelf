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


TARGET = wc

all: $(TARGET)

CC     = gcc
CFLAGS = -Wall -Wextra $(DEBUG_FLAGS)

debug: DEBUG_FLAGS = -g -DDEBUG
debug: clean $(TARGET)

wc: wc.c
	$(CC) $(CFLAGS) -o $(TARGET) wc.c

test: wc
	./wc /etc/passwd

clean:
	rm -f $(TARGET) *.o
