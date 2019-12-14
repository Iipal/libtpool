#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

bool	tpool_add_work(struct s_tpool *restrict tpool,
			void (*work_routine)(void *restrict),
			void *arg)
{
	pthread_mutex_lock(&tpool->pool_mutex);
	if (tpool->pool_size <= tpool->works_count) {
		pthread_mutex_unlock(&tpool->pool_mutex);
		return (false);
	}
	tpool->works[tpool->works_count++] = (struct s_work) {
		.routine = work_routine, .arg = arg
	};
	pthread_cond_broadcast(&tpool->work_cond);
	pthread_mutex_unlock(&tpool->pool_mutex);
	return (true);
}
