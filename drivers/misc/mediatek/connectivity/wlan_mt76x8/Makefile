### hardcode mantis chip id instead of loading from .config
include $(srctree)/drivers/misc/mediatek/connectivity/wlan_mt76x8/config/mantis.config
override WLAN_CHIP_ID := MT7668

ifeq ($(strip $(CONFIG_MTK_COMBO_WIFI_HIF)),)
CONFIG_MTK_COMBO_WIFI_HIF := sdio
endif

#/***** Manage configs into compile options ******/
ifneq ($(CFG_NUM_DIFFERENT_CHANNELS_STA),)
ccflags-y += -DCFG_NUM_DIFFERENT_CHANNELS_STA=$(CFG_NUM_DIFFERENT_CHANNELS_STA)
endif

ifneq ($(CFG_NUM_DIFFERENT_CHANNELS_P2P),)
ccflags-y += -DCFG_NUM_DIFFERENT_CHANNELS_P2P=$(CFG_NUM_DIFFERENT_CHANNELS_P2P)
endif

ifneq ($(CFG_DRIVER_INITIAL_RUNNING_MODE),)
ccflags-y += -DCFG_DRIVER_INITIAL_RUNNING_MODE=$(CFG_DRIVER_INITIAL_RUNNING_MODE)
endif

ifneq ($(CFG_ENABLE_WAKE_LOCK),)
ccflags-y += -DCFG_ENABLE_WAKE_LOCK=$(CFG_ENABLE_WAKE_LOCK)
endif

ifneq ($(CFG_DEFAULT_DBG_LEVEL),)
ccflags-y += -DCFG_DEFAULT_DBG_LEVEL=$(CFG_DEFAULT_DBG_LEVEL)
endif

ifneq ($(CFG_TX_DIRECT_USB),)
ccflags-y += -DCFG_TX_DIRECT_USB=$(CFG_TX_DIRECT_USB)
endif

ifneq ($(CFG_RX_DIRECT_USB),)
ccflags-y += -DCFG_RX_DIRECT_USB=$(CFG_RX_DIRECT_USB)
endif

ifneq ($(CFG_USB_REQ_TX_DATA_FFA_CNT),)
ccflags-y += -DCFG_USB_REQ_TX_DATA_FFA_CNT=$(CFG_USB_REQ_TX_DATA_FFA_CNT)
endif

ifneq ($(CFG_USB_REQ_TX_DATA_CNT),)
ccflags-y += -DCFG_USB_REQ_TX_DATA_CNT=$(CFG_USB_REQ_TX_DATA_CNT)
endif

ifneq ($(CFG_USB_REQ_RX_DATA_CNT),)
ccflags-y += -DCFG_USB_REQ_RX_DATA_CNT=$(CFG_USB_REQ_RX_DATA_CNT)
endif

ifneq ($(CFG_SUPPORT_ROAMING),)
ccflags-y += -DCFG_SUPPORT_ROAMING=$(CFG_SUPPORT_ROAMING)
endif

ifneq ($(CFG_SUPPORT_SAME_BSS_REASSOC),)
ccflags-y += -DCFG_SUPPORT_SAME_BSS_REASSOC=$(CFG_SUPPORT_SAME_BSS_REASSOC)
endif

ifneq ($(CFG_ENABLE_EFUSE_MAC_ADDR),)
ccflags-y += -DCFG_ENABLE_EFUSE_MAC_ADDR=$(CFG_ENABLE_EFUSE_MAC_ADDR)
endif

ifeq ($(CFG_DRIVER_INF_NAME_CHANGE), y)
ccflags-y += -DCFG_DRIVER_INF_NAME_CHANGE
endif

# Only when CFG_SUPPORT_SINGLE_SKU_LOCAL_DB enable,
# The CFG_SUPPORT_SINGLE_SKU_CUS_LOCAL_DB will be supported
ifneq ($(CFG_SUPPORT_SINGLE_SKU_LOCAL_DB),)
ccflags-y += -DCFG_SUPPORT_SINGLE_SKU_LOCAL_DB=$(CFG_SUPPORT_SINGLE_SKU_LOCAL_DB)
ifneq ($(CFG_SUPPORT_SINGLE_SKU_LOCAL_DB),0)
ifeq ($(CFG_SUPPORT_SINGLE_SKU_CUS_LOCAL_DB), y)
ccflags-y += -DCFG_SUPPORT_SINGLE_SKU_CUS_LOCAL_DB
endif
endif
endif

