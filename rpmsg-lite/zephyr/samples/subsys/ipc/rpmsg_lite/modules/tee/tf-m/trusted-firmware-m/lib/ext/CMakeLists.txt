#-------------------------------------------------------------------------------
# Copyright (c) 2020-2022, Arm Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/lib/ext CACHE STRING "" FORCE)

if(TFM_PARTITION_INITIAL_ATTESTATION)
  add_subdirectory(qcbor)
  add_subdirectory(t_cose)
endif()
add_subdirectory(mbedcrypto)
add_subdirectory(CMSIS_5)
if(BL2)
    add_subdirectory(mcuboot)
endif()
if(TEST_PSA_API)
    add_subdirectory(psa_arch_tests)
endif()
if (${PLATFORM_PSA_ADAC_SECURE_DEBUG})
    add_subdirectory(psa-adac)
endif()

add_subdirectory(tf-m-extras)
