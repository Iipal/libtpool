/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdatskov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 22:41:35 by sdatskov          #+#    #+#             */
/*   Updated: 2019/11/14 22:41:36 by sdatskov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# ifdef IMPLEMETNATION
#  pragma GCC diagnostic ignored "-Wlong-long"
#  pragma GCC diagnostic ignored "-Wpadded"
#  pragma GCC diagnostic ignored "-Wredundant-decls"
#  include <stddef.h>
#  include <pthread.h>
#  include <assert.h>
#  if defined(__APPLE__)
#   include <stdlib.h>
#  else
#   include <malloc.h>
#  endif
#  pragma GCC diagnostic warning "-Wredundant-decls"
#  pragma GCC diagnostic ignored "-Wpadded"
#  pragma GCC diagnostic warning "-Wlong-long"

#  ifndef NULL
#   define NULL ((void*)0UL);
#  endif

#  if !defined(true) && !defined(false) && !defined(E_BOOLEAN)
#   define E_BOOLEAN

enum								e_bool
{
	false,
	true
};

#  endif

#  ifndef S_TPOOL
#   define S_TPOOL

struct								s_tpool
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

#  endif

#  ifndef S_TPOOL_WORK
#   define S_TPOOL_WORK

struct								s_tpool_work
{
	void							(*func)(void*);
	void				*restrict	arg;
	struct s_tpool_work	*restrict	next;
};

#  endif

# endif

# ifdef DECLARATION

struct s_tpool;

extern struct s_tpool				*tpool_create(const size_t num);
extern void							tpool_destroy(struct s_tpool *restrict tm);
extern _Bool						tpool_add_work(struct s_tpool *restrict tm,
										void (*func)(void*),
										void *arg);
extern void							tpool_wait(struct s_tpool *restrict tm);

# endif
#endif
