/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/core/sbeMemAccessInterface.C $                      */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2016,2017                        */
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
#include "sbeMemAccessInterface.H"

#ifdef SEEPROM_IMAGE
// Using Function pointer to force long call
p9_adu_access_FP_t p9_adu_access_hwp = &p9_adu_access;
p9_adu_setup_FP_t p9_adu_setup_hwp = &p9_adu_setup;
#endif

using namespace fapi2;

void MEM_AVAILABLE_CHECK(uint32_t &io_available_len,uint32_t &io_len_to_send,bool &io_is_last_access)
{
    if(io_len_to_send > io_available_len)
    {
        SBE_INFO(SBE_FUNC" Allocated memory is less, truncating the access");
        io_len_to_send = io_available_len;
        io_is_last_access = true;
    }
    io_available_len -= io_len_to_send;
}

ReturnCode sbeMemAccessInterface::setup()
{
#define SBE_FUNC "sbeMemAccessInterface::setup"
    SBE_ENTER(SBE_FUNC);
    ReturnCode fapiRc = FAPI2_RC_SUCCESS;

    // Reset the current granule count
    iv_currGranule = 0;
    iv_intfCleanedUp = false;
    SBE_INFO("iv_addr [0x%08x%08x]", SBE::higher32BWord(iv_addr), SBE::lower32BWord(iv_addr));
    if(iv_interface == SBE_MEM_ACCESS_PBA)
    {
        // Call the PBA setup HWP
        SBE_EXEC_HWP(fapiRc,
                     p9_pba_setup,
                     plat_getChipTarget(),
                     iv_ex,
                     iv_addr,
                     (iv_mode == SBE_MEM_ACCESS_READ),
                     ((p9_PBA_oper_flag*)iv_flags)->setFlag(),
                     iv_maxGranule);
    }
    if(iv_interface == SBE_MEM_ACCESS_ADU)
    {
        // Call the ADU setup HWP
        SBE_EXEC_HWP(fapiRc,
                     p9_adu_setup_hwp,
                     plat_getChipTarget(),
                     iv_addr,
                     (iv_mode == SBE_MEM_ACCESS_READ),
                     ((p9_ADU_oper_flag*)iv_flags)->setFlag(),
                     iv_maxGranule)
    }
    // if setup returns error
    if(fapiRc != FAPI2_RC_SUCCESS)
    {
        SBE_ERROR(SBE_FUNC" setup Failed");
    }
    else
    {
        // Assumption is Hwp won't return zero for Num Granules
        assert(0 != iv_maxGranule);

        SBE_INFO(SBE_FUNC "Hwp returned iv_maxGranule=[0x%08X]",
                                             iv_maxGranule);
    }
    return fapiRc;
#undef SBE_FUNC
}

ReturnCode sbeMemAccessInterface::accessGranule(const bool i_isLastAccess)
{
#define SBE_FUNC "sbeMemAccessInterface::accessGranule"
    SBE_DEBUG(SBE_FUNC);
    ReturnCode fapiRc = FAPI2_RC_SUCCESS;

    do
    {
        // Check if we need to do a setup before access
        if(iv_intfCleanedUp)
        {
            fapiRc = setup();
            // if setup returns error
            if( fapiRc != FAPI2_RC_SUCCESS )
            {
                break;
            }
        }
        iv_intfCleanedUp = (i_isLastAccess || (iv_maxGranule == 1));
        if(iv_interface == SBE_MEM_ACCESS_PBA)
        {
            // Call PBA access for read/write
            SBE_EXEC_HWP(fapiRc,
                         p9_pba_access,
                         plat_getChipTarget(),
                         iv_addr,
                         (iv_mode == SBE_MEM_ACCESS_READ),
                         ((p9_PBA_oper_flag*)iv_flags)->setFlag(),
                         (iv_currGranule == 0),
                         iv_intfCleanedUp,
                         (uint8_t *)&iv_buffer);
        }
        if(iv_interface == SBE_MEM_ACCESS_ADU)
        {
            // Call ADU access HWP for ADU write/read request
            SBE_EXEC_HWP(fapiRc,
                     p9_adu_access_hwp,
                     plat_getChipTarget(),
                     iv_addr,
                     (iv_mode == SBE_MEM_ACCESS_READ),
                     ((p9_ADU_oper_flag*)iv_flags)->setFlag(),
                     (iv_currGranule == 0),
                     iv_intfCleanedUp,
                     (uint8_t *)&iv_buffer)
        }
        if(fapiRc != FAPI2_RC_SUCCESS)
        {
            SBE_ERROR(SBE_FUNC" access HWP failed");
            break;
        }
        iv_maxGranule--;
        iv_currGranule++;
        // Advance the address
        iv_addr += iv_granuleSize;
        iv_iterator = (iv_mode == SBE_MEM_ACCESS_READ)?
                        iv_granuleSize : 0;
    } while(false);

    return fapiRc;
#undef SBE_FUNC
}

