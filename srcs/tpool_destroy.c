#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

void	tpool_destroy(struct s_tpool *restrict tpool)
{
	size_t	i;

	i = ~0UL;
	mtx_lock(&tpool->pool_mutex);
	tpool->stop = true;
	cnd_broadcast(&tpool->work_cond);
	mtx_unlock(&tpool->pool_mutex);
	tpool_wait(tpool);
	mtx_destroy(&tpool->pool_mutex);
	cnd_destroy(&tpool->pool_cond);
	cnd_destroy(&tpool->work_cond);
	free(tpool->works);
	free(tpool);
}
