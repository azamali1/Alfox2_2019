ifeq ($(OS),Windows_NT)
SHELL = cmd
RMDIR = rmdir /s /q
RM = del /q
mymkdir = if not exist "$1" mkdir "$1"
else
RMDIR = rm -fr
RM = rm -f
mymkdir = mkdir -p $1
endif

PROJECT_OBJS = \
	project/LedTri.cpp.o \
	project/test_led_tri.cpp.o \

PLATFORM_CORE_OBJS = \
	core/delay.c.o \
	core/pulse_asm.S.o \
	core/Stream.cpp.o \
	core/wiring_shift.c.o \
	core/itoa.c.o \
	core/new.cpp.o \
	core/hooks.c.o \
	core/avr/dtostrf.c.o \
	core/abi.cpp.o \
	core/cortex_handlers.c.o \
	core/IPAddress.cpp.o \
	core/Tone.cpp.o \
	core/pulse.c.o \
	core/WMath.cpp.o \
	core/wiring_analog.c.o \
	core/USB/samd21_host.c.o \
	core/USB/PluggableUSB.cpp.o \
	core/USB/USBCore.cpp.o \
	core/USB/CDC.cpp.o \
	core/wiring_digital.c.o \
	core/wiring.c.o \
	core/Print.cpp.o \
	core/startup.c.o \
	core/main.cpp.o \
	core/WInterrupts.c.o \
	core/SERCOM.cpp.o \
	core/wiring_private.c.o \
	core/Uart.cpp.o \
	core/WString.cpp.o \
	core/Reset.cpp.o \

PLATFORM_VARIANT_OBJS = \
	variant/variant.cpp.o \

LIBRARIES_OBJS = \

TARGETS = \
	test_led_tri.hex \
	test_led_tri.bin \

all: $(TARGETS)

test_led_tri.hex: test_led_tri.elf
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-objcopy" -O ihex -R .eeprom  "./test_led_tri.elf" "./test_led_tri.hex"

test_led_tri.bin: test_led_tri.elf
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-objcopy" -O binary  "./test_led_tri.elf" "./test_led_tri.bin"

test_led_tri.elf: $(PROJECT_OBJS) $(LIBRARIES_OBJS) core.a
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++"  "-L." -Os -Wl,--gc-sections -save-temps  "-T/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200/linker_scripts/gcc/flash_with_bootloader.ld" "-Wl,-Map,./test_led_tri.map" --specs=nano.specs --specs=nosys.specs -mcpu=cortex-m0plus -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -o "./test_led_tri.elf" $(PROJECT_OBJS) $(LIBRARIES_OBJS) -Wl,--start-group "-L/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Lib/GCC/" -larm_cortexM0l_math -lm "./core.a" -Wl,--end-group

core.a:	$(PLATFORM_CORE_OBJS) $(PLATFORM_VARIANT_OBJS)

clean:
	-$(RMDIR) project core variant libraries
	-$(RM) *.hex *.eep *.bin *.elf *.a *.ar *.d

size:
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-size" -A "./test_led_tri.elf"

project/LedTri.cpp.o: ../../LedTri.cpp project/LedTri.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"

project/LedTri.cpp.d: ;

-include project/LedTri.cpp.d 

project/test_led_tri.cpp.o: ../../test_led_tri.cpp project/test_led_tri.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"

project/test_led_tri.cpp.d: ;

-include project/test_led_tri.cpp.d 


core/delay.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/delay.c core/delay.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/delay.c.d: ;

-include core/delay.c.d

core/pulse_asm.S.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/pulse_asm.S
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -c -g -x assembler-with-cpp -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/Stream.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/Stream.cpp core/Stream.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/Stream.cpp.d: ;

-include core/Stream.cpp.d

core/wiring_shift.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/wiring_shift.c core/wiring_shift.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/wiring_shift.c.d: ;

-include core/wiring_shift.c.d

core/itoa.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/itoa.c core/itoa.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/itoa.c.d: ;

-include core/itoa.c.d

core/new.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/new.cpp core/new.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/new.cpp.d: ;

-include core/new.cpp.d

core/hooks.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/hooks.c core/hooks.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/hooks.c.d: ;

-include core/hooks.c.d

