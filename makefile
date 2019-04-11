ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF = /etc/avrdude.conf
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/cores/arduino
BOARDS_TXT = /usr/share/arduino/hardware/archlinux-arduino/avr/boards.txt
ARDUINO_VAR_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/variants
BOOTLOADER_PARENT = /usr/share/arduino/hardware/archlinux-arduino/avr/bootloaders

### CXXFLAGS_STD
### Set the C++ standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cxxflags_std)
CXXFLAGS_STD      = -std=gnu++17

### CXXFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS         += -pedantic -Wall -Wextra

BOARD_TAG    = uno
ARDUINO_LIBS =

ISP_PROG = usbasp-clone
ISP_PORT = USB

MONITOR_BAUDRATE = 115200

include /usr/share/arduino/Arduino.mk

ispupload:
		sudo avrdude -p m328p -c $(ISP_PROG) -P $(ISP_PORT) -U $(OBJDIR)/p5-avr-base.elf

fuseupload:
		sudo avrdude -p m328p -c $(ISP_PROG) -P $(ISP_PORT) -U lfuse:w:fuses/low_fuse_val.hex:h -U hfuse:w:fuses/high_fuse_val.hex:h