ifneq ($(CFG_SUPPORT_DFS_MASTER),)
ccflags-y += -DCFG_SUPPORT_DFS_MASTER=$(CFG_SUPPORT_DFS_MASTER)
endif

ifneq ($(CFG_P2P_SCAN_REPORT_ALL_BSS),)
ccflags-y += -DCFG_P2P_SCAN_REPORT_ALL_BSS=$(CFG_P2P_SCAN_REPORT_ALL_BSS)
endif

ifneq ($(CFG_SCAN_CHANNEL_SPECIFIED),)
ccflags-y += -DCFG_SCAN_CHANNEL_SPECIFIED=$(CFG_SCAN_CHANNEL_SPECIFIED)
endif

ifneq ($(CFG_RX_BA_ENTRY_MISS_TIMEOUT),)
ccflags-y += -DCFG_RX_BA_ENTRY_MISS_TIMEOUT=$(CFG_RX_BA_ENTRY_MISS_TIMEOUT)
endif

ifeq ($(CFG_SUPPORT_DISABLE_BCN_HINTS), y)
ccflags-y += -DCFG_SUPPORT_DISABLE_BCN_HINTS
endif

ifneq ($(CFG_SUPPORT_RSSI_COMP),)
ccflags-y += -DCFG_SUPPORT_RSSI_COMP=$(CFG_SUPPORT_RSSI_COMP)
endif

ifneq ($(CFG_EFUSE_AUTO_MODE_SUPPORT),)
ccflags-y += -DCFG_EFUSE_AUTO_MODE_SUPPORT=$(CFG_EFUSE_AUTO_MODE_SUPPORT)
endif

ifneq ($(CFG_RX_SINGLE_CHAIN_SUPPORT),)
ccflags-y += -DCFG_RX_SINGLE_CHAIN_SUPPORT=$(CFG_RX_SINGLE_CHAIN_SUPPORT)
endif

ifneq ($(CFG_SUPPORT_BFER),)
ccflags-y += -DCFG_SUPPORT_BFER=$(CFG_SUPPORT_BFER)
endif

ifneq ($(CFG_SUPPORT_UPDATE_AP_MODE_SSID),)
ccflags-y += -DCFG_SUPPORT_UPDATE_AP_MODE_SSID=$(CFG_SUPPORT_UPDATE_AP_MODE_SSID)
endif

ifneq ($(CFG_IGNORE_1X_CLASS_ERROR),)
ccflags-y += -DCFG_IGNORE_1X_CLASS_ERROR=$(CFG_IGNORE_1X_CLASS_ERROR)
endif

ifeq ($(CFG_STR_DEAUTH_DELAY), y)
ccflags-y += -DCFG_STR_DEAUTH_DELAY
endif

ifeq ($(CFG_KEY_ERROR_STATISTIC_RECOVERY), y)
ccflags-y += -DCFG_KEY_ERROR_STATISTIC_RECOVERY=1
endif

ifeq ($(CFG_SUPPORT_MGMT_RSSI), y)
ccflags-y += -DCFG_SUPPORT_MGMT_RSSI=1
endif

ifneq ($(CFG_IOCTL_WAIT_FOR_COMPLETION_TIMEOUT),)
ccflags-y += -DCFG_IOCTL_WAIT_FOR_COMPLETION_TIMEOUT=$(CFG_IOCTL_WAIT_FOR_COMPLETION_TIMEOUT)
endif

# ---------------------------------------------------
# Compile Options
# ---------------------------------------------------
ccflags-y += $(WLAN_CHIP_LIST)

#WLAN_CHIP_ID=$(MTK_COMBO_CHIP)
ifeq ($(WLAN_CHIP_ID),)
    WLAN_CHIP_ID := MT6632
endif

