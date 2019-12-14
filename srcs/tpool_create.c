#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

#include <stdio.h>

struct s_tpool
	*tpool_create(const size_t threads_count)
{
	struct s_tpool	*tpool;
	thrd_t			thread;
	size_t			i;

	assert(threads_count);
	assert((tpool = calloc(1UL, sizeof(*tpool))));
	*tpool = (struct s_tpool) { .pool_size = threads_count,
								.threads_count = threads_count };
	assert((tpool->works = calloc(threads_count, sizeof(*tpool->works))));
	mtx_init(&tpool->pool_mutex, 0);
	cnd_init(&tpool->work_cond);
	cnd_init(&tpool->pool_cond);
	i = ~0UL;
	while (threads_count > ++i) {
		thrd_create(&thread, internal_thread_worker, tpool);
		thrd_detach(thread);
	}
	return (tpool);
}
