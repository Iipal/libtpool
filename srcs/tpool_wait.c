#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

void	tpool_wait(struct s_tpool *restrict tpool)
{
	mtx_lock(&tpool->pool_mutex);
	while (1) {
		if ((!tpool->stop && tpool->busy_works_mask)
		|| (tpool->stop && tpool->threads_count))
			cnd_wait(&tpool->pool_cond, &tpool->pool_mutex);
		else
			break ;
	}
	mtx_unlock(&tpool->pool_mutex);
}
