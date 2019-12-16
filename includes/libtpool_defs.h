#ifndef LIBTPOOL_DEFS_H
# define LIBTPOOL_DEFS_H

# if defined __linux__
#  include <sys/cdefs.h>

#  define tp_Nonnull _Nonnull
#  define tp_Nullable _Nullable

#  if defined __restrict
#   define tp_restrict __restrict
#  elif defined __restrict_arr
#   define tp_restrict __restrict_arr
#  else
#   define tp_restrict
#  endif

# elif defined __APPLE__

#  define tp_Nonnull __nonnull
#  define tp_Nullable __nullable
#  define tp_restrict __restrict

# else

#  define tp_Nonnull  /* unknown behavior on unknown system */
#  define tp_Nullable /* unknown behavior on unknown system */
#  define tp_restrict /* unknown behavior on unknown system */

# endif

#endif /* LIBTPOOL_DEFS_H */