ReturnCode sbeMemAccessInterface::accessWithBuffer(const void *io_buffer,
                                                   const uint32_t i_len,
                                                   const bool i_isLastAccess)
{
#define SBE_FUNC "sbeMemAccessInterface::accessWithBuffer"
    SBE_DEBUG(SBE_FUNC" len[%d]",i_len);
    ReturnCode fapiRc = FAPI2_RC_SUCCESS;
    uint32_t iterator = 0;
    bool is_lastGranule = false;

    do
    {
        if(iv_mode == SBE_MEM_ACCESS_WRITE)
        {
            // Fill buffer
            while((iv_iterator < iv_granuleSize) && (iterator < i_len))
            {
                iv_buffer[iv_iterator++] = ((char*)io_buffer)[iterator++];
            }
            // If Adu, put the ecc and itag applicable bytes
            if(iv_interface == SBE_MEM_ACCESS_ADU)
            {
                if(((p9_ADU_oper_flag*)iv_flags)->getEccMode())
                {
                    iv_buffer[iv_iterator++] = ((char*)io_buffer)[iterator++];
                }
                if(((p9_ADU_oper_flag*)iv_flags)->getItagMode())
                {
                    iv_buffer[iv_iterator++] = ((char*)io_buffer)[iterator++];
                }
            }
        }

        if(i_isLastAccess)
        {
            if((iv_mode == SBE_MEM_ACCESS_WRITE) &&
                        (iterator >= i_len))
            {
                is_lastGranule = true;
                alignAccessWithBuffer();
            }
            else if((iv_mode == SBE_MEM_ACCESS_READ) &&
                        ((i_len - iterator) <= iv_granuleSize))
            {
                is_lastGranule = true;
                iv_iterator = 0;
            }
        }
        if(((iv_mode == SBE_MEM_ACCESS_WRITE) &&
            (iv_iterator >= iv_granuleSize))
           ||
           ((iv_mode == SBE_MEM_ACCESS_READ) &&
            (iv_iterator == 0)))
        {
            fapiRc = accessGranule(is_lastGranule);
            // Break out on error
            if(fapiRc != FAPI2_RC_SUCCESS)
            {
                break;
            }
        }

        if(iv_mode == SBE_MEM_ACCESS_READ)
        {
            // Fill the buffer
            while((iv_iterator > 0) && (iterator < i_len))
            {
                ((char*)io_buffer)[iterator++] =
                        iv_buffer[iv_granuleSize - iv_iterator];
                iv_iterator--;
            }
            // If Adu, get the ecc and itag applicable bytes
            if(iv_interface == SBE_MEM_ACCESS_ADU)
            {
                uint32_t index = iv_granuleSize;
                if(((p9_ADU_oper_flag*)iv_flags)->getEccMode())
                {
                    ((char*)io_buffer)[iterator++] =
                                            iv_buffer[index++];
                }
                if(((p9_ADU_oper_flag*)iv_flags)->getItagMode())
                {
                    ((char*)io_buffer)[iterator++] =
                                            iv_buffer[index];
                }
            }
        }

        // data is completely processed
        if(iterator >= i_len)
        {
            break;
        }
    } while(true);

    return fapiRc;
#undef SBE_FUNC
}

void sbeMemAccessInterface::alignAccessWithBuffer()
{
#define SBE_FUNC "sbeMemAccessInterface::alignAccessWithBuffer"
    SBE_DEBUG(SBE_FUNC);
    // Required to fill zeroes only if the iv_buffer is partially occupied
    if(iv_iterator != 0)
    {
        // zero filling
        while(iv_iterator < iv_granuleSize)
        {
            iv_buffer[iv_iterator++] = 0;
        }
    }
#undef SBE_FUNC
}
