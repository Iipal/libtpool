#ifndef LIBTPOOL_H
# define LIBTPOOL_H

# ifndef _GNU_SOURCE
#  define ONLY_LOCAL_GNU_SOURCE_DEFINE
#  define _GNU_SOURCE
# endif

# include "libtpool_defs.h"

# include <sys/types.h>

struct s_tpool;
typedef struct s_tpool t_tpool;

t_tpool *tp_Nonnull
tpool_create(const size_t threads_count);

void
tpool_add_work(t_tpool *tp_restrict tp_Nonnull tpool,
	void (*tp_Nonnull work_routine)(void *tp_restrict tp_Nonnull),
	void *tp_restrict tp_Nonnull arg);

void
tpool_wait(t_tpool *tp_restrict tp_Nonnull tpool);

void
tpool_destroy(t_tpool *tp_restrict tp_Nonnull tpool);

# ifdef ONLY_LOCAL_GNU_SOURCE_DEFINE
#  undef ONLY_LOCAL_GNU_SOURCE_DEFINE
#  undef _GNU_SOURCE
# endif

#endif /* LIBTPOOL_H */
