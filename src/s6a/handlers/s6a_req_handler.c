/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>
#include <freeDiameter/libfdproto.h>

#include "s6a_config.h"
#include "err_codes.h"
#include "ipc_api.h"
#include "sec.h"
#include "msgType.h"

#include "s6a_fd.h"
#include "s6a.h"
#include "s6a_config.h"
#include "hss_message.h"

/************************************************************************
Current file : Stage  - AIR handler of S6A
ATTACH stages :
@@@	Stage 1 : IAM-->[stage1 handler]-->AIR, ULR
	Stage 2 : AIA, ULA -->[stage2 handler]--> Auth req
	Stage 3 : Auth resp-->[stage1 handler]-->Sec mode cmd
	Stage 4 : sec mode resp-->[stage1 handler]-->esm infor req
	Stage 5 : esm infor resp-->[stage1 handler]-->create session
	Stage 6 : create session resp-->[stage1 handler]-->init ctx setup
	Stage 7 : attach complete-->[stage1 handler]-->modify bearer
**************************************************************************/

/****Globals and externs ***/
extern int g_our_hss_fd;
extern s6a_config  g_s6a_cfg;
extern struct fd_dict_objects g_fd_dict_objs;
extern struct fd_dict_data g_fd_dict_data;
/****Global and externs end***/


void ulr_intermediate_cb(void * data, struct msg ** msg)
{
	dump_fd_msg(*msg);
}

/**
 * @brief Prepare ULR freediameter message, dump and post to HSS
 * @param[in] aia_msg - AIA info recvd from mme-app
 * @param[in] imsi - IMSI
 * @return int Sucess or failure code
 */
static int
send_FD_ULR(struct s6a_Q_msg *aia_msg, char imsi[])
{
	struct msg *fd_msg = NULL;
	struct avp *avp_ptr = NULL;
	int res = SUCCESS;
	struct s6a_sess_info s6a_sess = {.sess_id="", .sess_id_len = 0};
	char event = 12;
	union avp_value val;

	/*Create FD header and message for update location request.*/
	if(SUCCESS != (res = create_fd_sess_id(&s6a_sess, aia_msg->ue_idx)))
		return res;

	CHECK_FCT_DO(fd_msg_new(g_fd_dict_objs.ULR, MSGFL_ALLOC_ETEID, &fd_msg),
			return S6A_FD_ERROR)

	/*AVP: Session-Id*/
	val.os.data = (unsigned char*)s6a_sess.sess_id;
	val.os.len = strlen(s6a_sess.sess_id);
	add_fd_msg(&val, g_fd_dict_objs.sess_id, &fd_msg);

	/*AVP: Auth-Session-State*/
	val.i32 = 1; /*NO_STATE_MAINTAINED*/
	val.os.len = 0;
	add_fd_msg(&val, g_fd_dict_objs.auth_sess_state, &fd_msg);

	/*AVP: Origin-Host/Realm*/
	CHECK_FCT_DO(fd_msg_add_origin(fd_msg, 0), return S6A_FD_ERROR);

	/*AVP: Destination-Host*/
	val.os.data = (unsigned char*)g_s6a_cfg.hss_host_name;
	val.os.len = strlen(g_s6a_cfg.hss_host_name);
	add_fd_msg(&val, g_fd_dict_objs.dest_host, &fd_msg);

	/*AVP: Destination-Realm*/
	val.os.data = (unsigned char*)g_s6a_cfg.realm;
	val.os.len = strlen(g_s6a_cfg.realm);
	add_fd_msg(&val, g_fd_dict_objs.dest_realm, &fd_msg);

	/*AVP: User-Name*/
	val.os.data = (unsigned char*)imsi;
	val.os.len = strlen(imsi);
	add_fd_msg(&val, g_fd_dict_objs.user_name, &fd_msg);

	/*AVP: RAT-Type*/
	val.u32 = S6A_RAT_EUTRAN;
	val.os.len = 0;
	add_fd_msg(&val, g_fd_dict_objs.RAT_type, &fd_msg);

	/*AVP: ULR-Flags*/
	val.u32 = ULR_FLAG_S6AS6D_IND | ULR_FLAG_INIT_ATCH_IND ;
	add_fd_msg(&val, g_fd_dict_objs.ULR_flags, &fd_msg);

	/*AVP: Visited-PLMN-Id*/
	val.os.data = (unsigned char*)aia_msg->tai.plmn_id.idx;
	val.os.len = 3;
	add_fd_msg(&val, g_fd_dict_objs.visited_PLMN_id, &fd_msg);
	
	for(int i = 0; i < aia_msg->supp_features_list.count ; i++)
	{
	        /*AVP: Supported Features*/
            CHECK_FCT_DO(fd_msg_avp_new(g_fd_dict_objs.supported_features, 0, &avp_ptr), return -1);
            CHECK_FCT_DO(fd_msg_avp_add(fd_msg, MSG_BRW_LAST_CHILD, avp_ptr), return -1);

            val.u32 = 10415;
            add_fd_msg(&val, g_fd_dict_objs.vendor_id_supported, (struct msg**)&avp_ptr);


	        /*AVP: Supported Features
             *----->AVP: Feature-List-Id*/
            val.u32 = aia_msg->supp_features_list.supp_features[i].feature_list_id ;
            add_fd_msg(&val, g_fd_dict_objs.feature_list_id,
                            (struct msg**)&avp_ptr);

            /*AVP: Supported Features
             * ------>AVP: Feature-List*/
            val.u32 = aia_msg->supp_features_list.supp_features[i].feature_list;
            add_fd_msg(&val, g_fd_dict_objs.feature_list,
                            (struct msg**)&avp_ptr);
	}
	dump_fd_msg(fd_msg);

	/*Post ULR to HSS*/
	CHECK_FCT_DO(fd_msg_send(&fd_msg, ulr_intermediate_cb, (void*)&event),
			return S6A_FD_ERROR);

	return SUCCESS;
}


