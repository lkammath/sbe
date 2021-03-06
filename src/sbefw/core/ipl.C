/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/core/ipl.C $                                        */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2017,2018                        */
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
#include "fapi2.H"
#include "sberegaccess.H"

#include "ipl.H"

using namespace fapi2;

sbeRole g_sbeRole = SBE_ROLE_MASTER;

uint64_t G_ring_save[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// Globals
// TODO: via RTC 123602 This global needs to move to a class that will store the
// SBE FFDC.
fapi2::ReturnCode g_iplFailRc = FAPI2_RC_SUCCESS;

//----------------------------------------------------------------------------
// @note This is the responsibilty of caller to verify major/minor
//       number before calling this function

// @TODO via RTC 129077.
// This function should check for system checkstop as well.
ReturnCode sbeExecuteIstep (const uint8_t i_major, const uint8_t i_minor)
{
    #define SBE_FUNC "sbeExecuteIstep "
    SBE_INFO(SBE_FUNC"Major number:0x%x minor number:0x%x",
                       i_major, i_minor );

    ReturnCode rc = FAPI2_RC_SUCCESS;

    for(size_t entry = 0; entry < istepTable.len; entry++)
    {
        auto istepTableEntry = &istepTable.istepMajorArr[entry];
        if(( i_major == istepTableEntry->istepMajorNum ) &&
           ( i_minor <= istepTableEntry->len ))
        {
            auto istepMap = &istepTableEntry->istepMinorArr[i_minor-1];
            if(istepMap->istepWrapper != NULL)
            {
                rc = istepMap->istepWrapper(istepMap->istepHwp);
            }
            break;
        }
    }

    if(rc != FAPI2_RC_SUCCESS)
    {
        SBE_ERROR( SBE_FUNC" FAPI RC:0x%08X", rc);
        (void)SbeRegAccess::theSbeRegAccess().stateTransition(
                                                    SBE_DUMP_FAILURE_EVENT);
    }
    else
    {
        (void)SbeRegAccess::theSbeRegAccess().updateSbeStep(i_major, i_minor);
    } 

    return rc;
    #undef SBE_FUNC
}

//----------------------------------------------------------------------------
void sbeDoContinuousIpl()
{
    #define SBE_FUNC "sbeDoContinuousIpl "
    SBE_ENTER(SBE_FUNC);
    ReturnCode rc = FAPI2_RC_SUCCESS;
    do
    {
        // Set SBE state as IPLing
        (void)SbeRegAccess::theSbeRegAccess().stateTransition(
                                                SBE_PLCK_EVENT);
        // Run isteps
        for(size_t entry = 0; entry < istepTable.len; entry++)
        {
            auto istepTableEntry = &istepTable.istepMajorArr[entry];
            for(size_t step = 1; step <= istepTableEntry->len; step++)
            {
                auto istepMap = &istepTableEntry->istepMinorArr[step-1];
                if(istepMap->istepWrapper != NULL)
                {
                    rc = istepMap->istepWrapper(istepMap->istepHwp);
                }
                if(rc != FAPI2_RC_SUCCESS)
                {
                    SBE_ERROR(SBE_FUNC"Failed istep execution in plck mode: "
                            "Major: %d, Minor: %d",
                            istepTableEntry->istepMajorNum, step);
                    (void)SbeRegAccess::theSbeRegAccess().updateAsyncFFDCBit(
                                                                          true);
                    // exit outer loop as well
                    entry = istepTable.len;
                    break;
                }
                (void)SbeRegAccess::theSbeRegAccess().updateSbeStep(
                                    istepTableEntry->istepMajorNum,
                                    step);
                // Check if we reached runtime
                if(SBE_STATE_RUNTIME ==
                                SbeRegAccess::theSbeRegAccess().getSbeState())
                {
                    // Exit outer loop as well
                    entry = istepTable.len;
                    break;
                }
            }
        }
    } while(false);
    // Store l_rc in a global variable that will be a part of the SBE FFDC
    g_iplFailRc = rc;
    SBE_EXIT(SBE_FUNC);
    #undef SBE_FUNC
}
