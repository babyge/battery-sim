ROOT_DIR = $(CURDIR)

TARGET:=glue
TOOLCHAIN_ROOT:=/usr
TOOLCHAIN_PATH:=$(TOOLCHAIN_ROOT)/bin
TOOLCHAIN_PREFIX:=arm-none-eabi

# Optimization level, can be [0, 1, 2, 3, s].
OPTLVL:=3
DBG:=-g
#INSTRUMENTATION := -finstrument-functions

STARTUP	:= $(ROOT_DIR)/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc

MODULES+= Src \
	Drivers/STM32F0xx_HAL_Driver/Src \

INC_DIRS+= Inc \
	Drivers/CMSIS/Device/ST/STM32F0xx/Include \
	Drivers/CMSIS/Include \
	Drivers/STM32F0xx_HAL_Driver/Inc \


LINKER_SCRIPT:=$(ROOT_DIR)/SW4STM32/cubeMX/STM32F030C8Tx_FLASH.ld


SRC_DIRS:= $(addprefix $(ROOT_DIR)/,$(MODULES))
INC_DIRS+= $(MODULES)
INCLUDE+= $(addprefix -I$(ROOT_DIR)/,$(INC_DIRS))


BUILD_BASE = $(CURDIR)/build
BIN_DIR = $(CURDIR)/binary

BUILD_DIR := $(addprefix $(BUILD_BASE)/,$(MODULES))

# vpath is used so object files are written to the current directory instead
# of the same directory as their source files
#vpath %.c $(ROOT_DIR)/$(FREERTOS)/portable/MemMang \
#	$(ROOT_DIR)/$(FATFS)/drivers \
#	$(ROOT_DIR)/$(FATFS)/option \
#	$(ROOT_DIR)/core/net/mac/



#vpath %.s $(STARTUP)
ASRC=startup_stm32f030x8.s

# miniDTN files
SRC := $(foreach sdir,$(MODULES),$(wildcard $(sdir)/*.c))

CDEFS+= -DSTM32F030x8
CDEFS+= -DUSE_HAL_DRIVER
CDEFS+= -DSTM32F0XX

MCUFLAGS=-O$(OPTLVL) $(DBG) -MMD -std=gnu11 -Wall -Wextra -Wno-unused-parameter -fdata-sections -ffunction-sections -Wno-old-style-declaration -mcpu=cortex-m0 -mthumb 
CFLAGS+=$(MCUFLAGS) $(INCLUDE) $(CDEFS)

LDLIBS=-lc -lm -lnosys
LDFLAGS=$(MCUFLAGS) -T$(LINKER_SCRIPT) $(LDLIBS) -Wl,--gc-sections

CC=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-gcc
LD=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-gcc
OBJCOPY=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-objcopy
AS=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-as
AR=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-ar
GDB=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-gdb
SIZE=$(TOOLCHAIN_PATH)/$(TOOLCHAIN_PREFIX)-size

OBJ = $(SRC:%.c=$(BUILD_BASE)/%.o)

all: checkdirs $(OBJ)
	@echo [AS] $(ASRC)
	@$(AS) -o $(ASRC:%.s=$(BUILD_BASE)/%.o) $(STARTUP)/$(ASRC)
	@echo [LD] $(TARGET).elf
	@$(CC) -o $(BIN_DIR)/$(TARGET).elf $(LDFLAGS) $(OBJ) $(ASRC:%.s=$(BUILD_BASE)/%.o)
	@echo [OBJCOPY] $(TARGET).hex
	@$(OBJCOPY) -O ihex $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex
	@echo [OBJCOPY] $(TARGET).bin
	@$(OBJCOPY) -O binary $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin
	@$(SIZE) -A -x $(BIN_DIR)/$(TARGET).elf | grep "\.text\|\.data\|\.bss"

-include $(OBJ:.o=.d)

$(BUILD_BASE)/%.o: %.c
	@echo [CC] $(INSTRUMENTATION) $(notdir $<)
	@$(CC) $(CFLAGS) $(INSTRUMENTATION) $< -c -o $@

checkdirs: $(BUILD_DIR) $(BIN_DIR)
#	@echo $(SRC)


$(BUILD_DIR) $(BIN_DIR):
	$(Q) mkdir -p $@


.PHONY: clean

clean:
	@echo [RM] OBJ
	@rm -f $(OBJ)
	@rm -f $(OBJ:.o=.d)
	@rm -f $(ASRC:%.s=$(BUILD_BASE)/%.o)
	@echo [RM] BIN
	@rm -f $(BIN_DIR)/$(TARGET).elf
	@rm -f $(BIN_DIR)/$(TARGET).hex
	@rm -f $(BIN_DIR)/$(TARGET).bin


flash: all
	@st-flash --reset write $(BIN_DIR)/$(TARGET).bin 0x8000000

startgdb:
	st-util -m &
	sleep 1

stopgdb:
	killall st-util

debug: startgdb
	$(GDB) --args $(BIN_DIR)/$(TARGET).elf target extended remote :4242 b main
	killall st-util

idedebug: startgdb
	qtcreator -debug $(BIN_DIR)/$(TARGET).elf,server=:4242 ./minidtn.creator
	killall st-util
