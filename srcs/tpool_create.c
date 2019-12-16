#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

void *tp_Nullable
internal_thread_worker(void *tp_restrict tp_Nonnull arg);

struct s_tpool *tp_Nonnull
tpool_create(const size_t threads_count)
{
	struct s_tpool *tp_restrict tpool;

	assert(threads_count != 0UL);
	assert((tpool = calloc(1UL, sizeof(*tpool))));
	*tpool = (struct s_tpool) { .pool_size = threads_count,
								.threads_count = threads_count };
	assert((tpool->works = calloc(threads_count, sizeof(*tpool->works))));
	pthread_mutex_init(&tpool->pool_mutex, NULL);
	pthread_cond_init(&tpool->work_cond, NULL);
	pthread_cond_init(&tpool->pool_cond, NULL);
	for (size_t i = 0UL; threads_count > i; i++) {
		pthread_t thread;
		pthread_create(&thread, NULL, internal_thread_worker, tpool);
		pthread_detach(thread);
	}
	return (tpool);
}

static struct s_tpool_work
internal_get_work(struct s_tpool *tp_restrict tpool)
{
	struct s_tpool_work out = { NULL, NULL };
	size_t i;

	for (i = 0UL; tpool->pool_size > i && !tpool->works[i].routine; i++)
		;
	if (tpool->pool_size > i) {
		out = tpool->works[i];
		tpool->works[i] = (struct s_tpool_work) { NULL, NULL };
	}
	return (out);
}

void *tp_Nullable
internal_thread_worker(void *tp_restrict tp_Nonnull arg)
{
	struct s_tpool *tp_restrict tpool = (struct s_tpool *tp_restrict)arg;
	struct s_tpool_work work;

	while (1) {
		pthread_mutex_lock(&tpool->pool_mutex);
		if (tpool->stop)
		 	break ;
		if (!tpool->works_count)
			pthread_cond_wait(&tpool->work_cond, &tpool->pool_mutex);
		work = internal_get_work(tpool);
		++tpool->works_count;
		pthread_mutex_unlock(&tpool->pool_mutex);
		if (work.routine && work.arg)
			work.routine(work.arg);
		pthread_mutex_lock(&tpool->pool_mutex);
		--tpool->works_count;
		work = (struct s_tpool_work) { NULL, NULL };
		if (!tpool->stop && !tpool->works_count)
			pthread_cond_signal(&tpool->pool_cond);
		pthread_mutex_unlock(&tpool->pool_mutex);
	}
	tpool->threads_count--;
	pthread_cond_signal(&tpool->pool_cond);
	pthread_mutex_unlock(&tpool->pool_mutex);
	return (NULL);
}
