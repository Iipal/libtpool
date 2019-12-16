#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

void	tpool_add_work(struct s_tpool *tp_restrict tp_Nonnull tpool,
			void (*tp_Nonnull work_routine)(void *tp_restrict tp_Nonnull),
			void *tp_restrict tp_Nonnull arg)
{
	size_t i;

	pthread_mutex_lock(&tpool->pool_mutex);
	for (i = 0UL; tpool->pool_size > i && !!tpool->works[i].routine; i++)
		;
	if (tpool->pool_size > i)
		tpool->works[i] = (struct s_tpool_work) { work_routine, arg };
	pthread_cond_broadcast(&tpool->work_cond);
	pthread_mutex_unlock(&tpool->pool_mutex);
}
