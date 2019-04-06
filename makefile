ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF = /etc/avrdude.conf
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/cores/arduino
BOARDS_TXT = /usr/share/arduino/hardware/archlinux-arduino/avr/boards.txt
ARDUINO_VAR_PATH = /usr/share/arduino/hardware/archlinux-arduino/avr/variants
BOOTLOADER_PARENT = /usr/share/arduino/hardware/archlinux-arduino/avr/bootloaders


BOARD_TAG    = uno
ARDUINO_LIBS =

ISP_PROG = usbasp-clone
ISP_PORT = USB

include /usr/share/arduino/Arduino.mk

ispupload:
		sudo avrdude -p m328p -c $(ISP_PROG) -P $(ISP_PORT) -U $(OBJDIR)/p5-avr-base.elf