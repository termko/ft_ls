#include "libft.h"

intmax_t	ft_abs(intmax_t val)
{
	if (val < 0)
		return (-val);
	return (val);
}