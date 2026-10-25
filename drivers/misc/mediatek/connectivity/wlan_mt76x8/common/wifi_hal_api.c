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

/*! \file   "wifi_hal_api.c"
*    \brief  Provide wifi hal APIs for upper layer to use.
*/


/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include "precomp.h"
#include "wifi_hal_api.h"

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

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

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#if CFG_SUPPORT_SET_MIN_RATE
/*
 * @brief: wifiHal_setMinMgmtTransmitRate sets the lower bound the physical
 * data rate device uses for management or group addressed data frames.
 *
 * @param: rate_mbps, rate in mbps @refwifi_min_phy_rate_e.
           Valid values are defined @ref wifi_min_phy_rate_e [0, 1,2,6,12,24].
           In general, this is much more restrictive mandatory rates set than
           all supported rate set device can support.
           When set to PHY_RATE_DEFAULT 0, the API restores the driver/firmware
           default settings.


 * @return return 0 upon success non-zero otherwise (see @ref luma_osal_errno.h)


 * NOTE: this API may be called anytime and must not restart the connection.
 */
INT_32 wifiHalSetMinMgmtTransmitRate(IN P_ADAPTER_T prAdapter,
										IN UINT_32 rateMbps) {

	DBGLOG(INIT, INFO, "[%s:%d] rateMbps %d\n", __func__, __LINE__, rateMbps);
	ASSERT(prAdapter);

	if((rateMbps != 0) && (rateMbps != 1) && (rateMbps != 2) && (rateMbps != 6)
		&& (rateMbps != 12) && (rateMbps != 24))
		return -1;

	prAdapter->u4MgmtMinPhyRate = rateMbps * 10;

	if (prAdapter->prAisBssInfo) {
		if (prAdapter->prAisBssInfo->prStaRecOfAP)
			cnmStaSendUpdateCmd(prAdapter,
				prAdapter->prAisBssInfo->prStaRecOfAP,
				NULL,
				FALSE);
	}

	return 0;
}				/* end of wifiHalSetMinMgmtTransmitRate() */

INT_32 wifiHalSetMinDataTransmitRate(IN P_ADAPTER_T prAdapter,
                                     IN UINT_32 rateMbps) {

        DBGLOG(INIT, INFO, "[%s:%d] rateMbps %d\n", __func__, __LINE__, rateMbps);
        ASSERT(prAdapter);

        if((rateMbps != 0) && (rateMbps != 1) && (rateMbps != 2) && (rateMbps != 6)
                && (rateMbps != 12) && (rateMbps != 24))
                return -1;

        prAdapter->u4DataMinPhyRate = rateMbps * 10;

        return 0;
}

INT_32 wifiHalApplyMinMgmtTransmitRate(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo) {

	P_BSS_INFO_T prBssInfo;
	P_STA_RECORD_T prStaRec;

	UINT_8 ucRateSwIndex, ucRateIndex, ucRatePreamble;
	UINT_16 u2RateCode, u2RateCodeLimit, u2OperationalRateSet;
	UINT_32 u4Status;

	ASSERT(prAdapter);

	DBGLOG(INIT, INFO, "prAdapter->u4MgmtMinPhyRate %d\n", prAdapter->u4MgmtMinPhyRate);

	if(prAdapter->u4MgmtMinPhyRate == 0)
		return -1;

	prBssInfo = GET_BSS_INFO_BY_INDEX(prAdapter, prMsduInfo->ucBssIndex);
	prStaRec = cnmGetStaRecByIndex(prAdapter, prMsduInfo->ucStaRecIndex);

	/* Not to use TxD template for fixed rate */
	prMsduInfo->fgIsTXDTemplateValid = FALSE;

	/* Fixed Rate */
	prMsduInfo->ucRateMode = MSDU_RATE_MODE_MANUAL_DESC;

	if (prStaRec) {
		u2RateCode = prStaRec->u2HwDefaultFixedRateCode;
		u2OperationalRateSet = prStaRec->u2OperationalRateSet;
	} else {
		u2RateCode = prBssInfo->u2HwDefaultFixedRateCode;
		u2OperationalRateSet = prBssInfo->u2OperationalRateSet;
	}

	nicGetRateIndexFromRateSetWithLimit(
		u2OperationalRateSet,
		prAdapter->u4MgmtMinPhyRate, FALSE, &ucRateSwIndex);
	/* Convert SW rate index to rate code */
	nicSwIndex2RateIndex(ucRateSwIndex, &ucRateIndex, &ucRatePreamble);
	u4Status = nicRateIndex2RateCode(ucRatePreamble, ucRateIndex, &u2RateCodeLimit);
	if (u4Status == WLAN_STATUS_SUCCESS) {
		/* Replace by limitation rate */
		u2RateCode = u2RateCodeLimit;
		DBGLOG(NIC, INFO, "Coex RatePreamble=%d, R_SW_IDX:%d, R_CODE:0x%x\n",
		  ucRatePreamble, ucRateIndex, u2RateCode);
	}

	nicTxSetPktFixedRateOption(prMsduInfo, u2RateCode, FIX_BW_NO_FIXED, FALSE, FALSE);

	return 0;
}				/* end of wifiHalApplyMinMgmtTransmitRate() */

#endif
