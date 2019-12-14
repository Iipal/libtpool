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
(struct s_tpool *__restrict __nonnull tpool,
	void (*__nonnull work_routine)(void *__restrict __nonnull),
	void *__restrict __nonnull arg)
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
(struct s_tpool *__restrict __nonnull tpool,
struct s_work *__restrict __nonnull work)
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
