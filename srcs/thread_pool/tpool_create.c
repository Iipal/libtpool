/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshepele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:27:39 by dshepele          #+#    #+#             */
/*   Updated: 2019/11/14 21:27:39 by dshepele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(IMPLEMETNATION) && !defined(DECLARATION)
# define IMPLEMETNATION
# define DECLARATION
# include "thread_pool.h"
#endif

static struct s_tpool_work __attribute__((__nonnull__(1)))
	*tpool_work_get(struct s_tpool *restrict tm)
{
	struct s_tpool_work *restrict	work;

	if (!(work = tm->work_first))
		return (NULL);
	if (work->next == NULL)
	{
		tm->work_first = NULL;
		tm->work_last = NULL;
	}
	else
	{
		tm->work_first = work->next;
	}
	return (work);
}

static void __attribute__((,))
	*tpool_worker(struct s_tpool *restrict tm)
{
	struct s_tpool_work *restrict	work;

	while (-42)
	{
		pthread_mutex_lock(&(tm->work_mutex));
		if (tm->stop)
			break ;
		if (tm->work_first == NULL)
			pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));
		work = tpool_work_get(tm);
		tm->working_cnt++;
		pthread_mutex_unlock(&(tm->work_mutex));
		if (!!work)
			work->func(work->arg);
		if (!!work)
			free(work);
		pthread_mutex_lock(&(tm->work_mutex));
		if (!(tm->stop) && !(--(tm->working_cnt)) && !(tm->work_first))
			pthread_cond_signal(&(tm->working_cond));
		pthread_mutex_unlock(&(tm->work_mutex));
	}
	tm->thread_cnt--;
	pthread_cond_signal(&(tm->working_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	return (NULL);
}

struct s_tpool
	*tpool_create(const size_t num)
{
	struct s_tpool	*restrict	tm;
	pthread_t					thread;
	size_t						i;

	assert(!!num);
	assert((tm = (__typeof__(tm))(valloc(sizeof(*tm)))));
	*tm = __extension__((struct s_tpool){ .thread_cnt = num });
	pthread_mutex_init(&(tm->work_mutex), NULL);
	pthread_cond_init(&(tm->work_cond), NULL);
	pthread_cond_init(&(tm->working_cond), NULL);
	i = ~0UL;
	while (++i != num)
	{
		pthread_create(&thread, NULL, (void*(*)(void*))tpool_worker, tm);
		pthread_detach(thread);
	}
	return (tm);
}

#if defined(IMPLEMETNATION) && defined(DECLARATION)
# undef IMPLEMETNATION
# undef DECLARATION
#endif
