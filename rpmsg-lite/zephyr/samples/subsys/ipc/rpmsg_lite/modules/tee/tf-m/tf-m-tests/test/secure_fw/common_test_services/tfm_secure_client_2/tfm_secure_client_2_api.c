/*
 * Copyright (c) 2019-2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "tfm_secure_client_2_api.h"
#include "psa/client.h"

#include "psa_manifest/sid.h"

__attribute__((section("SFN")))
psa_status_t tfm_secure_client_2_call_test(int32_t id, const void *arg,
                                           size_t arg_len)
{
    psa_handle_t handle;
    psa_status_t status;
    psa_invec in_vec[] = {
        { .base = arg, .len = arg_len },
    };

    handle = psa_connect(TFM_SECURE_CLIENT_2_SID, TFM_SECURE_CLIENT_2_VERSION);
    if (!PSA_HANDLE_IS_VALID(handle)) {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Pass the ID through the type parameter of psa_call() */
    status = psa_call(handle, id, in_vec, 1, NULL, 0);
    psa_close(handle);

    return status;
}