core/avr/dtostrf.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/avr/dtostrf.c core/avr/dtostrf.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/avr/dtostrf.c.d: ;

-include core/avr/dtostrf.c.d

core/abi.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/abi.cpp core/abi.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/abi.cpp.d: ;

-include core/abi.cpp.d

core/cortex_handlers.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/cortex_handlers.c core/cortex_handlers.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/cortex_handlers.c.d: ;

-include core/cortex_handlers.c.d

core/IPAddress.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/IPAddress.cpp core/IPAddress.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/IPAddress.cpp.d: ;

-include core/IPAddress.cpp.d

core/Tone.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/Tone.cpp core/Tone.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/Tone.cpp.d: ;

-include core/Tone.cpp.d

core/pulse.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/pulse.c core/pulse.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/pulse.c.d: ;

-include core/pulse.c.d

core/WMath.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/WMath.cpp core/WMath.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/WMath.cpp.d: ;

-include core/WMath.cpp.d

core/wiring_analog.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/wiring_analog.c core/wiring_analog.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/wiring_analog.c.d: ;

-include core/wiring_analog.c.d

core/USB/samd21_host.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/USB/samd21_host.c core/USB/samd21_host.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/USB/samd21_host.c.d: ;

-include core/USB/samd21_host.c.d

core/USB/PluggableUSB.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/USB/PluggableUSB.cpp core/USB/PluggableUSB.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/USB/PluggableUSB.cpp.d: ;

-include core/USB/PluggableUSB.cpp.d

core/USB/USBCore.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/USB/USBCore.cpp core/USB/USBCore.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/USB/USBCore.cpp.d: ;

-include core/USB/USBCore.cpp.d

core/USB/CDC.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/USB/CDC.cpp core/USB/CDC.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/USB/CDC.cpp.d: ;

-include core/USB/CDC.cpp.d

core/wiring_digital.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/wiring_digital.c core/wiring_digital.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/wiring_digital.c.d: ;

-include core/wiring_digital.c.d

core/wiring.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/wiring.c core/wiring.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/wiring.c.d: ;

-include core/wiring.c.d

core/Print.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/Print.cpp core/Print.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/Print.cpp.d: ;

-include core/Print.cpp.d

core/startup.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/startup.c core/startup.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/startup.c.d: ;

-include core/startup.c.d

core/main.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/main.cpp core/main.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/main.cpp.d: ;

-include core/main.cpp.d

core/WInterrupts.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/WInterrupts.c core/WInterrupts.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/WInterrupts.c.d: ;

-include core/WInterrupts.c.d

core/SERCOM.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/SERCOM.cpp core/SERCOM.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/SERCOM.cpp.d: ;

-include core/SERCOM.cpp.d

core/wiring_private.c.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/wiring_private.c core/wiring_private.c.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-gcc" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"
	
core/wiring_private.c.d: ;

-include core/wiring_private.c.d

core/Uart.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/Uart.cpp core/Uart.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/Uart.cpp.d: ;

-include core/Uart.cpp.d

core/WString.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/WString.cpp core/WString.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/WString.cpp.d: ;

-include core/WString.cpp.d

core/Reset.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino/Reset.cpp core/Reset.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

core/Reset.cpp.d: ;

-include core/Reset.cpp.d


variant/variant.cpp.o: /home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200/variant.cpp variant/variant.cpp.d
	@$(call mymkdir,$(dir $@))
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10608 -DARDUINO_SAMD_MKRFox1200 -DARDUINO_ARCH_SAMD  -DUSE_ARDUINO_MKR_PIN_LAYOUT -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8050 -DUSBCON '-DUSB_MANUFACTURER="Arduino LLC"' '-DUSB_PRODUCT="Arduino MKR FOX 1200"' "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS/4.5.0/CMSIS/Include/" "-I/home/snir2g2/.arduinocdt/packages/arduino/tools/CMSIS-Atmel/1.1.0/CMSIS/Device/ATMEL/" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/cores/arduino" -I"/home/snir2g2/.arduinocdt/packages/arduino/hardware/samd/1.6.20/variants/mkrfox1200" "$<" -o "$@"
	"/home/snir2g2/.arduinocdt/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "./core.a" "$@"

variant/variant.cpp.d: ;

-include variant/variant.cpp.d


