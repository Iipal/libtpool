#include "tpool.h"

static struct s_tpool_work __attribute__((__nonnull__(1)))
	*in_tpool_work_create(void (*work_routine)(void*),
						void *restrict arg)
{
	struct s_tpool_work	*restrict	work;

	assert((work = (__typeof__(work))(valloc(sizeof(*work)))));
	*work = (struct s_tpool_work){ .func = work_routine, .arg = arg };
	return ((struct s_tpool_work*)work);
}

_Bool __attribute__((__nonnull__(1,2)))
	tpool_add_work(struct s_tpool *restrict tpool,
					void (*work_routine)(void*),
					void *arg)
{
	struct s_tpool_work	*restrict	work;

	if (!(work = in_tpool_work_create(work_routine, arg)))
		return (false);
	pthread_mutex_lock(&(tpool->work_mutex));
	if (!(tpool->work_first)) {
		tpool->work_first = work;
		tpool->work_last = tpool->work_first;
	} else {
		tpool->work_last->next = work;
		tpool->work_last = work;
	}
	pthread_cond_broadcast(&(tpool->work_cond));
	pthread_mutex_unlock(&(tpool->work_mutex));
	return (true);
}