/**
 * @brief dump recvd aia queue msg
 * @param[in] air_msg - IMSI
 * @return void
 */
void
dump_s6a_msg(struct s6a_Q_msg *air_msg)
{
	log_msg(LOG_INFO, "Received index= %d",air_msg->ue_idx);
	log_msg(LOG_INFO, "Received plmn %x %x %x ",air_msg->tai.plmn_id.idx[0],
			air_msg->tai.plmn_id.idx[1], air_msg->tai.plmn_id.idx[2]);
}

/**
 * @brief Prepare AIR freediameter message, dump and post to HSS
 * @param[in] aia_msg - AIA info recvd from mme-app
 * @param[in] imsi - IMSI
 * @return int Sucess or failure code
 */
static int
send_FD_AIR(struct s6a_Q_msg *aia_msg, char imsi[])
{
	struct avp *avp_ptr = NULL;
	struct msg *fd_msg = NULL;
	int res = 0;
	struct s6a_sess_info s6a_sess = {.sess_id="", .sess_id_len = 0};
	union avp_value val;

	log_msg(LOG_INFO, "In Send AIR:");
	dump_s6a_msg(aia_msg);

	/*Create FD header and message for authentication info request.*/
	if(SUCCESS != (res = create_fd_sess_id(&s6a_sess, aia_msg->ue_idx)))
		return res;

	CHECK_FCT_DO(fd_msg_new(g_fd_dict_objs.AIR, MSGFL_ALLOC_ETEID, &fd_msg),
			return S6A_FD_ERROR);

	/*AVP: Session-Id*/
	val.os.data = (unsigned char*)s6a_sess.sess_id;
	val.os.len = strlen(s6a_sess.sess_id);
	add_fd_msg(&val, g_fd_dict_objs.sess_id, &fd_msg);

	/*AVP: Auth-Session-State*/
	val.i32 = 1; /*NO_STATE_MAINTAINED*/
	val.os.len = 0;
	add_fd_msg(&val, g_fd_dict_objs.auth_sess_state, &fd_msg);

	/*AVP: Origin-Host/Realm*/
	CHECK_FCT_DO(fd_msg_add_origin(fd_msg, 0), return S6A_FD_ERROR)

	/*AVP: Destination-Host*/
	val.os.data = (unsigned char*)g_s6a_cfg.hss_host_name;
	val.os.len = strlen(g_s6a_cfg.hss_host_name);
	add_fd_msg(&val, g_fd_dict_objs.dest_host, &fd_msg);

	/*AVP: Destination-Realm*/
	val.os.data = (unsigned char*)g_s6a_cfg.realm;
	val.os.len = strlen(g_s6a_cfg.realm);
	add_fd_msg(&val, g_fd_dict_objs.dest_realm, &fd_msg);

	/*AVP: User-Name*/
	val.os.data = (unsigned char*)imsi;
	val.os.len = strlen(imsi);
	add_fd_msg(&val, g_fd_dict_objs.user_name, &fd_msg);

	/*AVP: Visited-PLMN-Id*/
	val.os.data = (unsigned char*)aia_msg->tai.plmn_id.idx;
	val.os.len = 3;
	add_fd_msg(&val, g_fd_dict_objs.visited_PLMN_id, &fd_msg);

	/*TODO: recheck. Can it be grouped better way*/
	/*AVP: Requested-EUTRAN-Authentication-Info*/
	CHECK_FCT_DO(fd_msg_avp_new(
		g_fd_dict_objs.req_EUTRAN_auth_info, 0, &avp_ptr),
		return -1);
	CHECK_FCT_DO(fd_msg_avp_add(fd_msg, MSG_BRW_LAST_CHILD, avp_ptr), return -1);

	/*AVP: Requested-EUTRAN-Authentication-Info
	 *----->AVP: Number-Of-Requested-Vectors(1410)*/
    if (aia_msg->auts.len)
	  val.i32 = 1;
    else
	  val.i32 = 5;
	val.os.len = 0;
	add_fd_msg(&val, g_fd_dict_objs.no_of_req_vectors,
			(struct msg**)&avp_ptr);

	/*AVP: Requested-EUTRAN-Authentication-Info
	 * ------>AVP: Immediate-Response-Preferred*/
	val.u32 = 0;
	add_fd_msg(&val, g_fd_dict_objs.immediate_resp_pref,
			(struct msg**)&avp_ptr);

    if(aia_msg->auts.len)
    {
        val.os.data = (unsigned char*)aia_msg->auts.val;
        val.os.len = aia_msg->auts.len;
        add_fd_msg(&val, g_fd_dict_objs.resync_info, (struct msg**)&avp_ptr);
    }
	
    dump_fd_msg(fd_msg);

	/*post AIR to hss */
	CHECK_FCT_DO(fd_msg_send(&fd_msg, NULL, NULL), return S6A_FD_ERROR);

	return SUCCESS;
}

