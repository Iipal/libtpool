#ifndef LIBTPOOL_S_WORK_H
# define LIBTPOOL_S_WORK_H

# if !(defined(LIBTPOOL_H) || defined(LIBTPOOL_INTERNAL))
#  error "do not include libtpool_s_work.h by yourself"
# endif

# ifndef S_WORK
#  define S_WORK

struct	s_work
{
	void	(*__nullable routine)(void *__restrict __nonnull);
	void	*__restrict __nullable arg;
};

# endif /* S_WORK */

#endif /* LIBTPOOL_S_WORK_H */
