include ./config.mk

# Source files
OBJS += src/main.o
OBJS += src/dragon.o
OBJS += src/dfu_mal.o
#OBJS += src/spi_if.o
OBJS += src/flash_if.o
OBJS += src/hw_config.o
OBJS += src/nor_if.o
OBJS += src/usb_desc.o
OBJS += src/usb_istr.o
OBJS += src/usb_prop.o
OBJS += src/usb_pwr.o
OBJS += src/fsmc_nor.o
#OBJS += src/spi_flash.o
#OBJS += src/unzip.o
#OBJS += src/newlib_stubs.o
#OBJS += src/stdio.o
OBJS += src/printf_stdarg.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nor.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_spi_flash.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_i2c_tsensor.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_lcd.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_sdio_sd.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_sram.o
#OBJS += STM32_EVAL/STM3210E_EVAL/stm3210e_eval_fsmc_nand.o
OBJS += startup/stm32f10x_it.o

SRCS := $(OBJS:.o=.c)

# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(SOURCE)))


.PHONY: subdirs $(SUBDIRS) $(LIBS)

# Define Messages.
# English
MSG_BEGIN = -------- begin --------
MSG_END = --------  end  --------



# Rules definition. ***********************************************************

all: begin gccversion $(OUTDIR)/$(PROJECT_NAME).bin post end
	 
$(OUTDIR)/$(PROJECT_NAME).bin : $(OUTDIR)/$(PROJECT_NAME).axf
	$(OBJCOPY) $(OUTDIR)/$(PROJECT_NAME).axf -O binary $(OUTDIR)/$(PROJECT_NAME).bin

$(OUTDIR)/$(PROJECT_NAME).axf : $(OUTDIR)/$(STARTUP_FILE).o $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(OUTDIR)/$(STARTUP_FILE).o $(LIBS) $(LINKER_FLAGS)

$(OUTDIR)/stm32f10x_it.o: ./startup/stm32f10x_it.c
	$(CC) $(CFLAGS) -c ./startup/stm32f10x_it.c -o $(OUTDIR)/stm32f10x_it.o

#$(OUTDIR)/main.o: main.c
#	$(CC) $(CFLAGS) -c main.c -o $(OUTDIR)/main.o

	$(foreach src, $(OBJS:.o=.c), $(CC) $(CFLAGS) -c -o $(src:.c=.o) $(src))
	
$(OUTDIR)/$(STARTUP_FILE).o : ./startup/$(STARTUP_FILE).c $(CONFIG_H_FILES)
	$(CC) -c $(CFLAGS) -O1 ./startup/$(STARTUP_FILE).c -o $(OUTDIR)/$(STARTUP_FILE).o

#$(LIBS):
#	$(MAKE) -C $(SUBDIRS)
#	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir))
./drivers/drivers.a:
	$(MAKE) -C drivers

./zlib/zlib.a:
	$(MAKE) -C zlib
	
clean :
	@rm $(OUTDIR)/$(STARTUP_FILE).o
	@rm $(OBJS)
	$(MAKE) -C $(SUBDIRS) clean
	@rm $(OUTDIR)/$(PROJECT_NAME).axf

# Eye candy.
begin:
##	@echo
	@echo $(MSG_BEGIN)

end:
	@echo $(MSG_END)
##	@echo

post:
	arm-none-eabi-size --format=berkeley $(OUTDIR)/$(PROJECT_NAME).axf 

# Display compiler version information.
gccversion :
	@$(CC) --version

$(shell mkdir $(OUTDIR) 2>NUL)