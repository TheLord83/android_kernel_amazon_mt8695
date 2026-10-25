/*******************************************************************************
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
 ******************************************************************************/
/*
 ** Id: @(#) gl_rst.c@@
 */

/*! \file   gl_rst.c
 *    \brief  Main routines for supporintg MT6620 whole-chip reset mechanism
 *
 *    This file contains the support routines of Linux driver for MediaTek Inc.
 *    802.11 Wireless LAN Adapters.
 */


/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 *******************************************************************************
 */

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 *******************************************************************************
 */
#include <linux/kernel.h>
#include <linux/workqueue.h>

#include "precomp.h"
#include "gl_rst.h"

static void glResetTriggerUpdateCnt(uint32_t u4RstFlag);

/*******************************************************************************
 *                              C O N S T A N T S
 *******************************************************************************
 */
// update chip_reset_info.c if apcChipResetReason / apcChipResetAction have
// changed
const char *const apcChipResetReason[RST_REASON_MAX] = {
	"RST_UNKNOWN",
	"RST_PROCESS_ABNORMAL_INT",
	"RST_DRV_OWN_FAIL",
	"RST_FW_ASSERT",
	"RST_BT_TRIGGER",
	"RST_OID_TIMEOUT",
	"RST_CMD_TRIGGER",
	"RST_CR_ACCESS_FAIL",
	"RST_HIF_FAIL",
	"RST_PROBE_FAIL",
};

const char *const apcChipResetAction[] = {
	"RST_FLAG_DO_CORE_DUMP",
	"RST_FLAG_PREVENT_POWER_OFF",
};

/*******************************************************************************
 *                            P U B L I C   D A T A
 *******************************************************************************
 */
#if CFG_CHIP_RESET_SUPPORT
enum _ENUM_CHIP_RESET_REASON_TYPE_T eResetReason;
uint64_t u8ResetTime;

#if CFG_CHIP_RESET_HANG
u_int8_t fgIsResetHangState = SER_L0_HANG_RST_NONE;
#endif

#endif

/*******************************************************************************
 *                           P R I V A T E   D A T A
 *******************************************************************************
 */
#if CFG_CHIP_RESET_SUPPORT
static struct RESET_STRUCT wifi_rst;
u_int8_t fgIsResetting = FALSE;
#endif

/*******************************************************************************
 *                   F U N C T I O N   D E C L A R A T I O N S
 *******************************************************************************
 */
#if CFG_CHIP_RESET_SUPPORT
static void mtk_wifi_reset(struct work_struct *work);

#if CFG_WMT_RESET_API_SUPPORT
static void mtk_wifi_trigger_reset(struct work_struct *work);
static void *glResetCallback(enum ENUM_WMTDRV_TYPE eSrcType,
			     enum ENUM_WMTDRV_TYPE eDstType,
			     enum ENUM_WMTMSG_TYPE eMsgType, void *prMsgBody,
			     unsigned int u4MsgLength);
#else
static u_int8_t is_bt_exist(void);
static u_int8_t rst_L0_notify_step1(u_int8_t force_reset);
static u_int8_t rst_L0_notify_step2(void);
static void wait_core_dump_end(void);
#endif
#endif

/*******************************************************************************
 *                              F U N C T I O N S
 *******************************************************************************
 */
#if CFG_CHIP_RESET_SUPPORT

/*----------------------------------------------------------------------------*/
/*!
 * @brief This routine is responsible for
 *        1. register wifi reset callback
 *        2. initialize wifi reset work
 *
 * @param none
 *
 * @retval none
 */
/*----------------------------------------------------------------------------*/
void glResetInit(struct GLUE_INFO *prGlueInfo)
{
#if CFG_WMT_RESET_API_SUPPORT
	/* 1. Register reset callback */
	mtk_wcn_wmt_msgcb_reg(WMTDRV_TYPE_WIFI,
			      (PF_WMT_CB) glResetCallback);

	/* 2. Initialize reset work */
	INIT_WORK(&(wifi_rst.rst_trigger_work),
		  mtk_wifi_trigger_reset);
#endif
	fgIsResetting = FALSE;
	wifi_rst.prGlueInfo = prGlueInfo;
	INIT_WORK(&(wifi_rst.rst_work), mtk_wifi_reset);
}

/*----------------------------------------------------------------------------*/
/*!
 * @brief This routine is responsible for
 *        1. deregister wifi reset callback
 *
 * @param none
 *
 * @retval none
 */
