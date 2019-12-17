#ifndef LIBTPOOL_INTERNAL_H
#define LIBTPOOL_INTERNAL_H

#ifndef LIBTPOOL_INTERNAL
#error "include libtpool.h only"
#endif /* LIBTPOOL_INTERNAL */

#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdalign.h>
#include <assert.h>

#include "libtpool_defs.h"

# ifndef S_TPOOL_WORK
#  define S_TPOOL_WORK

struct	s_tpool_work
{
	void	(*tp_Nullable routine)(void *tp_restrict tp_Nonnull);
	void	*tp_restrict tp_Nullable arg;
};

# endif /* S_TPOOL_WORK */

# ifndef S_TPOOL
#  define S_TPOOL

# if defined __APPLE__
#  define TPOOL_ALIGN_SIZE 8
# elif defined __linux__
#  define TPOOL_ALIGN_SIZE 4
# else
#  define TPOOL_ALIGN_SIZE 1
# endif

struct s_tpool
{
	struct s_tpool_work *tp_restrict tp_Nullable works;
	size_t works_count;
	size_t threads_count;
	size_t pool_size;
	pthread_mutex_t pool_mutex;
	pthread_cond_t pool_cond;
	pthread_cond_t work_cond;
	int stop;
	char dummy[TPOOL_ALIGN_SIZE] __attribute__((__unused__));
} __attribute__((__aligned__(__BIGGEST_ALIGNMENT__)));

# undef TPOOL_ALIGN_SIZE

# endif /* S_TPOOL */

void *tp_Nullable
internal_thread_worker(void *tp_restrict tp_Nonnull arg);

#endif /* LIBTPOOL_INTERNAL_H */
