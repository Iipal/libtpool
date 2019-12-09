#include <unistd.h>
#include "tpool.h"

void	cyka(void *arg)
{
	write(1, arg, 5);
}

int		main(void)
{
	const size_t				tcount = 64UL;
	struct s_tpool	*restrict	new_tpool;
	size_t						i;

	new_tpool = tpool_create(tcount);
	i = ~0UL;
	while (++i != tcount)
		tpool_add_work(new_tpool, cyka, "cyka\n");
	tpool_wait(new_tpool);
	tpool_destroy(new_tpool);
}
