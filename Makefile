#-------------------------------------------------------------------------------
# Makefile @ Denis Zheleznyakov http://ziblog.ru
#-------------------------------------------------------------------------------

SRC_C  = main.c

ifeq ($(MCU),STM32F107VCT6)

MCU_CORE = 3

SRC_C +=

SRC_ASM += stm32f10x_cl.s

LINKER_SCRIPT = 'mcu/startup/stm32f107vc_main.ld'

INCLUDES += -Imcu/std_lib/stm32f10x/inc
INCLUDES += -Imcu/std_lib/stm32f10x/src

VPATH += mcu/std_lib/stm32f10x/inc
VPATH += mcu/std_lib/stm32f10x/src

endif

GCC_PATH = D:/tools/codesourcery/2013-05-23
GCC_PREFIX = $(GCC_PATH)/bin/arm-none-eabi-

INCLUDES += -I$(GCC_PATH)/arm-none-eabi/include
INCLUDES += -I$(GCC_PATH)/arm-none-eabi/include/lib
INCLUDES += -Ibootloader
INCLUDES += -Idevice
INCLUDES += -Imcu
INCLUDES += -Imcu/core
INCLUDES += -Imcu/peripherals
INCLUDES += -Imcu/startup
INCLUDES += -Iutility

VPATH += $(GCC_PATH)/arm-none-eabi/include
VPATH += bootloader
VPATH += device
VPATH += mcu
VPATH += mcu/core
VPATH += mcu/peripherals
VPATH += mcu/peripherals/lcd
VPATH += mcu/startup
VPATH += utility

FLAGS_C += $(INCLUDES) -I.
FLAGS_C += -Os
FLAGS_C += -gdwarf-2 -g3
FLAGS_C += -Wall
FLAGS_C += -c
FLAGS_C += -fmessage-length=0
FLAGS_C += -fno-builtin
FLAGS_C += -ffunction-sections
FLAGS_C += -fdata-sections
FLAGS_C += -msoft-float
FLAGS_C += -mapcs-frame
FLAGS_C += -D__thumb2__=1
FLAGS_C += -mno-sched-prolog
FLAGS_C += -fno-hosted
FLAGS_C += -mtune=cortex-m$(MCU_CORE) -mcpu=cortex-m$(MCU_CORE)
FLAGS_C += -mthumb
FLAGS_C += -mfix-cortex-m3-ldrd
FLAGS_C += -fno-strict-aliasing
FLAGS_C += -ffast-math
FLAGS_C += -std=c99
FLAGS_C += -DARM_MATH_CM$(MCU_CORE)

FLAGS_LD += -Xlinker -Map=target/target.map
FLAGS_LD += -Wl,--gc-sections
FLAGS_LD += -mcpu=cortex-m$(MCU_CORE)
FLAGS_LD += -mthumb

FLAGS_ASM  = -D__ASSEMBLY__
FLAGS_ASM += -g $(FLAGS_C)
FLAGS_ASM += -I. -x assembler-with-cpp

all: clean
	@make MCU=STM32F107VCT6 -s -j job_main
	
job_main: main.elf

main.elf: $(SRC_ASM:%.S=target/%.o) $(SRC_C:%.c=target/%.o)
	@echo Linking: $@
	@$(GCC_PREFIX)gcc.exe $(FLAGS_LD) -T$(LINKER_SCRIPT) -o 'target/$@' $^ $(LIB_LD)	
	@$(GCC_PREFIX)size 'target/main.elf'
	@$(GCC_PREFIX)objcopy -O ihex 'target/main.elf' 'target/main.hex'
	@$(GCC_PREFIX)objdump -h -S -z 'target/main.elf' > 'target/main.lss'
	@$(GCC_PREFIX)nm -S -n 'target/main.elf' > 'target/main.sym'
	@rm -f target/*.o
	@rm -f target/*.map

$(SRC_C:%.c=target/%.o): target/%.o: %.c
	@echo Compiling: $<
	@$(GCC_PREFIX)gcc.exe $(FLAGS_C) -c $< -o $@


$(SRC_ASM:%.s=target/%.o): target/%.o: %.s
	@echo Compiling asm: $<
	@$(GCC_PREFIX)gcc.exe $(FLAGS_ASM) -c $< -o $@
	
clean:
	@mkdir -p target
	@rm -f target/*.*