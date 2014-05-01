include $(srctree)/arch/arm/mach-berlin/mv88de3100.mk

MWD=$(srctree)/arch/arm/mach-berlin
PWD=$(MWD)/modules/vpp_fb

HEADER_PATH :=  \
	-I$(MWD)/include \
	-I$(MWD)/include/mach \
	-I$(MWD)/modules/shm \
	-I$(MWD)/modules/cc  \
	-I$(MWD)/modules/nfc \
	-I$(MWD)/modules/pe \
	-I$(MWD)/modules/pe/gsinc \
	-I$(MWD)/modules/pe/gsinc/$(FIRMWARE) \
	-I$(PWD)/Common/include \
	-I$(PWD)/Common/include/$(FIRMWARE)

ccflags-y	+= -DLOGO_ENABLE_MAIN=1 -DLOGO_ENABLE_PIP=0 -DLOGO_ENABLE_AUX=0
#ccflags-y	+= -DLOGO_PROC_FS=1 -DLOGO_TIME_PROFILE=1
ccflags-y	+= $(MV_DEFINE) $(HEADER_PATH)

ccflags-y	+= -I$(PWD)/THINVPP/source/include/include_BG2_A0

ccflags-y 	+= -I$(PWD)/AVPLL/include
ccflags-y 	+= -I$(PWD)/THINVPP/include
ccflags-y 	+= -I$(PWD)/THINVPP/source/include
ccflags-y 	+= -I$(PWD)/THINVPP/source/BE/include
ccflags-y 	+= -I$(PWD)/THINVPP/source/CPCB/include
ccflags-y 	+= -I$(PWD)/THINVPP/source/FE/include
ccflags-y 	+= -I$(PWD)/THINVPP/source/MISC/include
ccflags-y 	+= -I$(PWD)/THINVPP/source/SCL/include
asflags-y 	+= -I$(PWD)

FASTLOGO_SOURCE += $(wildcard $(PWD)/AVPLL/source/*.c)
FASTLOGO_SOURCE += $(wildcard $(PWD)/THINVPP/source/*.c)
FASTLOGO_SOURCE += $(wildcard $(PWD)/THINVPP/source/BE/source/*.c)
FASTLOGO_SOURCE += $(wildcard $(PWD)/THINVPP/source/CPCB/source/*.c)
FASTLOGO_SOURCE += $(wildcard $(PWD)/THINVPP/source/FE/source/*.c)
FASTLOGO_SOURCE += $(wildcard $(PWD)/THINVPP/source/MISC/source/*.c)
FASTLOGO_SOURCE += $(wildcard $(PWD)/THINVPP/source/SCL/source/*.c)

FASTLOGO_OBJ += $(patsubst $(PWD)/%.c,%.o,$(FASTLOGO_SOURCE))
ifeq ($(CONFIG_BERLIN_PE),y)
#use the avio_dhub_drv in pe module
else
FASTLOGO_OBJ += DHUB/source/avio_dhub_drv.o
endif

obj-$(CONFIG_BERLIN_FBDEV) += galois_fastlogo.o
galois_fastlogo-objs := vpp_fb.o $(FASTLOGO_OBJ)
