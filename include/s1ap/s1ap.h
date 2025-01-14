/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __S1AP_H_
#define __S1AP_H_

#include <stdbool.h>

#include "s1ap_structs.h"
#include "log.h"
#include "s1ap_ie.h"
#include "InitiatingMessage.h"
#include "SuccessfulOutcome.h"
#include "UnsuccessfulOutcome.h"
#include "common_proc_info.h"
#include "msgType.h"
#include "s1ap_config.h"


/* Put all the instances within this */
typedef struct s1ap_instance 
{
	s1ap_config_t *s1ap_config;
}s1ap_instance_t;

int
s1_init_ctx_resp_handler(SuccessfulOutcome_t *msg);

int convertToInitUeProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies, initial_ue_msg_t* s1Msg);
int convertUplinkNasToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies, uplink_nas_t *s1Msg);

int convertUeCtxRelReqToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertInitCtxRspToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE* proto_ies);
int convertUeCtxRelComplToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE* proto_ies);
int convertUehoReqToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertHoAcklToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE* proto_ies);
int convertHoNotifyToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertEnbStatusTransferToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertHoFailureToProtoIe(UnsuccessfulOutcome_t *msg, struct proto_IE* proto_ies);
int convertUeHoCancelToProtoIe(InitiatingMessage_t *msg, struct proto_IE* proto_ies);
int convertErabModIndToProtoIe(InitiatingMessage_t *msg, struct proto_IE *proto_ies);
int convertErabSetupRespToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE *proto_ies);
int convertErabRelRespToProtoIe(SuccessfulOutcome_t *msg, struct proto_IE *proto_ies);
int convertPathSwitchReqToProtoIe(InitiatingMessage_t *msg, struct proto_IE *proto_ies);

int
s1_setup_handler(InitiatingMessage_t *msg, int enb_fd);

void
handle_s1ap_message(void *message);

int
init_s1ap();

void
read_config();

void*
IAM_handler(void *data);

int
s1_ctx_release_resp_handler(SuccessfulOutcome_t *msg);

int
s1_ctx_release_request_handler(InitiatingMessage_t *msg);

int 
s1_ctx_release_complete_handler(SuccessfulOutcome_t *msg);

int
s1_handover_ack_handler(SuccessfulOutcome_t *msg);

int
s1_handover_required_handler(InitiatingMessage_t *msg, int enb_fd);

int
s1_handover_notify_handler(InitiatingMessage_t *msg);

int
s1_enb_status_transfer_handler(InitiatingMessage_t *msg);

int
s1_handover_faliure_handler(UnsuccessfulOutcome_t *msg);

int
s1_handover_cancel_handler(InitiatingMessage_t *msg);


int
erab_mod_indication_handler(InitiatingMessage_t *msg);


int
erab_setup_response_handler(SuccessfulOutcome_t *msg);

int
erab_release_response_handler(SuccessfulOutcome_t *msg);

int
path_switch_req_handler(InitiatingMessage_t *msg, int enb_fd);

int s1ap_mme_encode_ue_context_release_command(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_paging_request(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_initiating(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_outcome(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_initial_context_setup_request(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_service_rej(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_tau_rej(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_s1_setup_failure(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_s1_setup_response(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_attach_rej(
        struct s1ap_common_req_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_handover_request(
        struct handover_request_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_handover_command(
        struct handover_command_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_handover_mme_status_transfer(
        struct mme_status_transfer_Q_msg *s1apPDU,
        uint8_t **buffer,
        uint32_t *length);

int s1ap_mme_encode_handover_prep_failure(
        struct handover_preparation_failure_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_handover_cancel_ack(
        struct handover_cancel_ack_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_erab_mod_confirmation(
  	struct erab_mod_confirm *s1apPDU,
  	uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_erab_setup_request(
  	struct erabsu_ctx_req_Q_msg *s1apPDU,
  	uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_erab_release_command(
    struct erab_release_command_Q_msg *s1apPDU,
    uint8_t **buffer, uint32_t *length);

int s1ap_mme_encode_path_switch_req_ack(
        struct path_switch_req_ack_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int s1ap_mme_path_switch_req_failure(
        struct path_switch_req_fail_Q_msg *s1apPDU,
        uint8_t **buffer, uint32_t *length);

int
s1ap_mme_decode_initiating (InitiatingMessage_t *initiating_p, int enb_fd);

int
s1ap_mme_decode_successfull_outcome (SuccessfulOutcome_t *initiating_p);

int
s1ap_mme_decode_unsuccessfull_outcome (UnsuccessfulOutcome_t *initiating_p);

int
copyU16(unsigned char *buffer, uint32_t val);

int
send_sctp_msg(int connSock, unsigned char *buffer, size_t len, uint16_t stream_no);

void
buffer_copy(struct Buffer *buffer, void *value, size_t size);

/**
 * @brief Decode int value from the byte array received in the s1ap incoming
 * packet.
 * @param[in] bytes - Array of bytes in packet
 * @param[in] len - Length of the bytes array from which to extract the int
 * @return Integer value extracted out of bytes array. 0 if failed.
 */
int
decode_int_val(unsigned char *bytes, short len);

char*
msg_to_hex_str(const char *msg, int len, char **buffer);

unsigned short
get_length(char **msg);
#endif /*__S1AP_H_*/
