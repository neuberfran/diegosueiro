#-------------------------------------------------------------------------------
# Copyright (c) 2021, Arm Limited. All rights reserved.
# Copyright (c) 2022 Cypress Semiconductor Corporation (an Infineon company)
# or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

fetch_remote_library(
    LIB_NAME                libmetal
    LIB_SOURCE_PATH_VAR     LIBMETAL_SRC_PATH
    LIB_BINARY_PATH_VAR     LIBMETAL_BIN_PATH
    LIB_PATCH_DIR           ${CMAKE_CURRENT_LIST_DIR}
    LIB_FORCE_PATCH         LIBMETAL_FORCE_PATCH
    FETCH_CONTENT_ARGS
        GIT_REPOSITORY      https://github.com/OpenAMP/libmetal.git
        GIT_TAG             ${LIBMETAL_VERSION}
)