ccflags-y += -DCFG_SUPPORT_DEBUG_FS=$(CFG_SUPPORT_DEBUG_FS)
ifneq ($(TARGET_BUILD_VARIANT), user)
ccflags-y += -DWLAN_INCLUDE_PROC=1
else
ccflags-y += -DCFG_SUPPORT_PRIVACY_INFO
endif
ccflags-y += -DCFG_SUPPORT_AGPS_ASSIST=$(CFG_SUPPORT_AGPS_ASSIST)
ccflags-y += -DCFG_SUPPORT_TSF_USING_BOOTTIME=$(CFG_SUPPORT_TSF_USING_BOOTTIME)
ccflags-y += -Werror
ccflags-y:=$(filter-out -U$(WLAN_CHIP_ID),$(ccflags-y))
ccflags-y += -DLINUX -D$(WLAN_CHIP_ID)

ifeq ($(CONFIG_MTK_WIFI_MCC_SUPPORT), y)
    ccflags-y += -DCFG_SUPPORT_CHNL_CONFLICT_REVISE=0
     $(info DCFG_SUPPORT_CHNL_CONFLICT_REVISE=0)
else
    ccflags-y += -DCFG_SUPPORT_CHNL_CONFLICT_REVISE=1
     $(info DCFG_SUPPORT_CHNL_CONFLICT_REVISE=1)
endif

ifeq ($(CONFIG_MTK_AEE_FEATURE), y)
    ccflags-y += -DCFG_SUPPORT_AEE=1
    $(info DCFG_SUPPORT_AEE=1)
else
    ccflags-y += -DCFG_SUPPORT_AEE=0
    $(info DCFG_SUPPORT_AEE=0)
endif

ifeq ($(CFG_GARP_KEEPALIVE),y)
    ccflags-y += -DCFG_GARP_KEEPALIVE=1
    $(info CFG_GARP_KEEPALIVE=1)
else
    ccflags-y += -DCFG_GARP_KEEPALIVE=0
    $(info CFG_GARP_KEEPALIVE=0)
endif

ifeq ($(CONFIG_MTK_WPA3_SUPPORT), y)
    ccflags-y += -DCFG_SUPPORT_CFG80211_AUTH=1
    ccflags-y += -DCFG_SUPPORT_SAE=1
    ccflags-y += -DCFG_SUPPORT_OWE=0
    ccflags-y += -DCFG_SUPPORT_SUITB=0
else
    ccflags-y += -DCFG_SUPPORT_CFG80211_AUTH=0
    ccflags-y += -DCFG_SUPPORT_SAE=0
    ccflags-y += -DCFG_SUPPORT_OWE=0
    ccflags-y += -DCFG_SUPPORT_SUITB=0
endif

# Disable wlan feature send only one cfg to FW
# Default is enabled in the config.h
ifeq ($(CFG_SUPPORT_SEND_ONLY_ONE_CFG), n)
    ccflags-y += -DCFG_SUPPORT_SEND_ONLY_ONE_CFG=0
endif

# Enable Metrics for Wlan reset
ifeq ($(CONFIG_AMAZON_METRICS_LOG), y)
    ccflags-y += -DCFG_AMAZON_METRICS_LOG=$(CONFIG_AMAZON_METRICS_LOG)
endif

# Disable ASSERT() for user load, enable for others
ifneq ($(TARGET_BUILD_VARIANT),user)
    ccflags-y += -DBUILD_QA_DBG=1
else
    ccflags-y += -DBUILD_QA_DBG=0
endif

ccflags-y += -DCFG_BUILT_IN_DRIVER=1
ccflags-y += -DCFG_WPS_DISCONNECT=1

ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), sdio)
	ccflags-y += -D_HIF_SDIO=1
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), pcie)
    ccflags-y += -D_HIF_PCIE=1
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), usb)
	ccflags-y += -D_HIF_USB=1
else
    $(error Unsuppoted HIF=$(CONFIG_MTK_COMBO_WIFI_HIF)!!)
endif

#load TxPwrLimit.dat or not
ifneq ($(CFG_SUPPORT_PWR_LIMIT_NO_FILE_LOAD),y)
ccflags-y += -DCFG_SUPPORT_PWR_LIMIT_FILE_LOAD
endif

#Periodic PS mode profile Options
ifeq ($(CFG_SUPPORT_PERIODIC_PS),y)
ccflags-y += -DSUPPORT_PERIODIC_PS
endif

ifeq ($(CFG_SUPPORT_ENFORCE_PWR_MODE),y)
ccflags-y += -DSUPPORT_ENFORCE_PWR_MODE
endif

