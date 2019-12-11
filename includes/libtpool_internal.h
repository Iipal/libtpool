/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtpool_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:17:57 by tmaluh            #+#    #+#             */
/*   Updated: 2019/12/11 20:32:23 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTPOOL_INTERNAL_H
# define LIBTPOOL_INTERNAL_H

# ifndef LIBTPOOL_INTERNAL
#  error "include libtpool.h only"
# endif

# include <pthread.h>
# include <assert.h>

# if defined(__APPLE__)
#  include <stdlib.h>
# else
#  include <malloc.h>
# endif

# ifndef S_TPOOL_WORK
#  define S_TPOOL_WORK

struct					s_tpool_work
{
	void							(*func)(void*);
	void *restrict					arg;
	struct s_tpool_work *restrict	next;
};

# endif

# ifndef S_TPOOL
#  define S_TPOOL

struct					s_tpool
{
	struct s_tpool_work *restrict	work_first;
	struct s_tpool_work *restrict	work_last;
	pthread_mutex_t					work_mutex;
	pthread_cond_t					work_cond;
	pthread_cond_t					working_cond;
	size_t							working_cnt;
	size_t							thread_cnt;
	_Bool							stop;
	char							stub[7];
};

# endif

#endif
