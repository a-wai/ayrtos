MCU         = atmega328p
TARGET_ARCH = -mmcu=$(MCU)
CC          = avr-gcc
CPPFLAGS    = $(TARGET_ARCH) -I. -I.. -DATMEGA328P -DF_CPU=16000000
CFLAGS      = -Wall -Os
C_SRCS      = $(wildcard *.c)
OBJ_FILES   = $(C_SRCS:.c=.o)

all: $(OBJ_FILES)

clean:
	rm -rf *.o

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@
