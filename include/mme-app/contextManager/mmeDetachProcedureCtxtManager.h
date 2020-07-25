 /*
 * Copyright 2019-present, Infosys Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __MmeDetachProcedureCtxtManager__
#define __MmeDetachProcedureCtxtManager__
/******************************************************
* mmeDetachProcedureCtxtManager.h
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/ctxtManagerTmpls/blockPoolManager.h.tt>
 ***************************************/
#include "memPoolManager.h"

namespace mme
{
	class MmeDetachProcedureCtxt;
	class MmeDetachProcedureCtxtManager
	{
		public:
			/****************************************
			* MmeDetachProcedureCtxtManager
			*  constructor
			****************************************/
			MmeDetachProcedureCtxtManager(int numOfBlocks);
			
			/****************************************
			* MmeDetachProcedureCtxtManager
			*    Destructor
			****************************************/
			~MmeDetachProcedureCtxtManager();
			
			/******************************************
			 * allocateMmeDetachProcedureCtxt
			 * allocate MmeDetachProcedureCtxt data block
			 ******************************************/
			MmeDetachProcedureCtxt* allocateMmeDetachProcedureCtxt();
			
			/******************************************
			 * deallocateMmeDetachProcedureCtxt
			 * deallocate a MmeDetachProcedureCtxt data block
			 ******************************************/
			void deallocateMmeDetachProcedureCtxt(MmeDetachProcedureCtxt* MmeDetachProcedureCtxtp );
	
		private:
			cmn::memPool::MemPoolManager<MmeDetachProcedureCtxt> poolManager_m;
	};
};

#endif
		
		