ifeq ($(CFG_RATE_CONTROL),y)
ccflags-y += -DCFG_RATE_CONTROL=1
endif

#support STA + P2P GO MCC case
ifeq ($(CFG_SUPPORT_STA_P2P_MCC),y)
ccflags-y += -DSTA_P2P_MCC
endif

ifeq ($(CFG_SUPPORT_P2P_OPEN_SECURITY),y)
ccflags-y += -DCFG_SUPPORT_P2P_OPEN_SECURITY
endif

ifeq ($(CFG_SUPPORT_P2P_GO_11b_RATE),y)
ccflags-y += -DCFG_SUPPORT_P2P_GO_11b_RATE
endif

ifeq ($(CFG_SUPPORT_P2P_GO_KEEP_RATE_SETTING),y)
ccflags-y += -DCFG_SUPPORT_P2P_GO_KEEP_RATE_SETTING
endif

#support adminctrl for external PTA
ifeq ($(CFG_SUPPORT_ADMINCTRL),y)
ccflags-y += -DCFG_SUPPORT_ADMINCTRL
endif

ifeq ($(CFG_SUPPORT_ADJUST_MCC_STAY_TIME),y)
ccflags-y += -DCFG_SUPPORT_ADJUST_MCC_STAY_TIME
endif

ifeq ($(CFG_SUPPORT_ANT_DIV),y)
ccflags-y += -DCFG_SUPPORT_ANT_DIV
endif

ifeq ($(CFG_ENABLE_DEWEIGHTING_CTRL), y)
    ccflags-y += -DCFG_ENABLE_DEWEIGHTING_CTRL=1
else
    ccflags-y += -DCFG_ENABLE_DEWEIGHTING_CTRL=0
endif

ifeq ($(CFG_DUMP_TXPOWR_TABLE),y)
ccflags-y += -DCFG_DUMP_TXPOWR_TABLE
endif

#For adjust channel request interval when ais join net work
ifeq ($(CFG_SUPPORT_ADJUST_JOIN_CH_REQ_INTERVAL),y)
ccflags-y += -DCFG_SUPPORT_ADJUST_JOIN_CH_REQ_INTERVAL
endif

ifeq ($(CFG_IPI_2CHAIN_SUPPORT),n)
ccflags-y += -DCFG_IPI_2CHAIN_SUPPORT=0
else
ccflags-y += -DCFG_IPI_2CHAIN_SUPPORT=1
endif

ifeq ($(CFG_ENABLE_PS_INTV_CTRL), y)
    ccflags-y += -DCFG_ENABLE_PS_INTV_CTRL=1
else
    ccflags-y += -DCFG_ENABLE_PS_INTV_CTRL=0
endif

ifeq ($(CFG_ENABLE_1RPD_MMPS_CTRL), y)
    ccflags-y += -DCFG_ENABLE_1RPD_MMPS_CTRL=1
else
    ccflags-y += -DCFG_ENABLE_1RPD_MMPS_CTRL=0
endif

ifeq ($(CFG_GET_TEMPURATURE),y)
ccflags-y += -DCFG_GET_TEMPURATURE
endif

# Config option to register the temperature sensor to virtual sensor framework
# or only use it as a physical sensor.
# Set to y if you want to use the sensor only as a physical sensor
ifeq ($(CFG_TEMP_SENSOR_AS_PHYSICAL_ONLY), y)
ccflags-y += -DCFG_TEMP_SENSOR_AS_PHYSICAL_ONLY
endif

ifeq ($(CFG_SUPPORT_EXT_PTA_DEBUG_COMMAND),y)
ccflags-y += -DCFG_SUPPORT_EXT_PTA_DEBUG_COMMAND
endif

ifeq ($(CFG_SUPPORT_DUAL_CARD_DUAL_DRIVER),y)
ccflags-y += -DCFG_SUPPORT_DUAL_CARD_DUAL_DRIVER
endif

ifeq ($(CFG_SUPPORT_MULTICAST_ENHANCEMENT),y)
ccflags-y += -DCFG_SUPPORT_MULTICAST_ENHANCEMENT
endif

ifeq ($(CFG_SUPPORT_UNICAST_ENHANCEMENT),y)
ccflags-y += -DCFG_SUPPORT_UNICAST_ENHANCEMENT
endif

