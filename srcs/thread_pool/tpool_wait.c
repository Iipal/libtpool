/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshepele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:42:54 by dshepele          #+#    #+#             */
/*   Updated: 2019/11/14 21:42:55 by dshepele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(IMPLEMETNATION) && !defined(DECLARATION)
# define IMPLEMETNATION
# define DECLARATION
# include "thread_pool.h"
#endif

void __attribute__((__nonnull__(1)))
	tpool_wait(struct s_tpool *restrict tm)
{
	pthread_mutex_lock(&(tm->work_mutex));
	while (-42)
	{
		if ((!(tm->stop) && !!(tm->working_cnt))
		|| (!!(tm->stop) && !!(tm->thread_cnt)))
		{
			pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
		}
		else
		{
			break ;
		}
	}
	pthread_mutex_unlock(&(tm->work_mutex));
}

#if defined(IMPLEMETNATION) && defined(DECLARATION)
# undef IMPLEMETNATION
# undef DECLARATION
#endif
