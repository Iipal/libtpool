#include "tpool.h"

static struct s_tpool_work __attribute__((__nonnull__(1)))
	*tpool_work_create(void (*func)(void*),
						void *restrict arg)
{
	struct s_tpool_work	*restrict	work;

	assert((work = (__typeof__(work))(valloc(sizeof(*work)))));
	*work = (struct s_tpool_work){
		.func = func,
		.arg = arg };
	return ((struct s_tpool_work*)work);
}

_Bool __attribute__((__nonnull__(1,2)))
	tpool_add_work(struct s_tpool *restrict tm,
					void (*func)(void*),
					void *arg)
{
	struct s_tpool_work	*restrict	work;

	if (!(work = tpool_work_create(func, arg)))
		return (false);
	pthread_mutex_lock(&(tm->work_mutex));
	if (!(tm->work_first))
	{
		tm->work_first = work;
		tm->work_last = tm->work_first;
	}
	else
	{
		tm->work_last->next = work;
		tm->work_last = work;
	}
	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	return (true);
}