ifeq ($(CFG_SUPPORT_MT76X8_WIFI_PLATFORM_DRIVER),y)
ccflags-y += -DCFG_SUPPORT_MT76X8_WIFI_PLATFORM_DRIVER
endif

ifeq ($(CFG_SUPPORT_802_11K),y)
ccflags-y += -DCFG_SUPPORT_802_11K=1
endif

ifeq ($(CFG_SUPPORT_802_11V),y)
ccflags-y += -DCFG_SUPPORT_802_11V=1
endif

ifeq ($(CFG_SUPPORT_802_11V_BSS_TRANSITION_MGT),y)
ccflags-y += -DCFG_SUPPORT_802_11V_BSS_TRANSITION_MGT=1
endif

ifeq ($(CFG_SUPPORT_DISABLE_JP_DFS), y)
ccflags-y += -DCFG_SUPPORT_DISABLE_JP_DFS
endif

ifeq ($(CFG_SUPPORT_DISABLE_MXIN_DFS), y)
ccflags-y += -DCFG_SUPPORT_DISABLE_MXIN_DFS
endif

ifeq ($(TARGET_BUILD_VARIANT), user)
ifeq ($(CFG_SUPPORT_EMPTY_MAC), y)
ccflags-y += -DCFG_SUPPORT_EMPTY_MAC
endif
endif


ifeq ($(CFG_KEEP_SAA_STATUS_CODE), y)
ccflags-y += -DCFG_KEEP_SAA_STATUS_CODE=1
endif

ifeq ($(CFG_ROAMING_5G_PREFER),y)
ccflags-y += -DCFG_ROAMING_5G_PREFER=1
endif

ifneq ($(CFG_SUPPORT_REORDER_TIMER_PER_TID),)
ccflags-y += -DCFG_SUPPORT_REORDER_TIMER_PER_TID=$(CFG_SUPPORT_REORDER_TIMER_PER_TID)
endif

ifeq ($(CFG_DFS_NEWCH_DFS_FORCE_DISCONNECT),n)
ccflags-y += -DCFG_DFS_NEWCH_DFS_FORCE_DISCONNECT=0
endif

ifneq ($(CFG_CFG80211_VERSION),)
VERSION_STR = $(subst ",,$(subst ., , $(subst -, ,$(subst v,,$(CFG_CFG80211_VERSION)))))
$(info VERSION_STR=$(VERSION_STR))
X = $(firstword $(VERSION_STR))
Y = $(word 2 ,$(VERSION_STR))
Z = $(word 3 ,$(VERSION_STR))
VERSION := $(shell echo "$$(( $X * 65536 + $Y * 256 + $Z))" )
ccflags-y += -DCFG_CFG80211_VERSION=$(VERSION)
$(info DCFG_CFG80211_VERSION=$(VERSION))
endif

$(info HIF=$(CONFIG_MTK_COMBO_WIFI_HIF))

$(info DUAL_CARD_DAUL_DRIVER=$(CFG_SUPPORT_DUAL_CARD_DUAL_DRIVER))

ifeq ($(CONFIG_MTK_PASSPOINT_R1_SUPPORT), y)
    ccflags-y += -DCFG_SUPPORT_PASSPOINT=1
    ccflags-y += -DCFG_HS20_DEBUG=1
    ccflags-y += -DCFG_ENABLE_GTK_FRAME_FILTER=1
else ifeq ($(CONFIG_MTK_PASSPOINT_R2_SUPPORT), y)
    ccflags-y += -DCFG_SUPPORT_PASSPOINT=1
    ccflags-y += -DCFG_HS20_DEBUG=1
    ccflags-y += -DCFG_ENABLE_GTK_FRAME_FILTER=1
else
    ccflags-y += -DCFG_SUPPORT_PASSPOINT=0
    ccflags-y += -DCFG_HS20_DEBUG=0
    ccflags-y += -DCFG_ENABLE_GTK_FRAME_FILTER=0
endif

ifeq ($(MTK_MET_PROFILING_SUPPORT), yes)
    ccflags-y += -DCFG_MET_PACKET_TRACE_SUPPORT=1
else
    ccflags-y += -DCFG_MET_PACKET_TRACE_SUPPORT=0
endif

ifeq ($(MTK_MET_TAG_SUPPORT), yes)
    ccflags-y += -DMET_USER_EVENT_SUPPORT
    ccflags-y += -DCFG_MET_TAG_SUPPORT=1
else
    ccflags-y += -DCFG_MET_TAG_SUPPORT=0
endif

ifeq ($(MODULE_NAME),)
	MODULE_NAME := wlan_$(shell echo $(strip $(WLAN_CHIP_ID)) | tr A-Z a-z)_$(CONFIG_MTK_COMBO_WIFI_HIF)
endif
ccflags-y += -DDBG=0
ccflags-y += -I$(src)/os -I$(src)/os/linux/include
ccflags-y += -I$(src)/include -I$(src)/include/nic -I$(src)/include/mgmt -I$(src)/include/chips
ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), sdio)
ccflags-y += -I$(src)/os/linux/hif/sdio/include
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), pcie)
ccflags-y += -I$(src)/os/linux/hif/pcie/include
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), usb)
ccflags-y += -I$(src)/os/linux/hif/usb/include
endif

