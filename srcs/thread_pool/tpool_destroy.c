/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshepele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:41:29 by dshepele          #+#    #+#             */
/*   Updated: 2019/11/14 21:41:30 by dshepele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(IMPLEMETNATION) && !defined(DECLARATION)
# define IMPLEMETNATION
# define DECLARATION
# include "thread_pool.h"
#endif

void __attribute__((__nonnull__(1)))
	tpool_destroy(struct s_tpool *restrict tm)
{
	struct s_tpool_work *restrict	work;
	struct s_tpool_work *restrict	work2;

	pthread_mutex_lock(&(tm->work_mutex));
	work = tm->work_first;
	while (!!work)
	{
		work2 = work->next;
		free(work);
		work = work2;
	}
	tm->stop = true;
	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));
	tpool_wait(tm);
	pthread_mutex_destroy(&(tm->work_mutex));
	pthread_cond_destroy(&(tm->work_cond));
	pthread_cond_destroy(&(tm->working_cond));
	free((void*)tm);
}

#if defined(IMPLEMETNATION) && defined(DECLARATION)
# undef IMPLEMETNATION
# undef DECLARATION
#endif
