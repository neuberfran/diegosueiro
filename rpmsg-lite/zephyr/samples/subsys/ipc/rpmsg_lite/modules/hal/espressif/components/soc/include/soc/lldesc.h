// Copyright 2010-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "sdkconfig.h"

#if CONFIG_IDF_TARGET_ESP32
#include "esp32/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32S2
#include "esp32s2/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32S3
#include "esp32s3/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32C3
#include "esp32c3/rom/lldesc.h"
#elif CONFIG_IDF_TARGET_ESP32H2
#include "esp32h2/rom/lldesc.h"
#endif

//the size field has 12 bits, but 0 not for 4096.
//to avoid possible problem when the size is not word-aligned, we only use 4096-4 per desc.
/** Maximum size of data in the buffer that a DMA descriptor can hold. */
#define LLDESC_MAX_NUM_PER_DESC (4096-4)

// Some DMA operations might impose certain alignment restrictions on the length
#define LLDESC_MAX_NUM_PER_DESC_16B_ALIGNED (4096 - 16)
#define LLDESC_MAX_NUM_PER_DESC_32B_ALIGNED (4096 - 32)

/**
 * Generate a linked list pointing to a (huge) buffer in an descriptor array.
 *
 * The caller should ensure there is enough size to hold the array, by calling
 * ``lldesc_get_required_num_constrained`` with the same max_desc_size argument.
 *
 * @param[out] out_desc_array Output of a descriptor array, the head should be fed to the DMA.
 * @param buffer Buffer for the descriptors to point to.
 * @param size Size (or length for TX) of the buffer
 * @param max_desc_size Maximum length of each descriptor
 * @param isrx The RX DMA may require the buffer to be word-aligned, set to true for a RX link, otherwise false.
 */
void lldesc_setup_link_constrained(lldesc_t *out_desc_array, const void *buffer, int size, int max_desc_size, bool isrx);

/**
 * Generate a linked list pointing to a (huge) buffer in an descriptor array.
 *
 * The caller should ensure there is enough size to hold the array, by calling
 * ``lldesc_get_required_num``.
 *
 * @param[out] out_desc_array Output of a descriptor array, the head should be fed to the DMA.
 * @param buffer Buffer for the descriptors to point to.
 * @param size Size (or length for TX) of the buffer
 * @param isrx The RX DMA may require the buffer to be word-aligned, set to true for a RX link, otherwise false.
 */
#define lldesc_setup_link(out_desc_array, buffer, size, isrx) lldesc_setup_link_constrained(out_desc_array, buffer, size, LLDESC_MAX_NUM_PER_DESC, isrx)

/**
 * @brief Get the received length of a linked list, until end of the link or eof.
 *
 * @param head      The head of the linked list.
 * @param[out] out_next Output of the next descriptor of the EOF descriptor. Return NULL if there's no
 *                 EOF. Can be set to NULL if next descriptor is not needed.
 * @return The accumulation of the `len` field of all descriptors until EOF or the end of the link.
 */
int lldesc_get_received_len(lldesc_t* head, lldesc_t** out_next);

/**
 * Get the number of descriptors required for a given buffer size.
 *
 * @param data_size Size to check descriptor num.
 *
 * @return Numbers required.
 */
static inline int lldesc_get_required_num_constrained(int data_size, int max_desc_size)
{
    return (data_size + max_desc_size - 1) / max_desc_size;
}

/**
 * Get the number of descriptors required for a given buffer size.
 *
 * @param data_size Size to check descriptor num.
 * @param max_desc_size Maximum length of each descriptor
 * @return Numbers required.
 */
#define lldesc_get_required_num(data_size) lldesc_get_required_num_constrained(data_size, LLDESC_MAX_NUM_PER_DESC)
