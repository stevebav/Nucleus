
/*
 * Copyright 2019-present, Infosys Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <mmeSmDefs.h>
#include <smTypes.h>
#include <string>
/**************************************
 * 
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/mmeSmDefs.cpp.tt>
 **************************************/
using namespace std;
using namespace SM;

SM::SmUtility* smUtil = SM::SmUtility::Instance();

void populateEventStringMap()
{
    smUtil->addEventToStrEntry(ABORT_EVENT,"ABORT_EVENT");      
    smUtil->addEventToStrEntry(AIA_FROM_HSS,"AIA_FROM_HSS");      
    smUtil->addEventToStrEntry(ATT_CMP_FROM_UE,"ATT_CMP_FROM_UE");      
    smUtil->addEventToStrEntry(ATTACH_REQ_FROM_UE,"ATTACH_REQ_FROM_UE");      
    smUtil->addEventToStrEntry(AUTH_RESP_FAILURE,"AUTH_RESP_FAILURE");      
    smUtil->addEventToStrEntry(AUTH_RESP_FROM_UE,"AUTH_RESP_FROM_UE");      
    smUtil->addEventToStrEntry(AUTH_RESP_SUCCESS,"AUTH_RESP_SUCCESS");      
    smUtil->addEventToStrEntry(AUTH_RESP_SYNC_FAILURE,"AUTH_RESP_SYNC_FAILURE");      
    smUtil->addEventToStrEntry(CLR_FROM_HSS,"CLR_FROM_HSS");      
    smUtil->addEventToStrEntry(CS_RESP_FROM_SGW,"CS_RESP_FROM_SGW");      
    smUtil->addEventToStrEntry(DDN_FROM_SGW,"DDN_FROM_SGW");      
    smUtil->addEventToStrEntry(DEFAULT_EVENT,"DEFAULT_EVENT");      
    smUtil->addEventToStrEntry(DEL_SESSION_RESP_FROM_SGW,"DEL_SESSION_RESP_FROM_SGW");      
    smUtil->addEventToStrEntry(DETACH_ACCEPT_FROM_UE,"DETACH_ACCEPT_FROM_UE");      
    smUtil->addEventToStrEntry(DETACH_REQ_FROM_UE,"DETACH_REQ_FROM_UE");      
    smUtil->addEventToStrEntry(ENB_STATUS_TRANFER_FROM_SRC_ENB,"ENB_STATUS_TRANFER_FROM_SRC_ENB");      
    smUtil->addEventToStrEntry(ESM_INFO_NOT_REQUIRED,"ESM_INFO_NOT_REQUIRED");      
    smUtil->addEventToStrEntry(ESM_INFO_REQUIRED,"ESM_INFO_REQUIRED");      
    smUtil->addEventToStrEntry(ESM_INFO_RESP_FROM_UE,"ESM_INFO_RESP_FROM_UE");      
    smUtil->addEventToStrEntry(HO_NOTIFY_FROM_ENB,"HO_NOTIFY_FROM_ENB");      
    smUtil->addEventToStrEntry(HO_REQUEST_ACK_FROM_ENB,"HO_REQUEST_ACK_FROM_ENB");      
    smUtil->addEventToStrEntry(HO_REQUIRED_FROM_ENB,"HO_REQUIRED_FROM_ENB");      
    smUtil->addEventToStrEntry(IDENTITY_RESPONSE_FROM_UE,"IDENTITY_RESPONSE_FROM_UE");      
    smUtil->addEventToStrEntry(IMSI_VALIDATION_FAILURE,"IMSI_VALIDATION_FAILURE");      
    smUtil->addEventToStrEntry(IMSI_VALIDATION_SUCCESS,"IMSI_VALIDATION_SUCCESS");      
    smUtil->addEventToStrEntry(INIT_CTXT_RESP_FROM_UE,"INIT_CTXT_RESP_FROM_UE");      
    smUtil->addEventToStrEntry(INTRA_S1HO_START,"INTRA_S1HO_START");      
    smUtil->addEventToStrEntry(MB_RESP_FROM_SGW,"MB_RESP_FROM_SGW");      
    smUtil->addEventToStrEntry(REL_AB_RESP_FROM_SGW,"REL_AB_RESP_FROM_SGW");      
    smUtil->addEventToStrEntry(S1_REL_REQ_FROM_UE,"S1_REL_REQ_FROM_UE");      
    smUtil->addEventToStrEntry(SEC_MODE_RESP_FROM_UE,"SEC_MODE_RESP_FROM_UE");      
    smUtil->addEventToStrEntry(SERVICE_REQUEST_FROM_UE,"SERVICE_REQUEST_FROM_UE");      
    smUtil->addEventToStrEntry(STATE_GUARD_TIMEOUT,"STATE_GUARD_TIMEOUT");      
    smUtil->addEventToStrEntry(TAU_NOT_REQUIRED,"TAU_NOT_REQUIRED");      
    smUtil->addEventToStrEntry(TAU_REQUEST_FROM_UE,"TAU_REQUEST_FROM_UE");      
    smUtil->addEventToStrEntry(TAU_REQUIRED,"TAU_REQUIRED");      
    smUtil->addEventToStrEntry(UE_CTXT_REL_COMP_FROM_ENB,"UE_CTXT_REL_COMP_FROM_ENB");      
    smUtil->addEventToStrEntry(ULA_FROM_HSS,"ULA_FROM_HSS");      
    smUtil->addEventToStrEntry(VALIDATE_IMSI,"VALIDATE_IMSI");      
}

