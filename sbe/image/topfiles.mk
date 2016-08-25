# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: sbe/image/topfiles.mk $
#
# OpenPOWER sbe Project
#
# Contributors Listed Below - COPYRIGHT 2015,2016
# [+] International Business Machines Corp.
#
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.
#
# IBM_PROLOG_END_TAG
TOP-C-SOURCES =
TOP-CPP-SOURCES =
TOP-S-SOURCES = base_ppe_header.S  pm_loader.S

# generated by ppeParseProcSbeFixed.pl
TOP-FIXED-HEADERS += $(IMAGE_SRCDIR)/proc_sbe_fixed_system.H
TOP-FIXED-HEADERS += $(IMAGE_SRCDIR)/proc_sbe_fixed_perv.H
TOP-FIXED-HEADERS += $(IMAGE_SRCDIR)/proc_sbe_fixed_proc_chip.H
TOP-FIXED-HEADERS += $(IMAGE_SRCDIR)/proc_sbe_fixed_core.H
TOP-FIXED-HEADERS += $(IMAGE_SRCDIR)/proc_sbe_fixed_ex.H
TOP-FIXED-HEADERS += $(IMAGE_SRCDIR)/proc_sbe_fixed_eq.H

TOP_OBJECTS = $(TOP-C-SOURCES:.c=.o) $(TOP-CPP-SOURCES:.C=.o) $(TOP-S-SOURCES:.S=.o)

BASE-LOADER-C-SOURCES = base_loader.c
BASE-LOADER-S-SOURCES = base_loader_setup.S

BASE_LOADER_OBJECTS = $(BASE-LOADER-C-SOURCES:.c=.o)  $(BASE-LOADER-S-SOURCES:.S=.o)

OTPROM-LOADER-S-SOURCES = pm_otprom_loader.S
OTPROM_LOADER_OBJECTS = $(OTPROM-LOADER-S-SOURCES:.S=.o)

PLAT_FAPI2_DIR_INCL = $(PLAT_FAPI2_DIR)/include
# generated by ppeParseAttributeInfo.pl
GEN-PARSEATTRIBUTEINFO += $(PLAT_FAPI2_DIR_INCL)/fapi2AttributeIds.H
GEN-PARSEATTRIBUTEINFO += $(PLAT_FAPI2_DIR_INCL)/fapi2ChipEcFeature.C
GEN-PARSEATTRIBUTEINFO += $(PLAT_FAPI2_DIR_INCL)/fapi2AttributePlatCheck.H
GEN-PARSEATTRIBUTEINFO += $(PLAT_FAPI2_DIR_INCL)/fapi2AttributesSupported.html
GEN-PARSEATTRIBUTEINFO += $(PLAT_FAPI2_DIR_INCL)/fapi2AttrInfo.csv
GEN-PARSEATTRIBUTEINFO += $(PLAT_FAPI2_DIR_INCL)/fapi2AttrEnumInfo.csv

PPE_FAPI2_DIR_SRC = $(PLAT_FAPI2_DIR)/src
# generated by ppeCreateAttrGetSetMacros.pl
GEN-CREATEATTRGETSETMACROS += fapi2PlatAttributeService.H.temp
GEN-CREATEATTRGETSETMACROS += $(PPE_FAPI2_DIR_SRC)/fapi2PlatAttributeService.C
GEN-CREATEATTRGETSETMACROS += $(PLAT_FAPI2_DIR_INCL)/fapi2PlatAttributeService.H

# generated by ppeCreateIfAttrService.pl
GEN-CREATEIFATTRSERVICE += $(PLAT_FAPI2_DIR_INCL)/fapi2AttributeService.C
