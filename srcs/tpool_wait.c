/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:24:08 by tmaluh            #+#    #+#             */
/*   Updated: 2019/12/11 20:24:13 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtpool.h"

#define LIBTPOOL_INTERNAL
#include "libtpool_internal.h"
#undef LIBTPOOL_INTERNAL

void __attribute__((__nonnull__(1)))
	tpool_wait(struct s_tpool *restrict tpool)
{
	pthread_mutex_lock(&(tpool->work_mutex));
	while (-42)
		if ((!(tpool->stop) && !!(tpool->working_cnt))
		|| (!!(tpool->stop) && !!(tpool->thread_cnt)))
			pthread_cond_wait(&(tpool->working_cond), &(tpool->work_mutex));
		else
			break ;
	pthread_mutex_unlock(&(tpool->work_mutex));
}
