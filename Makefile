############################################################################################
# Makefile by EVCHI based on Makefile from CubeIDE and Makefile from
# http://we.easyelectronics.ru/storm_ua/esche-odin-shablon-proekta-pod-stm32-na-gcc.html
#
#	Version 2: Out-of-tree build into $(BUILD_DIR)
#
#	Issue: For some reason AS uses CFLAGS instead of ASFLAGS (CubeIDE generated this!).
#		STMicroelectronics must be asked about that.
#
# 15.04.2020 17:37
############################################################################################

# General
# ------------------------------------------------------------------------------------------
TARGET ?= STM32_generic

CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

DEBUG = 1
OPT = -O1

BUILD_DIR ?= __build__

# Toolchain binaries
# ------------------------------------------------------------------------------------------
AS = arm-none-eabi-gcc -x assembler-with-cpp
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
CP = arm-none-eabi-objcopy
SZ = arm-none-eabi-size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

RM = rm

# Assembler definitions
# ------------------------------------------------------------------------------------------
ASM_DEFS +=

# Assembler include directories
# ------------------------------------------------------------------------------------------
ASM_INCLUDEDIRS +=

# Assembler source directories
# ------------------------------------------------------------------------------------------
ASM_SOURCEDIRS += startup

# C definitions
# ------------------------------------------------------------------------------------------
C_DEFS += 

# C include directories
# ------------------------------------------------------------------------------------------
C_INCLUDEDIRS += core/CMSIS
C_INCLUDEDIRS += core/sys
C_INCLUDEDIRS += core
C_INCLUDEDIRS += drivers
C_INCLUDEDIRS += modules
C_INCLUDEDIRS += main

# C source directories
# ------------------------------------------------------------------------------------------
C_SOURCEDIRS += core/CMSIS
C_SOURCEDIRS += core/sys
C_SOURCEDIRS += core
C_SOURCEDIRS += drivers
C_SOURCEDIRS += modules
C_SOURCEDIRS += main

# GCC settings
# ------------------------------------------------------------------------------------------
# AS FLAGS
# Actually for some reason AS uses CFLAGS (CubeIDE generated this!)
#ASFLAGS += $(MCU)
#ASFLAGS += $(addprefix -D, $(ASM_DEFS))
#ASFLAGS += $(addprefix -I, $(ASM_INCLUDEDIRS))
#ASFLAGS += $(OPT)
#ASFLAGS += -Wall -fdata-sections -ffunction-sections

# C FLAGS
CFLAGS += $(MCU)
CFLAGS += $(addprefix -D, $(C_DEFS))
CFLAGS += $(addprefix -I, $(C_INCLUDEDIRS))
CFLAGS += $(OPT)
CFLAGS += -Wall -fdata-sections -ffunction-sections
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#Linker settings
LIBS = -lc -lm -lnosys 
LIBDIR = 

LDSCRIPT = ld-scripts/STM32F407VGTx_FLASH.ld

LDFLAGS += $(MCU)
LDFLAGS += -specs=nano.specs
LDFLAGS += -T$(LDSCRIPT) $(LIBDIR) $(LIBS)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# Objects list
# ------------------------------------------------------------------------------------------
OBJS += $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(wildcard  $(addsuffix /*.c, $(C_SOURCEDIRS)))))
OBJS += $(addprefix $(BUILD_DIR)/, $(patsubst %.s, %.o, $(wildcard  $(addsuffix /*.s, $(ASM_SOURCEDIRS)))))

# Search paths for make
# ------------------------------------------------------------------------------------------
VPATH += $(C_SOURCEDIRS)
VPATH += $(ASM_SOURCEDIRS)
VPATH += $(BUILD_DIR)

# Files to remove list
# ------------------------------------------------------------------------------------------
#TOREMOVE += $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.hex $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.map
#TOREMOVE += $(addprefix $(BUILD_DIR)/, $(addsuffix /*.o, $(C_SOURCEDIRS)))
#TOREMOVE += $(addprefix $(BUILD_DIR)/, $(addsuffix /*.d, $(C_SOURCEDIRS)))
#TOREMOVE += $(addprefix $(BUILD_DIR)/, $(addsuffix /*.lst, $(C_SOURCEDIRS)))
#TOREMOVE += $(addprefix $(BUILD_DIR)/, $(addsuffix /*.o, $(ASM_SOURCEDIRS)))
#TOREMOVE += $(addprefix $(BUILD_DIR)/, $(addsuffix /*.d, $(ASM_SOURCEDIRS)))

# Default action: build all
# ------------------------------------------------------------------------------------------
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# Rules for creating subdirs if they don't exist
.PRECIOUS: $(BUILD_DIR)/. $(BUILD_DIR)%/.

$(BUILD_DIR)/.:
	@mkdir -p $@

$(BUILD_DIR)%/.:
	@mkdir -p $@

# Compile
# ------------------------------------------------------------------------------------------
.SECONDEXPANSION:
$(BUILD_DIR)/%.o: %.c | $$(@D)/.	# If needed, subdir will be created
	@echo Building file: $<
	@$(CC) $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(<:.c=.lst) -c $< -o $@
	@echo Finished building file: $<

.SECONDEXPANSION:
$(BUILD_DIR)/%.o: %.s | $$(@D)/.	# If needed, subdir will be created
	@echo Building file: $<
	@$(AS) $(CFLAGS) -c $< -o $@
	@echo Finished building file: $<

# .bin
# ------------------------------------------------------------------------------------------
$(BUILD_DIR)/$(TARGET).bin: $(TARGET).elf
	@$(BIN) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# .hex
# ------------------------------------------------------------------------------------------
$(BUILD_DIR)/$(TARGET).hex: $(TARGET).elf
	@$(HEX) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex

# .elf
# ------------------------------------------------------------------------------------------
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo
	@echo Building target: $@
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo Finished building target: $@
	@echo
	@$(SZ) $@

# Clean up
# ------------------------------------------------------------------------------------------
clean:
#	$(RM) -f $(wildcard $(TOREMOVE))
	@$(RM) -fR $(BUILD_DIR)

# Rebuild all
# ------------------------------------------------------------------------------------------
rebuild:
	@echo Error: Not implemented yet. Use clean + build

# Dependencies generated by GCC
# ------------------------------------------------------------------------------------------
-include $(patsubst %.o, %.d, $(OBJS))