/*----------------------------------------------------------------------------*/
void glResetUninit(void)
{
#if CFG_WMT_RESET_API_SUPPORT
	/* 1. Deregister reset callback */
	mtk_wcn_wmt_msgcb_unreg(WMTDRV_TYPE_WIFI);
#endif
}
/*----------------------------------------------------------------------------*/
/*!
 * @brief This routine is called for generating reset request to WMT
 *
 * @param   None
 *
 * @retval  None
 */
/*----------------------------------------------------------------------------*/
void glSendResetRequest(void)
{
#if CFG_WMT_RESET_API_SUPPORT

	/* WMT thread would trigger whole chip reset itself */
#endif
}

/*----------------------------------------------------------------------------*/
/*!
 * @brief This routine is called for checking if connectivity chip is resetting
 *
 * @param   None
 *
 * @retval  TRUE
 *          FALSE
 */
/*----------------------------------------------------------------------------*/
u_int8_t kalIsResetting(void)
{
	return fgIsResetting;
}

static void glResetTriggerUpdateCnt(uint32_t u4RstFlag)
{
	uint32_t i;
	typedef uint32_t (*p_inc_func_type) (uint32_t);
	p_inc_func_type inc_func;
	char *reason_func_name = "incChipResetReasonCnt";
	char *action_func_name = "incChipResetActionCnt";
	void *pvAddrReason = NULL;
	void *pvAddrAction = NULL;

	pvAddrReason = (void *) kal_kallsyms_lookup_name(reason_func_name);
	pvAddrAction = (void *) kal_kallsyms_lookup_name(action_func_name);

	if (eResetReason >= 0 && eResetReason < RST_REASON_MAX) {
		DBGLOG(INIT, ERROR, "reset reason %s\n",
			apcChipResetReason[eResetReason]);
		if(pvAddrReason) {
			inc_func = (p_inc_func_type) pvAddrReason;
			inc_func(eResetReason);
			kal_kallsyms_put(reason_func_name);
		}
		else {
			DBGLOG(INIT, ERROR, "%s does not exist\n", reason_func_name);
		}
	}
	else
		DBGLOG(INIT, ERROR, "unsupported reason %d\n", eResetReason);

	for (i = 0; i < sizeof(apcChipResetAction) / sizeof(char *); i++) {
		if (u4RstFlag & BIT(i)) {
			DBGLOG(INIT, ERROR, "action %s\n", apcChipResetAction[i]);
			if(pvAddrAction) {
				inc_func = (p_inc_func_type) pvAddrAction;
				inc_func(i);
				kal_kallsyms_put(action_func_name);
			}
			else {
				DBGLOG(INIT, ERROR, "%s does not exist\n", action_func_name);
			}
		}
	}

}

u_int8_t glResetTrigger(struct ADAPTER *prAdapter,
		uint32_t u4RstFlag, const uint8_t *pucFile, uint32_t u4Line)
{
	u_int8_t fgResult = TRUE;
	uint16_t u2FwOwnVersion;
	uint16_t u2FwPeerVersion;
#if CFG_FTV_60720_PATCH
	struct GLUE_INFO *prGlueInfo = wifi_rst.prGlueInfo;
#endif

	dump_stack();
	if (kalIsResetting())
		return fgResult;

	fgIsResetting = TRUE;

#if CFG_FTV_60720_PATCH
	if(prGlueInfo == NULL) {
		DBGLOG(INIT, ERROR, "prGlueInfo is NULL\n");
		return FALSE;
	}

	if (!completion_done(&prGlueInfo->rPendComp)) {
		complete(&prGlueInfo->rPendComp);
		DBGLOG(INIT, ERROR, "release pending kalIoctl operation\n");
	}
#endif

	if (eResetReason != RST_BT_TRIGGER)
		DBGLOG(INIT, STATE, "[SER][L0] wifi trigger eResetReason=%d\n",
								eResetReason);
	else
		DBGLOG(INIT, STATE, "[SER][L0] BT trigger\n");

#if CFG_WMT_RESET_API_SUPPORT
	if (u4RstFlag & RST_FLAG_DO_CORE_DUMP)
		if (glIsWmtCodeDump())
			DBGLOG(INIT, WARN, "WMT is code dumping !\n");
#endif
	if (prAdapter == NULL) {
		prAdapter = wifi_rst.prGlueInfo->prAdapter;
		if (prAdapter == NULL) {
#if CFG_FTV_abc123_135_PATCH
			fgIsResetting = FALSE;
#endif
			DBGLOG(INIT, ERROR,
				"[SER][L0] Adapter is null, stop reset flow\n");
			return fgResult;
		}
	}
	u2FwOwnVersion = prAdapter->rVerInfo.u2FwOwnVersion;
	u2FwPeerVersion = prAdapter->rVerInfo.u2FwPeerVersion;

	DBGLOG(INIT, ERROR,
		"Trigger chip reset in %s line %u! Chip[%04X E%u] FW Ver DEC[%u.%u] HEX[%x.%x], Driver Ver[%u.%u]\n",
		 pucFile, u4Line, MTK_CHIP_REV,
	wlanGetEcoVersion(prAdapter),
		(uint16_t)(u2FwOwnVersion >> 8),
		(uint16_t)(u2FwOwnVersion & BITS(0, 7)),
		(uint16_t)(u2FwOwnVersion >> 8),
		(uint16_t)(u2FwOwnVersion & BITS(0, 7)),
		(uint16_t)(u2FwPeerVersion >> 8),
		(uint16_t)(u2FwPeerVersion & BITS(0, 7)));

	glResetTriggerUpdateCnt(u4RstFlag);

	prAdapter->u4HifDbgFlag |= DEG_HIF_DEFAULT_DUMP;
	halPrintHifDbgInfo(prAdapter);

#if CFG_WMT_RESET_API_SUPPORT
	wifi_rst.rst_trigger_flag = u4RstFlag;
	schedule_work(&(wifi_rst.rst_trigger_work));
#else
#if CFG_FTV_abc123_135_PATCH
	wifi_rst.rst_trigger_flag = u4RstFlag;
#endif
	wifi_rst.prGlueInfo = prAdapter->prGlueInfo;
	schedule_work(&(wifi_rst.rst_work));
#endif

	return fgResult;
}

