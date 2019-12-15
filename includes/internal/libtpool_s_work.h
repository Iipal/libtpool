#ifndef LIBTPOOL_S_WORK_H
# define LIBTPOOL_S_WORK_H

# if !(defined(LIBTPOOL_H) || defined(LIBTPOOL_INTERNAL))
#  error "do not include libtpool_s_work.h by yourself"
# endif

# include "libtpool_defs.h"

# ifndef S_WORK
#  define S_WORK

struct	s_work
{
	void	(*tp_Nullable routine)(void *tp_restrict tp_Nonnull);
	void	*tp_restrict tp_Nullable arg;
};

# endif /* S_WORK */

#endif /* LIBTPOOL_S_WORK_H */
