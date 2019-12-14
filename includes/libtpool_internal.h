#ifndef LIBTPOOL_INTERNAL_H
# define LIBTPOOL_INTERNAL_H

# ifndef LIBTPOOL_INTERNAL
#  error "include libtpool.h only"
# endif /* LIBTPOOL_INTERNAL */

# include <stdlib.h>
# include <pthread.h>
# include <assert.h>

# include "libtpool_s_work.h"

# ifndef S_TPOOL
#  define S_TPOOL

struct	s_tpool
{
	struct s_work *__restrict __nonnull	works;
	size_t								works_count;
	size_t								threads_count;
	size_t								pool_size;
	pthread_mutex_t						pool_mutex;
	pthread_cond_t						pool_cond;
	pthread_cond_t						work_cond;
	int									stop;
};

# endif /* S_TPOOL */

void *__nullable	internal_thread_worker(void *__restrict __nonnull arg);

#endif /* LIBTPOOL_INTERNAL_H */