void glGetRstReason(enum _ENUM_CHIP_RESET_REASON_TYPE_T
		    eReason)
{
	if (kalIsResetting())
		return;

	u8ResetTime = sched_clock();
	eResetReason = eReason;
}


/*----------------------------------------------------------------------------*/
/*!
 * @brief This routine is called for wifi reset
 *
 * @param   skb
 *          info
 *
 * @retval  0
 *          nonzero
 */
/*----------------------------------------------------------------------------*/
static void mtk_wifi_reset(struct work_struct *work)
{
	struct RESET_STRUCT *rst = container_of(work,
						struct RESET_STRUCT, rst_work);
	u_int8_t fgResult = FALSE;
	u_int8_t retry_cnt = 0;
#if CFG_FTV_abc123_135_PATCH
	u_int8_t force_reset = 0;
#endif

#if CFG_WMT_RESET_API_SUPPORT
	wifi_reset_end(rst->rst_data);
#else

#if CFG_FTV_abc123_135_PATCH
	if (wifi_rst.rst_trigger_flag & RST_FLAG_DO_CORE_DUMP) {
		force_reset = 0;
	}
	else {
		force_reset = 1;
	}

	fgResult = rst_L0_notify_step1(force_reset);

	while(fgResult == BT_RESET_NOT_READY) {
		DBGLOG(INIT, ERROR, "BT not ready for reset step 1 yet\n");

		kalMsleep(500);
		if(retry_cnt < BT_RESET_NOTIFY_MAX_RETRY) {
			/*
				corner case where wlanRemove() is called before this reset can
				startl wlanRemve() maybe called by rmmod or bus disconnect
			*/
			if (kalIsHalted()) {
				DBGLOG(INIT, ERROR, "device is halted, skip polling BT\n");
				return;
			}
			fgResult = rst_L0_notify_step1(force_reset);
			retry_cnt++;
		}
		else {
			DBGLOG(INIT, ERROR,
				"BT not ready for reset step 1 => give up\n");
			force_reset = 1;
			fgResult = rst_L0_notify_step1(force_reset);
			break;
		}
	}
#else
	fgResult = rst_L0_notify_step1(0);

	while(fgResult == BT_RESET_NOT_READY) {
		DBGLOG(INIT, ERROR, "BT not ready for reset step 1 yet\n");
		if(retry_cnt < BT_RESET_NOTIFY_MAX_RETRY) {
			kalMsleep(500);
			fgResult = rst_L0_notify_step1(0);
			retry_cnt++;
		}
		else {
			kalMsleep(500);
			fgResult = rst_L0_notify_step1(1);
			break;
		}
	}

#endif

	wait_core_dump_end();

#if CFG_FTV_abc123_135_PATCH
	if(fgResult == BT_RESET_OK) {
		fgResult = rst_L0_notify_step2();

		while(fgResult == BT_RESET_NOT_READY) {
			DBGLOG(INIT, ERROR, "BT not ready for reset step 2 yet\n");

			if(retry_cnt < BT_RESET_NOTIFY_MAX_RETRY) {
				kalMsleep(500);
			/*
				corner case where wlanRemove() is called before this reset can
				startl wlanRemve() maybe called by rmmod or bus disconnect
			*/
				if (kalIsHalted()) {
					DBGLOG(INIT, ERROR, "device is halted, skip polling BT\n");
					return;
				}
				fgResult = rst_L0_notify_step2();
				retry_cnt++;
			}
			else {
				DBGLOG(INIT, ERROR,
					"BT not ready for reset step 2 => give up\n");
				break;
			}
		}
	}
#else
	fgResult = rst_L0_notify_step2();

	while(fgResult == BT_RESET_NOT_READY) {
		DBGLOG(INIT, ERROR, "BT not ready for reset step 2 yet\n");
		kalMsleep(500);
		fgResult = rst_L0_notify_step2();
	}
#endif

#if CFG_CHIP_RESET_HANG
	if (fgIsResetHangState == SER_L0_HANG_RST_NONE)
		fgIsResetHangState = SER_L0_HANG_RST_TRGING;
#endif

	if (is_bt_exist() == FALSE)
		kalRemoveProbe(rst->prGlueInfo);

#endif

	DBGLOG(INIT, STATE, "[SER][L0] flow end, fgResult=%d\n", fgResult);

}


