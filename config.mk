# Project name
PROJECT_NAME=BootloaderDFU

# Board support
#BOARD_SUPPORT = USE_STM3210E_EVAL
BOARD_SUPPORT = USE_DRAGON_BOARD

CONFIG_STM32_DRIVERS = y
CONFIG_STM32_USB_DRIVERS = y
CONFIG_FSMC_DRAGON = y
CONFIG_SERIAL_DRAGON = y
#CONFIG_ZLIB = y

# Directory for output files (lst, obj, dep, elf, sym, map, hex, bin etc.).
OUTDIR = ./bin

SUBDIRS += drivers
#SUBDIRS += zlib

# Toolchain definition.
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-size
NM = arm-none-eabi-nm

LDSCRIPT = ./startup/stm32_flash.ld

# Startup file without extension!
STARTUP_FILE = startup_stm32f10x

# should use --gc-sections but the debugger does not seem to be able to cope with the option.
LINKER_FLAGS += -nostartfiles 
LINKER_FLAGS += -Xlinker -o$(OUTDIR)/$(PROJECT_NAME).axf 
LINKER_FLAGS += -Xlinker -M 
LINKER_FLAGS += -Xlinker -Map=$(PROJECT_NAME).map 
LINKER_FLAGS += -Xlinker --no-gc-sections
LINKER_FLAGS += -T$(LDSCRIPT)



# Debugging format.
#DEBUG = stabs
#DEBUG = dwarf-2
DEBUG= gdb

# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = 0


# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = gnu99

ARFLAGS = cr

TOP_DIR = /home/grzybek/workspace/BootloaderDFU

# Includes folder
INCLUDES += $(TOP_DIR)/includes/stm32f10x_drivers
INCLUDES += $(TOP_DIR)/startup
INCLUDES += $(TOP_DIR)/includes/STM32_USB-FS-Device_Driver
INCLUDES += $(TOP_DIR)/includes/
INCLUDES += $(TOP_DIR)/includes/serial
INCLUDES += $(TOP_DIR)/includes/fsmc

# Compiler flags definition.
CFLAGS += -g$(DEBUG)
CFLAGS += -O$(OPT)
CFLAGS += -std=$(CSTANDARD)
#CFLAGS += -T$(LDSCRIPT)
CFLAGS += -I $(TOP_DIR)/includes/stm32f10x_drivers
CFLAGS += -I $(TOP_DIR)/startup
#CFLAGS += -I $(TOP_DIR)/zlib
CFLAGS += -I $(TOP_DIR)/includes/STM32_USB-FS-Device_Driver
CFLAGS += -I $(TOP_DIR)/includes/
CFLAGS += -I $(TOP_DIR)/includes/serial
CFLAGS += -I $(TOP_DIR)/includes/fsmc
CFLAGS += -I $(TOP_DIR)/STM32_EVAL/STM3210E_EVAL
CFLAGS += -I $(TOP_DIR)/STM32_EVAL/Common
CFLAGS += -D $(BOARD_SUPPORT)
CFLAGS += -D STM32F10X_HD
CFLAGS += -D USE_STDPERIPH_DRIVER
CFLAGS += -D VECT_TAB_FLASH
CFLAGS += -D GCC_ARMCM3
CFLAGS += -D inline=
CFLAGS += -D PACK_STRUCT_END=__attribute\(\(packed\)\)
CFLAGS += -D ALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\)
CFLAGS += -mthumb
CFLAGS += -mcpu=cortex-m3
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections

LIBS+=./drivers/drivers.a
#LIBS+=./zlib/zlib.a
