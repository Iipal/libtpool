/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtpool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:18:17 by tmaluh            #+#    #+#             */
/*   Updated: 2019/12/11 20:30:59 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTPOOL_H
# define LIBTPOOL_H

# include <stddef.h>
# include <sys/types.h>
# include <stdbool.h>

struct s_tpool;

/*
** Creating the threads pool of 'threads_count' threads counts.
** All created threads in the pool are detached and waiting
**  until 'tpool_add_work' allocate a new 'work'.
*/
extern struct s_tpool	*tpool_create(const size_t threads_count);

/*
** Deleting all created threads and the tpool.
*/
extern void				tpool_destroy(struct s_tpool *restrict tpool);

/*
** Allocating new 'work'.
*/
extern _Bool			tpool_add_work(struct s_tpool *restrict tpool,
							void (*work_routine)(void*),
							void *arg);
/*
** Waiting until all threads in the pool done a work.
*/
extern void				tpool_wait(struct s_tpool *restrict tpool);

#endif