#if CFG_WMT_RESET_API_SUPPORT

static void mtk_wifi_trigger_reset(struct work_struct *work)
{
	u_int8_t fgResult = FALSE;
	struct RESET_STRUCT *rst = container_of(work,
					struct RESET_STRUCT, rst_trigger_work);

	fgIsResetting = TRUE;
	/* Set the power off flag to FALSE in WMT to prevent chip power off
	 * after wlanProbe return failure, because we need to do core dump
	 * afterward.
	 */
	if (rst->rst_trigger_flag & RST_FLAG_PREVENT_POWER_OFF)
		mtk_wcn_set_connsys_power_off_flag(FALSE);

	fgResult = mtk_wcn_wmt_assert_timeout(WMTDRV_TYPE_WIFI, 0x40, 0);
	DBGLOG(INIT, INFO, "reset result %d, trigger flag 0x%x\n",
				fgResult, rst->rst_trigger_flag);
}

/* Weak reference for those platform doesn't support wmt functions */
u_int8_t __weak mtk_wcn_stp_coredump_start_get(void)
{
	return FALSE;
}


/*0= f/w assert flag is not set, others=f/w assert flag is set */
u_int8_t glIsWmtCodeDump(void)
{
	return mtk_wcn_stp_coredump_start_get();
}

/*----------------------------------------------------------------------------*/
/*!
 * @brief This routine is invoked when there is reset messages indicated
 *
 * @param   eSrcType
 *          eDstType
 *          eMsgType
 *          prMsgBody
 *          u4MsgLength
 *
 * @retval
 */
/*----------------------------------------------------------------------------*/
static void *glResetCallback(enum ENUM_WMTDRV_TYPE eSrcType,
			     enum ENUM_WMTDRV_TYPE eDstType,
			     enum ENUM_WMTMSG_TYPE eMsgType, void *prMsgBody,
			     unsigned int u4MsgLength)
{
	switch (eMsgType) {
	case WMTMSG_TYPE_RESET:
		if (u4MsgLength == sizeof(enum ENUM_WMTRSTMSG_TYPE)) {
			enum ENUM_WMTRSTMSG_TYPE *prRstMsg =
					(enum ENUM_WMTRSTMSG_TYPE *) prMsgBody;

			switch (*prRstMsg) {
			case WMTRSTMSG_RESET_START:
				DBGLOG(INIT, WARN, "Whole chip reset start!\n");
				wifi_reset_start();
				break;

			case WMTRSTMSG_RESET_END:
				DBGLOG(INIT, WARN, "Whole chip reset end!\n");
				fgIsResetting = FALSE;
				wifi_rst.rst_data = RESET_SUCCESS;
				schedule_work(&(wifi_rst.rst_work));
				break;

			case WMTRSTMSG_RESET_END_FAIL:
				DBGLOG(INIT, WARN, "Whole chip reset fail!\n");
				fgIsResetting = FALSE;
				wifi_rst.rst_data = RESET_FAIL;
				schedule_work(&(wifi_rst.rst_work));
				break;

			default:
				break;
			}
		}
		break;

	default:
		break;
	}

	return NULL;
}
#else
static u_int8_t is_bt_exist(void)
{
	typedef int (*p_bt_fun_type) (int);
	p_bt_fun_type bt_func;
	char *bt_func_name = "WF_rst_L0_notify_BT_step1";

	bt_func = (p_bt_fun_type) kal_kallsyms_lookup_name(bt_func_name);
	if (bt_func) {
		kal_kallsyms_put(bt_func_name);
		return TRUE;
	}

	DBGLOG(INIT, ERROR, "[SER][L0] %s does not exist\n", bt_func_name);
	return FALSE;
}

