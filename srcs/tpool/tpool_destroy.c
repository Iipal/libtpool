#include "tpool.h"

void __attribute__((__nonnull__(1)))
	tpool_destroy(struct s_tpool *restrict tpool)
{
	struct s_tpool_work *restrict	work;
	struct s_tpool_work *restrict	work2;

	pthread_mutex_lock(&(tpool->work_mutex));
	work = tpool->work_first;
	while (!!work)
	{
		work2 = work->next;
		free(work);
		work = work2;
	}
	tpool->stop = true;
	pthread_cond_broadcast(&(tpool->work_cond));
	pthread_mutex_unlock(&(tpool->work_mutex));
	tpool_wait(tpool);
	pthread_mutex_destroy(&(tpool->work_mutex));
	pthread_cond_destroy(&(tpool->work_cond));
	pthread_cond_destroy(&(tpool->working_cond));
	free((void*)tpool);
}