/**
API to send AIR oto customer HSS over custome RPC
*/
static void
send_rpc_AIR(struct s6a_Q_msg *air_msg, char imsi[])
{
	struct hss_req_msg msg;

	msg.hdr = HSS_AIR_MSG;
	msg.ue_idx = air_msg->ue_idx;

	strncpy(msg.data.air.imsi, imsi, IMSI_STR_LEN);
	memcpy(msg.data.air.plmn_id, air_msg->tai.plmn_id.idx, 3);

	if (write(g_our_hss_fd, &msg, HSS_REQ_MSG_SIZE) < 0) {
		log_msg(LOG_ERROR, "HSS AIR msg send failed.");
		 		perror("writing on stream socket");
	}
	log_msg(LOG_INFO, "AIR msg send to hss for ue_idx %d",
		air_msg->ue_idx);
}

/**
API to send ULR oto customer HSS over custome RPC
*/
static void
send_rpc_ULR(struct s6a_Q_msg *ulr_msg, char imsi[])
{
	struct hss_req_msg msg;

	msg.hdr = HSS_ULR_MSG;
	msg.ue_idx = ulr_msg->ue_idx;

	strncpy(msg.data.air.imsi, imsi, IMSI_STR_LEN);
	memcpy(msg.data.air.plmn_id, ulr_msg->tai.plmn_id.idx, 3);

	if (write(g_our_hss_fd, &msg, HSS_REQ_MSG_SIZE) < 0) {
		log_msg(LOG_ERROR, "HSS ULR msg send failed.");
		perror("writing on stream socket");
	}
	log_msg(LOG_INFO, "ULR msg send to hss");
}


/**
 * @brief convert binary imsi to string imsi
 * Binary imsi is stored in 8 bytes, each nibble representing each imsi char.
 * char imsi stroes each char in 1 byte.
 * @param[in] b_imsi : Binary imsi
 * @param[out] s_imsi : Converted string imsi
 * @return void
 */
void
imsi_bin_to_str(unsigned char *b_imsi, char *s_imsi)
{
	if(NULL == b_imsi || NULL == s_imsi) return;

	memset(s_imsi, 0, STR_IMSI_LEN);

	/* Byte 'AB' in b_imsi, is converted to two bytes 'A', 'B' in s_imsi*/
	s_imsi[0] = '0' + ((b_imsi[0]>>4) & 0x0F);

	for(int i=1; i < BINARY_IMSI_LEN; ++i) {
		s_imsi[(i*2)-1] = '0' + (b_imsi[i] & 0x0F);
		s_imsi[(i*2)] = '0' + ((b_imsi[i]>>4) & 0x0F);
	}
	s_imsi[(BINARY_IMSI_LEN*2)-1] = '\0';
}

/**
 * @brief Post AIR and ULR messsages simultaneously to HSS.
 * @return int Sucess or failure code
 */
static int
AIR_processing(struct s6a_Q_msg * air_msg)
{
	log_msg(LOG_INFO, "IMSI recvd - %s %d ", air_msg->imsi, air_msg->msg_type);

	if(HSS_FD == g_s6a_cfg.hss_type) {
		if(air_msg->msg_type == auth_info_request)
			/*post to next processing*/
			send_FD_AIR(air_msg, (char *)air_msg-> imsi);
		else if(air_msg->msg_type == update_loc_request)
			send_FD_ULR(air_msg, (char *)air_msg-> imsi);
	} else {
		log_msg(LOG_INFO, "Sending over IPC");
		send_rpc_AIR(air_msg, (char *) air_msg->imsi);
		send_rpc_ULR(air_msg, (char *) air_msg->imsi);

	}

	return SUCCESS;
}

/*
* Thread function for stage.
*/
void*
S6Req_handler(void *data)
{
	log_msg(LOG_INFO, "S6 message received from mme-app");

	AIR_processing((struct s6a_Q_msg *)data);
	
	return NULL;
}
