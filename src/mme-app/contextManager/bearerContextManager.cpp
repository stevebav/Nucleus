 /*
 * Copyright 2019-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */ 
/******************************************************************************
 * bearerContextManager.cpp
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/ctxtManagerTmpls/blockPoolManager.cpp.tt>
 ******************************************************************************/

#include "memPoolManager.h"
#include "contextManager/dataBlocks.h"
#include "contextManager/bearerContextManager.h"

using namespace cmn::memPool;

namespace mme
{
	/******************************************************************************
	* Constructor
	******************************************************************************/
	BearerContextManager::BearerContextManager(int numOfBlocks):poolManager_m(numOfBlocks)
	{
	}
	
	/******************************************************************************
	* Destructor
	******************************************************************************/
	BearerContextManager::~BearerContextManager()
	{
	}
	
	/******************************************************************************
	* Allocate BearerContext data block
	******************************************************************************/
	BearerContext* BearerContextManager::allocateBearerContext()
	{
		BearerContext* BearerContext_p = poolManager_m.allocate();
		return BearerContext_p;
	}
	
	/******************************************************************************
	* Deallocate a BearerContext data block
	******************************************************************************/
	void BearerContextManager::deallocateBearerContext(BearerContext* BearerContextp )
	{
		poolManager_m.free( BearerContextp );
	}
}