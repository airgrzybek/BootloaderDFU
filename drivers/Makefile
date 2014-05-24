# drivers makefile

include ../config.mk

LIB := drivers.a

# ST Library source files.
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/core_cm3.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/system_stm32f10x.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/misc.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_rcc.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_gpio.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_spi.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_tim.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_usart.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_fsmc.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_flash.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_exti.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_dma.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_sdio.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_i2c.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_adc.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_rtc.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_pwr.o 
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/stm32f10x_bkp.o
COBJS-$(CONFIG_STM32_DRIVERS) += stm32f10x_drivers/system_stm32f10x.o

COBJS-$(CONFIG_STM32_USB_DRIVERS) += STM32_USB-FS-Device_Driver/usb_core.o
COBJS-$(CONFIG_STM32_USB_DRIVERS) += STM32_USB-FS-Device_Driver/usb_init.o
COBJS-$(CONFIG_STM32_USB_DRIVERS) += STM32_USB-FS-Device_Driver/usb_int.o
COBJS-$(CONFIG_STM32_USB_DRIVERS) += STM32_USB-FS-Device_Driver/usb_mem.o
COBJS-$(CONFIG_STM32_USB_DRIVERS) += STM32_USB-FS-Device_Driver/usb_regs.o
COBJS-$(CONFIG_STM32_USB_DRIVERS) += STM32_USB-FS-Device_Driver/usb_sil.o

COBJS-$(CONFIG_SERIAL_DRAGON) += serial/dragon_serial.o

COBJS-$(CONFIG_FSMC_DRAGON) += fsmc/dragon_fsmc_nor.o
COBJS-$(CONFIG_FSMC_DRAGON) += fsmc/dragon_fsmc_sram.o

COBJS	:= $(COBJS-y)

SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(COBJS)

all:	$(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) 

clean:
	@rm -f $(OBJS)
	@rm -f $(LIB)