void populateStateStringMap()
{
    smUtil->addStateToStrEntry(default_state,"default_state");
    smUtil->addStateToStrEntry(attach_start,"attach_start");
    smUtil->addStateToStrEntry(attach_wf_aia,"attach_wf_aia");
    smUtil->addStateToStrEntry(attach_wf_att_cmp,"attach_wf_att_cmp");
    smUtil->addStateToStrEntry(attach_wf_auth_resp,"attach_wf_auth_resp");
    smUtil->addStateToStrEntry(attach_wf_auth_resp_validate,"attach_wf_auth_resp_validate");
    smUtil->addStateToStrEntry(attach_wf_cs_resp,"attach_wf_cs_resp");
    smUtil->addStateToStrEntry(attach_wf_esm_info_check,"attach_wf_esm_info_check");
    smUtil->addStateToStrEntry(attach_wf_esm_info_resp,"attach_wf_esm_info_resp");
    smUtil->addStateToStrEntry(attach_wf_identity_response,"attach_wf_identity_response");
    smUtil->addStateToStrEntry(attach_wf_imsi_validate_action,"attach_wf_imsi_validate_action");
    smUtil->addStateToStrEntry(attach_wf_init_ctxt_resp,"attach_wf_init_ctxt_resp");
    smUtil->addStateToStrEntry(attach_wf_init_ctxt_resp_att_cmp,"attach_wf_init_ctxt_resp_att_cmp");
    smUtil->addStateToStrEntry(attach_wf_mb_resp,"attach_wf_mb_resp");
    smUtil->addStateToStrEntry(attach_wf_sec_cmp,"attach_wf_sec_cmp");
    smUtil->addStateToStrEntry(attach_wf_ula,"attach_wf_ula");
    smUtil->addStateToStrEntry(default_mme_state,"default_mme_state");
    smUtil->addStateToStrEntry(detach_start,"detach_start");
    smUtil->addStateToStrEntry(detach_wf_del_session_resp,"detach_wf_del_session_resp");
    smUtil->addStateToStrEntry(intra_s1_ho_start,"intra_s1_ho_start");
    smUtil->addStateToStrEntry(ni_detach_start,"ni_detach_start");
    smUtil->addStateToStrEntry(ni_detach_wf_del_sess_resp,"ni_detach_wf_del_sess_resp");
    smUtil->addStateToStrEntry(ni_detach_wf_det_accpt_del_sess_resp,"ni_detach_wf_det_accpt_del_sess_resp");
    smUtil->addStateToStrEntry(ni_detach_wf_detach_accept,"ni_detach_wf_detach_accept");
    smUtil->addStateToStrEntry(ni_detach_wf_s1_rel_comp,"ni_detach_wf_s1_rel_comp");
    smUtil->addStateToStrEntry(paging_start,"paging_start");
    smUtil->addStateToStrEntry(paging_wf_service_req,"paging_wf_service_req");
    smUtil->addStateToStrEntry(s1_ho_wf_ho_notify,"s1_ho_wf_ho_notify");
    smUtil->addStateToStrEntry(s1_ho_wf_ho_request_ack,"s1_ho_wf_ho_request_ack");
    smUtil->addStateToStrEntry(s1_ho_wf_modify_bearer_response,"s1_ho_wf_modify_bearer_response");
    smUtil->addStateToStrEntry(s1_ho_wf_tau_check,"s1_ho_wf_tau_check");
    smUtil->addStateToStrEntry(s1_ho_wf_tau_request,"s1_ho_wf_tau_request");
    smUtil->addStateToStrEntry(s1_release_start,"s1_release_start");
    smUtil->addStateToStrEntry(s1_release_wf_release_access_bearer_resp,"s1_release_wf_release_access_bearer_resp");
    smUtil->addStateToStrEntry(s1_release_wf_ue_ctxt_release_comp,"s1_release_wf_ue_ctxt_release_comp");
    smUtil->addStateToStrEntry(service_request_start,"service_request_start");
    smUtil->addStateToStrEntry(service_request_wf_aia,"service_request_wf_aia");
    smUtil->addStateToStrEntry(service_request_wf_auth_resp_validate,"service_request_wf_auth_resp_validate");
    smUtil->addStateToStrEntry(service_request_wf_auth_response,"service_request_wf_auth_response");
    smUtil->addStateToStrEntry(service_request_wf_init_ctxt_resp,"service_request_wf_init_ctxt_resp");
    smUtil->addStateToStrEntry(service_request_wf_mb_resp,"service_request_wf_mb_resp");
    smUtil->addStateToStrEntry(service_request_wf_sec_cmp,"service_request_wf_sec_cmp");
    smUtil->addStateToStrEntry(tau_start,"tau_start");
}