static u_int8_t rst_L0_notify_step1(u_int8_t force_reset)
{
	if (eResetReason != RST_BT_TRIGGER) {
		typedef int (*p_bt_fun_type) (int);
		p_bt_fun_type bt_func;
		char *bt_func_name = "WF_rst_L0_notify_BT_step1";

		DBGLOG(INIT, STATE, "[SER][L0] %s\n", bt_func_name);
		bt_func =
			(p_bt_fun_type) kal_kallsyms_lookup_name(bt_func_name);
		if (bt_func) {
			if(bt_func(force_reset) != TRUE) {
				kal_kallsyms_put(bt_func_name);
				return BT_RESET_NOT_READY;
			}
			else {
				kal_kallsyms_put(bt_func_name);
			}
		} else {
			DBGLOG(INIT, ERROR,
				"[SER][L0] %s does not exist\n", bt_func_name);
			return BT_RESET_FUNC_NOT_FOUND;
		}
	}

	return BT_RESET_OK;
}

static u_int8_t rst_L0_notify_step2(void)
{

#ifdef CFG_SUPPORT_CONNAC2X
	if (eResetReason == RST_BT_TRIGGER) {
		typedef void (*p_bt_fun_type) (void);
		p_bt_fun_type bt_func;
		char *bt_func_name = "WF_rst_L0_notify_BT_step2";

		bt_func =
			(p_bt_fun_type) kal_kallsyms_lookup_name(bt_func_name);
		if (bt_func) {
			if(bt_func() != TRUE) {
				kal_kallsyms_put(bt_func_name);
				return BT_RESET_NOT_READY;
			}
			else {
				kal_kallsyms_put(bt_func_name);
			}
		} else {
			DBGLOG(INIT, WARN, "[SER][L0] %s does not exist\n",
							bt_func_name);
			return BT_RESET_FUNC_NOT_FOUND;
		}
	} else {
		/* if wifi trigger, then wait bt ready notify */
		DBGLOG(INIT, WARN, "[SER][L0] not support..\n");
	}
#else
	typedef int (*p_bt_fun_type) (void);
	p_bt_fun_type bt_func;
	char *bt_func_name = "WF_rst_L0_notify_BT_step2";

	DBGLOG(INIT, STATE, "[SER][L0] %s\n", bt_func_name);
	bt_func =
		(p_bt_fun_type) kal_kallsyms_lookup_name(bt_func_name);
	if (bt_func) {
		if(bt_func() != TRUE) {
			kal_kallsyms_put(bt_func_name);
			return BT_RESET_NOT_READY;
		}
		else {
			kal_kallsyms_put(bt_func_name);
		}
	} else {
		DBGLOG(INIT, WARN, "[SER][L0] %s does not exist\n",
							bt_func_name);
		return BT_RESET_FUNC_NOT_FOUND;
	}
#endif
	return BT_RESET_OK;
}

static void wait_core_dump_end(void)
{
#ifdef CFG_SUPPORT_CONNAC2X
	if (eResetReason == RST_OID_TIMEOUT)
		return;
	DBGLOG(INIT, WARN, "[SER][L0] not support..\n");
#endif
}

int32_t BT_rst_L0_notify_WF_step1(int32_t force_reset)
{
	if(force_reset == 0) {
		if (kalIsResetting()) {
			return FALSE;
		}
	}

	GL_RESET_TRIGGER(NULL, RST_FLAG_CHIP_RESET, RST_BT_TRIGGER);

	return TRUE;
}
EXPORT_SYMBOL(BT_rst_L0_notify_WF_step1);

int32_t BT_rst_L0_notify_WF_step2(int32_t reserved)
{
	DBGLOG(INIT, WARN, "[SER][L0] not support...\n");

	return 0;
}
EXPORT_SYMBOL(BT_rst_L0_notify_WF_step2);

#endif


#else

u_int8_t kalIsResetting(void)
{
	return FALSE;
}

#endif

