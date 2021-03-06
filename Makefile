TTY = /dev/ttyACM0
MCU         = atmega328p
TARGET_ARCH = -mmcu=$(MCU)
TARGET      = kernel
CC          = avr-gcc
CPPFLAGS    = -mmcu=$(MCU) -I. -I.. -DATMEGA328P -DF_CPU=16000000
CFLAGS      = -Wall -Os
LDFLAGS     = -mmcu=$(MCU) -lm -Wl,--gc-sections -Os
PGMER       = -c arduino -b 115200 -P $(TTY)
DUDE        = avrdude -V -p $(MCU) 
C_SRCS      = $(wildcard *.c)
OBJ_FILES   = \
	kernel/kernel.o \
	kernel/sched.o \
	kernel/task.o \
	util/str.o \
	driver/adc.o \
	driver/mcu.o \
	driver/serial.o \
	driver/timer.o \
	arch/avr/atmega328p/timer.o \
	arch/avr/atmega328p/adc.o \
	arch/avr/atmega328p/mcu.o \
	arch/avr/atmega328p/usart.o \
	apps/sample.o

all: $(TARGET).hex

clean:
	rm -rf $(TARGET).elf *.hex
	make -C driver clean
	make -C kernel clean
	make -C util clean
	make -C arch/avr/atmega328p clean
	make -C apps clean

$(TARGET).elf: $(OBJ_FILES)
	make -C driver
	make -C kernel
	make -C util
	make -C arch/avr/atmega328p
	make -C apps
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)
	
$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	$(DUDE) $(PGMER) -U flash:w:$(TARGET).hex
	
size: $(TARGET).elf
	avr-size --format=avr --mcu=$(MCU) $(TARGET).elf
