# makefile for arm iar toolchain
AS = iasmarm
LD = ilinkarm
OBJCOPY = ielftool --silent
SIZE = size

# Enable extension mode (gcc compatible)
CFLAGS += -e --debug --silent

# silent mode
ASFLAGS += -S $(addprefix -I,$(INC))
