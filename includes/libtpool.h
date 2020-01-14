#ifndef LIBTPOOL_H
# define LIBTPOOL_H

# ifndef _GNU_SOURCE
#  define _LTPOOL_ONLY_LOCAL_GNU_SOURCE_DEFINE
#  define _GNU_SOURCE
# endif

# include <sys/types.h>

struct s_tpool;
typedef struct s_tpool TPool;

TPool*
tpool_create(const size_t threads_count);

void
tpool_add_work(TPool *restrict tpool,
	void (*work_routine)(void *restrict),
	void *restrict arg);

void
tpool_wait(TPool *restrict tpool);

void
tpool_destroy(TPool *restrict tpool);

# ifdef _LTPOOL_ONLY_LOCAL_GNU_SOURCE_DEFINE
#  undef _LTPOOL_ONLY_LOCAL_GNU_SOURCE_DEFINE
#  undef _GNU_SOURCE
# endif

#endif /* LIBTPOOL_H */
