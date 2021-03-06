/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/core/sbeerrorcodes.H $                              */
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
/*
 * @file: ppe/sbe/sbefw/sbeerrorcodes.H
 *
 * @brief This file contains the SBE internal error status codes
 *
 */

#ifndef __SBEFW_SBEERRORCODES_H
#define __SBEFW_SBEERRORCODES_H

#include <stdint.h>


/**
 * @brief enums SBE internal error codes
 *
*/
enum sbeInternalResponseCodes
{
    SBE_FIFO_RESET_RECEIVED  = 0xFA00,
    SBE_FIFO_RESET_HANDLING_FAILED = 0xFB00,
    SBE_FUNC_NOT_SUPPORTED   = 0xFC00,
};


#endif // __SBEFW_SBEERRORCODES_H