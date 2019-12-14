#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

#include <stdio.h>

static struct s_current_work __attribute_pure__
	*s_get_work(const struct s_tpool *restrict tpool)
{
	struct s_current_work	*out;
	size_t					i;

	out = NULL;
	i = tpool->works_count - 1UL;
	if (tpool->works[i].routine && !(tpool->busy_works_mask & (1L << i))) {
		out = valloc(sizeof(*out));
		*out = (struct s_current_work) { tpool->works[i], 1L << i };
	}
	return (out);
}

int
	internal_thread_worker(void *restrict arg)
{
	struct s_tpool *restrict		tpool = (struct s_tpool *restrict)arg;
	struct s_current_work			*c_work;

	while (1) {
		mtx_lock(&tpool->pool_mutex);
		if (tpool->stop)
		 	break ;
		if (!tpool->works_count)
			cnd_wait(&tpool->work_cond, &tpool->pool_mutex);
		if ((c_work = s_get_work(tpool)))
			tpool->busy_works_mask |= c_work->work_mask_index;
		mtx_unlock(&tpool->pool_mutex);
		if (c_work) {
			c_work->work.routine(c_work->work.arg);
			free(c_work);
			c_work = NULL;
		}
		mtx_lock(&tpool->pool_mutex);
		if (tpool->works_count)
			--tpool->works_count;
		if (!tpool->stop && !tpool->works_count)
			cnd_signal(&tpool->pool_cond);
		mtx_unlock(&tpool->pool_mutex);
	}
	tpool->threads_count--;
	cnd_signal(&tpool->pool_cond);
	mtx_unlock(&tpool->pool_mutex);
	return (0);
}