ifneq ($(PLATFORM_FLAGS), )
    ccflags-y += $(PLATFORM_FLAGS)
endif

obj-y += $(MODULE_NAME).o

ifneq ($(CFG_CHIP_RESET_SUPPORT),)
ifneq ($(TARGET_BUILD_VARIANT), user)
CFG_CHIP_RESET_SUPPORT := 0
endif
ccflags-y += -DCFG_CHIP_RESET_SUPPORT=$(CFG_CHIP_RESET_SUPPORT)
endif

ifneq ($(CFG_SUPPORT_SET_MIN_RATE),)
ccflags-y += -DCFG_SUPPORT_SET_MIN_RATE=$(CFG_SUPPORT_SET_MIN_RATE)
endif



# ---------------------------------------------------
# Directory List
# ---------------------------------------------------
COMMON_DIR  := common/
OS_DIR      := os/linux/
ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), sdio)
HIF_DIR	    := os/linux/hif/sdio/
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), pcie)
HIF_DIR     := os/linux/hif/pcie/
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), usb)
HIF_DIR	    := os/linux/hif/usb/
endif
NIC_DIR     := nic/
MGMT_DIR    := mgmt/
CHIPS       := chips/


# ---------------------------------------------------
# Objects List
# ---------------------------------------------------

COMMON_OBJS :=	$(COMMON_DIR)dump.o \
	       		$(COMMON_DIR)wlan_lib.o \
	       		$(COMMON_DIR)wlan_oid.o \
	       		$(COMMON_DIR)wlan_bow.o \
	       		$(COMMON_DIR)wifi_hal_api.o

NIC_OBJS := $(NIC_DIR)nic.o \
			$(NIC_DIR)nic_tx.o \
			$(NIC_DIR)nic_rx.o \
			$(NIC_DIR)nic_pwr_mgt.o \
            $(NIC_DIR)nic_rate.o \
			$(NIC_DIR)cmd_buf.o \
			$(NIC_DIR)que_mgt.o \
			$(NIC_DIR)nic_cmd_event.o \
			$(NIC_DIR)nic_umac.o

OS_OBJS :=	$(OS_DIR)gl_init.o \
			$(OS_DIR)gl_kal.o  \
			$(OS_DIR)gl_bow.o \
			$(OS_DIR)gl_wext.o \
			$(OS_DIR)gl_wext_priv.o \
			$(OS_DIR)gl_ate_agent.o \
			$(OS_DIR)gl_qa_agent.o \
			$(OS_DIR)gl_hook_api.o \
			$(OS_DIR)gl_rst.o \
			$(OS_DIR)gl_cfg80211.o \
			$(OS_DIR)gl_proc.o \
			$(OS_DIR)gl_vendor.o \
			$(OS_DIR)platform.o

ifeq ($(CFG_GET_TEMPURATURE),y)
OS_OBJS +=	$(OS_DIR)amazon_wifi_temp_sensor.o
endif

