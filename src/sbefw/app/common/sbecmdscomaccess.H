/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/sbefw/app/common/sbecmdscomaccess.H $                     */
/*                                                                        */
/* OpenPOWER sbe Project                                                  */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2018                        */
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
 * @file: ppe/sbe/sbefw/sbecmdscomaccess.H
 *
 * @brief This file contains the Interfaces for the SCOM Access chip-ops
 *
 */

#ifndef __SBEFW_SBECMDSCOMACCESS_H
#define __SBEFW_SBECMDSCOMACCESS_H

#include <stdint.h>

namespace SBE_COMMON
{

/**
  * @brief sbeDownFifoGetStatus : Write data into Downstream FIFO
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbeGetScom (uint8_t *i_pArg);


/**
  * @brief sbeDownFifoGetStatus : Write data into Downstream FIFO
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbePutScom (uint8_t *i_pArg);


/**
  * @brief sbeModifyScom : Modify the Scom data
  *     This chipOp needs to do the following
  *        1. Read Register Data (getscom)
  *        2. modify the scomData using the given op mode
  *        3. Write the modified Data into the Register (putscom)
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbeModifyScom (uint8_t *i_pArg);


/**
  * @brief sbePutScomUnderMask : Write data into Downstream FIFO
  *    The following steps need to be done as part of this command :
  *        1. Read Register Data (getscom)
  *        2. 'AND' the Mask with the data read from register
  *        3. 'OR' the modifying data with the result of step 2
  *        4. Write the result of step 3 into the register (putscom)
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbePutScomUnderMask (uint8_t *i_pArg);

/**
  * @brief sbeMultiScom:
  *
  * @param[in] i_pArg Buffer to be passed to the function (not used as of now)
  *
  * @return    Rc from the FIFO access utility
  */
uint32_t sbeMultiScom (uint8_t *i_pArg);
} // namespace SBE_COMMON

#endif /* __SBEFW_SBECMDSCOMACCESS_H */
