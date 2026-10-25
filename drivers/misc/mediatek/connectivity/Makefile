#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

# Connectivity combo driver
obj-$(CONFIG_MTK_BT_MT7663_SDIO) += bt_mt7663_sdio/
ifeq ($(CONFIG_MTK_WIFI_MT7663_SDIO),y)
ifeq ($(CONFIG_MTK_COMBO_CHIP_MT7668),y)
obj-y += wlan_mt76x8/
else
obj-y += wlan/
endif
endif
