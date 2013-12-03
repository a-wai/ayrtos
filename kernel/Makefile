MCU         = atmega328p
TARGET_ARCH = -mmcu=$(MCU)
TARGET      = kernel
CC          = avr-gcc
CPPFLAGS    = -mmcu=$(MCU) -I. -I.. -DATMEGA328P -DF_CPU=16000000
CFLAGS      = -Wall -Os
LDFLAGS     = -mmcu=$(MCU) -lm -Wl,--gc-sections -Os
PGMER       = -c arduino -b 115200 -P $(TTY)
DUDE        = avrdude -V -p $(MCU) $(DUDECFG)
C_SRCS      = $(wildcard *.c)
OBJ_FILES   = $(C_SRCS:.c=.o)

all: $(OBJ_FILES)

clean:
	rm -rf *.o

asm:
	$(CC) -S $(CPPFLAGS) $(CFLAGS) task.c -o task.s

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@
