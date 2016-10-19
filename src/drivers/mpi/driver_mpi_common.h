/* StarPU --- Runtime system for heterogeneous multicore architectures.
 *
 * Copyright (C) 2015  Mathieu Lirzin <mthl@openmailbox.org>
 * Copyright (C) 2016  Inria
 *
 * StarPU is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * StarPU is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License in COPYING.LGPL for more details.
 */

#ifndef __DRIVER_MPI_COMMON_H__
#define __DRIVER_MPI_COMMON_H__

#include <drivers/mp_common/mp_common.h>
#include <drivers/mpi/driver_mpi_source.h>

#ifdef STARPU_USE_MPI_MASTER_SLAVE

int _starpu_mpi_common_mp_init();
void _starpu_mpi_common_mp_deinit();

int _starpu_mpi_common_is_src_node();
int _starpu_mpi_common_get_src_node();

int _starpu_mpi_common_is_mp_initialized();
int _starpu_mpi_common_recv_is_ready(const struct _starpu_mp_node *mp_node);

void _starpu_mpi_common_mp_initialize_src_sink(struct _starpu_mp_node *node);

void _starpu_mpi_common_send(const struct _starpu_mp_node *node, void *msg, int len);
void _starpu_mpi_common_recv(const struct _starpu_mp_node *node, void *msg, int len);

void _starpu_mpi_common_recv_from_device(const struct _starpu_mp_node *node, int src_devid, void *msg, int len);
void _starpu_mpi_common_send_to_device(const struct _starpu_mp_node *node, int dst_devid, void *msg, int len);


#endif  /* STARPU_USE_MPI_MASTER_SLAVE */

#endif	/* __DRIVER_MPI_COMMON_H__ */
