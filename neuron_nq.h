// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2021, Amazon.com, Inc. or its affiliates. All Rights Reserved
 */

#ifndef NEURON_NQ_H
#define NEURON_NQ_H

#include <linux/kernel.h>
#include <linux/types.h>
#include "neuron_device.h"

#define NOTIFIC_NQ_SIZE 0x28   // total size of the NQ register space
#define NOTIFIC_NQ_BASE_ADDR_LO_OFFSET_START 0x100
#define NOTIFIC_NQ_BASE_ADDR_LO_OFFSET(index) (NOTIFIC_NQ_BASE_ADDR_LO_OFFSET_START + ((index)*NOTIFIC_NQ_SIZE) + 0)

#define NOTIFIC_NQ_BASE_ADDR_LO_RESET_VALUE 0x00000000

static inline void notific_write_nq_base_addr_lo(void __iomem *base, size_t index,
								  uint32_t value)
{
	const size_t offset = NOTIFIC_NQ_BASE_ADDR_LO_OFFSET(index);

	reg_write32(base + offset, value);
}

#define NOTIFIC_NQ_BASE_ADDR_HI_OFFSET_START 0x104
#define NOTIFIC_NQ_BASE_ADDR_HI_OFFSET(index) (NOTIFIC_NQ_BASE_ADDR_HI_OFFSET_START + ((index)*NOTIFIC_NQ_SIZE) + 0)

#define NOTIFIC_NQ_BASE_ADDR_HI_RESET_VALUE 0x00000000

static inline void notific_write_nq_base_addr_hi(void __iomem *base, size_t index,
								  uint32_t value)
{
	const size_t offset = NOTIFIC_NQ_BASE_ADDR_HI_OFFSET(index);

	reg_write32(base + offset, value);
}

#define NOTIFIC_NQ_F_SIZE_OFFSET_START 0x108
#define NOTIFIC_NQ_F_SIZE_OFFSET(index) (NOTIFIC_NQ_F_SIZE_OFFSET_START + ((index)*NOTIFIC_NQ_SIZE) + 0)

#define NOTIFIC_F_SIZE_RESET_VALUE 0x00000000

static inline void notific_write_nq_f_size(void __iomem *base, size_t index,
							    uint32_t value)
{
	const size_t offset = NOTIFIC_NQ_F_SIZE_OFFSET(index);

	reg_write32(base + offset, value);
}

#define NOTIFIC_NQ_HEAD_OFFSET 0x10c

/**
 * nnq_init_storage() - Allocate the per-NC and per-TS notification queue
 *                      tracking arrays
 *
 * @nd: neuron device
 *
 */
int nnq_init_storage(struct neuron_device *nd);

/**
 * nnq_destroy_storage() - Free the per-NC and per-TS notification queue
 *                         tracking arrays
 *
 * @nd: neuron device
 */
void nnq_destroy_storage(struct neuron_device *nd);

/**
 * nnq_init() - Initialize notification queue for NeuronCore
 *
 * @nd: neuron device
 * @nc_id: core index in the device
 * @eng_index: notification engine index in the core
 * @nq_type: type of the notification queue
 * @size: size of queue in bytes
 * @on_host_memory: if true, NQ is created in host memory
 * @hbm_index: If NQ is created on device memory which DRAM channel to use.
 * @force_alloc_mem: If true, force allocate new memory (and delete already allocated memory, if any)
 * @nq_mc[out]: memchunk used by the NQ will be written here
 * @mc_ptr[out]: Pointer to memchunk backing this NQ
 *
 * Return: 0 on if initialization succeeds, a negative error code otherwise.
 */
int nnq_init(struct neuron_device *nd, u8 nc_id, u8 eng_index, u32 nq_type, u32 size,
	       u32 on_host_memory, u32 hbm_index,
	       bool force_alloc_mem, struct mem_chunk **nq_mc, u64 *mmap_offset);

/**
 * nnq_destroy_nc() - Disable notification in the device
 *
 * @nd: neuron device
 * @nc_id: neuron core
 *
 */
void nnq_destroy_nc(struct neuron_device *nd, u8 nc_id);

/**
 * nnq_destroy_all() - Disable notification in the device
 *
 * @nd: neuron device
 *
 */
void nnq_destroy_all(struct neuron_device *nd);

#endif