MGMT_OBJS := $(MGMT_DIR)ais_fsm.o \
			 $(MGMT_DIR)aaa_fsm.o \
			 $(MGMT_DIR)assoc.o \
			 $(MGMT_DIR)auth.o \
			 $(MGMT_DIR)bss.o \
			 $(MGMT_DIR)cnm.o \
			 $(MGMT_DIR)cnm_timer.o \
			 $(MGMT_DIR)cnm_mem.o \
			 $(MGMT_DIR)hem_mbox.o \
			 $(MGMT_DIR)mib.o \
			 $(MGMT_DIR)privacy.o  \
			 $(MGMT_DIR)rate.o \
			 $(MGMT_DIR)rlm.o \
			 $(MGMT_DIR)rlm_domain.o \
			 $(MGMT_DIR)reg_rule.o \
			 $(MGMT_DIR)rlm_obss.o \
			 $(MGMT_DIR)rlm_protection.o \
			 $(MGMT_DIR)rsn.o \
			 $(MGMT_DIR)saa_fsm.o \
			 $(MGMT_DIR)scan.o \
			 $(MGMT_DIR)scan_fsm.o \
             $(MGMT_DIR)swcr.o \
             $(MGMT_DIR)roaming_fsm.o \
             $(MGMT_DIR)tkip_mic.o \
             $(MGMT_DIR)hs20.o \
             $(MGMT_DIR)tdls.o \
             $(MGMT_DIR)wnm.o

CHIPS_OBJS := $(CHIPS)mt6632.o \
			  $(CHIPS)mt7668.o
# ---------------------------------------------------
# P2P Objects List
# ---------------------------------------------------

COMMON_OBJS += $(COMMON_DIR)wlan_p2p.o

NIC_OBJS += $(NIC_DIR)p2p_nic.o

OS_OBJS += $(OS_DIR)gl_p2p.o \
           $(OS_DIR)gl_p2p_cfg80211.o \
           $(OS_DIR)gl_p2p_init.o \
           $(OS_DIR)gl_p2p_kal.o

MGMT_OBJS += $(MGMT_DIR)p2p_dev_fsm.o\
            $(MGMT_DIR)p2p_dev_state.o\
            $(MGMT_DIR)p2p_role_fsm.o\
            $(MGMT_DIR)p2p_role_state.o\
            $(MGMT_DIR)p2p_func.o\
            $(MGMT_DIR)p2p_scan.o\
            $(MGMT_DIR)p2p_ie.o\
            $(MGMT_DIR)p2p_rlm.o\
            $(MGMT_DIR)p2p_assoc.o\
            $(MGMT_DIR)p2p_bss.o\
            $(MGMT_DIR)p2p_rlm_obss.o\
            $(MGMT_DIR)p2p_fsm.o

MGMT_OBJS += $(MGMT_DIR)wapi.o

ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), sdio)
HIF_OBJS :=  $(HIF_DIR)arm.o \
             $(HIF_DIR)sdio.o \
             $(HIF_DIR)sdio_test_driver_core.o \
             $(HIF_DIR)sdio_test_driver_ops.o
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), pcie)
HIF_OBJS :=  $(HIF_DIR)arm.o \
             $(HIF_DIR)pcie.o
else ifeq ($(CONFIG_MTK_COMBO_WIFI_HIF), usb)
HIF_OBJS :=  $(HIF_DIR)usb.o
endif

HIF_OBJS +=  $(HIF_DIR)hal_api.o

$(MODULE_NAME)-objs  += $(COMMON_OBJS)
$(MODULE_NAME)-objs  += $(NIC_OBJS)
$(MODULE_NAME)-objs  += $(OS_OBJS)
$(MODULE_NAME)-objs  += $(HIF_OBJS)
$(MODULE_NAME)-objs  += $(MGMT_OBJS)
$(MODULE_NAME)-objs  += $(CHIPS_OBJS)

#
# mtprealloc
#
ifeq ($(CFG_MTK_PREALLOC_DRIVER), y)
ccflags-y += -DCFG_PREALLOC_MEMORY
ccflags-y += -I$(src)/prealloc/include
MODULE_NAME_PREALLOC = $(MODULE_NAME)_prealloc
PREALLOC_OBJS := prealloc/prealloc.o
PREALLOC_OBJS += prealloc/chip_reset_info.o
$(MODULE_NAME_PREALLOC)-objs += $(PREALLOC_OBJS)
obj-m += $(MODULE_NAME_PREALLOC).o
endif
