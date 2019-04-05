arduino-builder \
  -compile \
  -hardware /usr/share/arduino/hardware \
  -hardware $HOME/.arduino15/packages \
  -tools /usr/share/arduino/tools-builder \
  -tools $HOME/.arduino15/packages \
  -libraries $HOME/Arduino/libraries \
  -fqbn archlinux-arduino:avr:uno \
  -build-path .build \
  main.ino