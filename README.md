AyRTOS
======

AyRTOS is a simple RTOS targeting Arduino boards, developped as a self-educational project.

It is designed to run on Arduino boards using only the standard C functions, and therefore does not use the Arduino libraries. We chose Arduino because it is a development platform which is widely available, easy to use and extend, and cheap enough for our needs.

AyRTOS is running only on the Arduino Uno (Atmel ATmega328P) for now, but ultimately it will be possible to port it to any architecture.

v1.0 will include :

* preemptive multitasking
* drivers for the ATmega328P peripherals (USART, SPI, I2C, ADC...)
* drivers for 16x2 LCD screens
