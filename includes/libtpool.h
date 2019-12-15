#ifndef LIBTPOOL_H
# define LIBTPOOL_H

# ifndef _GNU_SOURCE
#  define ONLY_LOCAL_GNU_SOURCE_DEFINE
#  define _GNU_SOURCE
# endif

# include "libtpool_s_work.h"
# include "libtpool_defs.h"

# include <sys/types.h>
# include <stdbool.h>

struct s_tpool;

struct s_tpool *tp_Nonnull
tpool_create(const size_t threads_count);

bool
# if __has_attribute(overloadable)
__attribute__((overloadable)) tpool_add_work
# else
tpool_add_work
# endif
(struct s_tpool *tp_restrict tp_Nonnull tpool,
	void (*tp_Nonnull work_routine)(void *tp_restrict tp_Nonnull),
	void *tp_restrict tp_Nonnull arg);

bool
# if __has_attribute(overloadable)
__attribute__((overloadable)) tpool_add_work
# else
tpool_add_w_work
# endif
(struct s_tpool *tp_restrict tp_Nonnull tpool,
struct s_work *tp_restrict tp_Nonnull work);

void
tpool_wait(struct s_tpool *tp_restrict tp_Nonnull tpool);

void
tpool_destroy(struct s_tpool *tp_restrict tp_Nonnull tpool);

# ifdef ONLY_LOCAL_GNU_SOURCE_DEFINE
#  undef ONLY_LOCAL_GNU_SOURCE_DEFINE
#  undef _GNU_SOURCE
# endif

#endif /* LIBTPOOL_H */
