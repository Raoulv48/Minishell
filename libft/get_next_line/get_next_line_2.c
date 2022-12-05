#include <stddef.h>

int	old_ternary(char **line, int ret, int flag)
{
	if (flag == 1)
	{
		if (*line == NULL)
			return (-1);
		else
			return (ret);
	}
	else
	{
		if (*line == NULL)
			return (-1);
		else
			return (1);
	}
}
