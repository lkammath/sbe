# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/build/import_hwp_mk/power/istep2/Makefile $
#
# OpenPOWER sbe Project
#
# Contributors Listed Below - COPYRIGHT 2016,2018
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
# This Makefile compiles all of the hardware procedure code. See the
# "*.mk" file in this directory.

#all generated files from this makefile will end up in obj/*
export SUB_OBJDIR = /$(IMPORT_OBJDIR)/istep2

include img_defs.mk
include istep2files.mk

export VPATH = $(PERV_SRCDIR):$(NEST_SRCDIR):$(CACHE_SRCDIR):$(CORE_SRCDIR):$(PM_SRCDIR):$(INITFILES_SRCDIR):$(LIB_SRCDIR)

OBJSISTEP2 := $(addprefix $(OBJDIR-ISTEP2)/, $(ISTEP2_OBJECTS))

.PHONY: clean istep2

libistep2.a: istep2
	$(AR) crs $(OBJDIR-ISTEP2)/libistep2.a $(OBJDIR-ISTEP2)/*.o

istep2: $(OBJSISTEP2)
$(OBJSISTEP2) $(OBJSISTEP2:.o=.d): | $(OBJDIR-ISTEP2)

$(OBJDIR-ISTEP2):
	mkdir -p $(OBJDIR-ISTEP2)

clean:
	rm -fr $(OBJDIR-ISTEP2)

ifneq ($(MAKECMDGOALS),clean)
include $(OBJSISTEP2:.o=.d)
endif
