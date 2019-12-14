#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

size_t	tpool_alive(struct s_tpool *restrict tpool)
{
	size_t	n;

	mtx_lock(&tpool->pool_mutex);
	n = tpool->threads_count;
	mtx_unlock(&tpool->pool_mutex);
	return (n);
}
