###############################################################################
# SDIO
###############################################################################
ccflags-y += -DDBG=0
ccflags-y += -I$(src)/os -I$(src)/os/linux/include
ifeq ($(MTK_CHIP_PCM), TRUE)
    ccflags-y += -DMTK_CHIP_PCM
endif

SDIO_MOD_NAME = btmtksdio
SDIO_CFILES := \
	btmtk_sdio.c \
        btmtk_main.c
ifeq ($(CONFIG_AMAZON_A2DP_TS),y)
    SDIO_CFILES += btif_audio_ts.c
endif

ifneq ($(TARGET_BUILD_VARIANT), user)
        ccflags-y += -DMTK_KERNEL_DEBUG
endif

$(SDIO_MOD_NAME)-objs := $(SDIO_CFILES:.c=.o)

ifeq ($(CONFIG_MP_WAKEUP_SOURCE_SYSFS_STAT), y)
        ccflags-y += -DCONFIG_MP_WAKEUP_SOURCE_SYSFS_STAT
else
endif

ifneq ($(filter abc123_ftv abc123 abc123, $(TARGET_PRODUCT)),)
    ccflags-y += -Dabc123_AML_TEMP_CHIP_RESET_FIX
endif

ccflags-y += -DANDROID_OS

###############################################################################
# Common
###############################################################################
obj-y := $(SDIO_MOD_NAME).o
