/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/p9/procedures/hwp/pm/p9_suspend_powman.H $   */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2016,2017                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
//-----------------------------------------------------------------------------------
///
/// @file p9_suspend_powman.H
/// @brief Suspend the OCC/PM
//
// *HWP HWP Owner: Adam Hale Adam.Samuel.Hale@ibm.com
// *HWP FW Owner: Raja Das rajadas2@in.ibm.com
// *HWP Team: PM
// *HWP Level: 3
// *HWP Consumed by: SBE
// ----------------------------------------------------------------------------------

#ifndef P9_SUSPEND_POWMAN__
#define P9_SUSPEND_POWMAN__

//-------------------------------------------------------
// Includes
//-------------------------------------------------------
#include <fapi2.H>

//-------------------------------------------------------
// Structure definitions
//-------------------------------------------------------

//Function pointer typedef definition for HWP call support
typedef fapi2::ReturnCode
(*p9_suspend_powman_FP_t) (const fapi2::Target<fapi2::TARGET_TYPE_PROC_CHIP>&);

//-------------------------------------------------------
// Constant definitions
//-------------------------------------------------------

//--------------------------------------------------------
// Function prototypes
//--------------------------------------------------------

extern "C"
{

/// @brief Suspend the OCC/PM
/// @param[in] i_target => P9 chip target
/// @return FAPI_RC_SUCCESS if the read/write completes successfully
    fapi2::ReturnCode p9_suspend_powman(const fapi2::Target<fapi2::TARGET_TYPE_PROC_CHIP>& i_target);


}//extern "C"

#endif //P9_SUSPEND_POWMAN_

