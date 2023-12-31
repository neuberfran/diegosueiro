/*
 * Copyright (c) 2018-2021 mcumgr authors
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef H_STAT_MGMT_
#define H_STAT_MGMT_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Command IDs for statistics management group.
 */
#define STAT_MGMT_ID_SHOW   0
#define STAT_MGMT_ID_LIST   1

/**
 * Command result codes for statistics management group.
 */
enum stat_mgmt_ret_code_t {
	/** No error, this is implied if there is no ret value in the response */
	STAT_MGMT_RET_RC_OK = 0,

	STAT_MGMT_RET_RC_INVALID_GROUP,
	STAT_MGMT_RET_RC_INVALID_STAT_NAME,
	STAT_MGMT_RET_RC_INVALID_STAT_SIZE,
	STAT_MGMT_RET_RC_WALK_ABORTED,
};

/**
 * @brief Represents a single value in a statistics group.
 */
struct stat_mgmt_entry {
	const char *name;
	uint64_t value;
};

#ifdef CONFIG_MCUMGR_SMP_SUPPORT_ORIGINAL_PROTOCOL
/*
 * @brief	Translate stat mgmt group error code into MCUmgr error code
 *
 * @param ret	#stat_mgmt_ret_code_t error code
 *
 * @return	#mcumgr_err_t error code
 */
int stat_mgmt_translate_error_code(uint16_t ret);
#endif

#ifdef __cplusplus
}
#endif

#endif /* H_STAT_MGMT_ */
