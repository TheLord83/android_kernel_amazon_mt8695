/******************************************************************************
 *
 * This file is provided under a dual license.  When you use or
 * distribute this software, you may choose to be licensed under
 * version 2 of the GNU General Public License ("GPLv2 License")
 * or BSD License.
 *
 * GPLv2 License
 *
 * Copyright(C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 *
 * BSD LICENSE
 *
 * Copyright(C) 2016 MediaTek Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

/*! \file   "wifi_hal_api.h"
*    \brief This file contains the declairation file of wifi hal APIs for
*	   upper layer
*/


#ifndef _WIFI_HAL_API_H
#define _WIFI_HAL_API_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/


/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
#if CFG_SUPPORT_SET_MIN_RATE
typedef enum _ENUM_PARAM_WIFI_MIN_PHY_RATE_T {
	WIFI_MIN_PHY_RATE_NO_LIMIT,
	WIFI_MIN_PHY_RATE_CCK_1MBPS,
	WIFI_MIN_PHY_RATE_CCK_2MBPS,
	WIFI_MIN_PHY_RATE_OFDM_6MBPS,
	WIFI_MIN_PHY_RATE_OFDM_12MBPS,
	WIFI_MIN_PHY_RATE_OFDM_24MBPS
} ENUM_PARAM_WIFI_MIN_PHY_RATE_T, *P_ENUM_PARAM_WIFI_MIN_PHY_RATE_T;
#endif


/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
#if CFG_SUPPORT_SET_MIN_RATE
INT_32 wifiHalSetMinMgmtTransmitRate(IN P_ADAPTER_T prAdapter,
                                        IN UINT_32 rateMbps);

INT_32 wifiHalSetMinDataTransmitRate(IN P_ADAPTER_T prAdapter,
                                        IN UINT_32 rateMbps);

INT_32 wifiHalApplyMinMgmtTransmitRate(IN P_ADAPTER_T prAdapter,
										IN P_MSDU_INFO_T prMsduInfo);
#endif


/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _WIFI_HAL_API_H */
