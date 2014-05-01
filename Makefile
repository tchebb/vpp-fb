include $(srctree)/arch/arm/mach-berlin/mv88de3100.mk

MWD=$(srctree)/arch/arm/mach-berlin
PWD=$(MWD)/modules/vpp_fb

HEADER_PATH :=  \
	-I$(MWD)/include \
	-I$(MWD)/include/mach \
	-I$(MWD)/modules/cc  \
	-I$(MWD)/modules/nfc \
	-I$(MWD)/modules/pe \
	-I$(MWD)/modules/pe/gsinc \
	-I$(MWD)/modules/pe/gsinc/$(FIRMWARE) \
	-I$(PWD)/Common/include \
	-I$(PWD)/Common/include/$(FIRMWARE)

ccflags-y	+= -DVPPFB_ENABLE_MAIN=1 -DVPPFB_ENABLE_PIP=0 -DVPPFB_ENABLE_AUX=0
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

VPPFB_SOURCE += $(wildcard $(PWD)/AVPLL/source/*.c)
VPPFB_SOURCE += $(wildcard $(PWD)/THINVPP/source/*.c)
VPPFB_SOURCE += $(wildcard $(PWD)/THINVPP/source/BE/source/*.c)
VPPFB_SOURCE += $(wildcard $(PWD)/THINVPP/source/CPCB/source/*.c)
VPPFB_SOURCE += $(wildcard $(PWD)/THINVPP/source/FE/source/*.c)
VPPFB_SOURCE += $(wildcard $(PWD)/THINVPP/source/MISC/source/*.c)
VPPFB_SOURCE += $(wildcard $(PWD)/THINVPP/source/SCL/source/*.c)

VPPFB_OBJ += $(patsubst $(PWD)/%.c,%.o,$(VPPFB_SOURCE))
ifeq ($(CONFIG_BERLIN_PE),y)
#use the avio_dhub_drv in pe module
else
VPPFB_OBJ += DHUB/source/avio_dhub_drv.o
endif

obj-$(CONFIG_BERLIN_FBDEV) += vpp_fb_obj.o
vpp_fb_obj-objs := vpp_fb.o $(VPPFB_OBJ)
