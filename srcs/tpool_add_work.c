#include "libtpool.h"

#define LIBTPOOL_INTERNAL
# include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

bool
# if __has_attribute(overloadable)
__attribute__((overloadable)) tpool_add_work
# else
tpool_add_work
# endif
(struct s_tpool *tp_restrict tp_Nonnull tpool,
	void (*work_routine)(void *tp_restrict tp_Nonnull),
	void *tp_restrict tp_Nonnull arg)
{
	size_t	i;

	pthread_mutex_lock(&tpool->pool_mutex);
	i = ~0UL;
	while (tpool->pool_size > ++i)
		if (!tpool->works[i].routine) {
			tpool->works[i] = (struct s_work) { work_routine, arg };
			break ;
		}
	pthread_cond_broadcast(&tpool->work_cond);
	pthread_mutex_unlock(&tpool->pool_mutex);
	return (true);
}

bool
# if __has_attribute(overloadable)
__attribute__((overloadable)) tpool_add_work
# else
tpool_add_w_work
# endif
(struct s_tpool *tp_restrict tp_Nonnull tpool,
struct s_work *tp_restrict tp_Nonnull work)
{
	size_t	i;

	pthread_mutex_lock(&tpool->pool_mutex);
	i = ~0UL;
	while (tpool->pool_size > ++i)
		if (!tpool->works[i].routine) {
			tpool->works[i] = *work;
			break ;
		}
	pthread_cond_broadcast(&tpool->work_cond);
	pthread_mutex_unlock(&tpool->pool_mutex);
	return (true);
}
