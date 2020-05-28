/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
 /******************************************************
 * attachWfInitCtxtRespAttCmp.h
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.h.tt>
 ******************************************************/
 
#ifndef __AttachWfInitCtxtRespAttCmp__
#define __AttachWfInitCtxtRespAttCmp__

#include "state.h"

namespace mme {

	class AttachWfInitCtxtRespAttCmp : public SM::State
	{
		public:
			/******************************************
			* Instance 
			*    Creates static instance for the state
			*******************************************/
			static AttachWfInitCtxtRespAttCmp* Instance();

			/****************************************
			* AttachWfInitCtxtRespAttCmp
			*    Destructor
			****************************************/
			~AttachWfInitCtxtRespAttCmp();			
			
			/******************************************
			* initialize
			*  Initializes action handlers for the state
			* and next state
			******************************************/
			void initialize();
	
		private:
			/****************************************
			* AttachWfInitCtxtRespAttCmp
			*    Private constructor
			****************************************/
			AttachWfInitCtxtRespAttCmp();  
	};
};
#endif // __AttachWfInitCtxtRespAttCmp__
