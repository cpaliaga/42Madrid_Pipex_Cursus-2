/* UTIL_STR.C */
#include "pipex.h"

void	ft_bzero(void *s, size_t n)
{
	char	*mem;

	mem = s;
	while (n-- > 0)
		*mem++ = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	len;

	len = (count * size);
	if (len < count && len < size)
		return (NULL);
	if (len > SIZE_MAX)
		return (NULL);
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = 0;
	while (*(s1 + len) != '\0')
		len++;
	i = 0;
	copy = (char *)ft_calloc((len + 1), sizeof(char));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		*(copy + i) = *(s1 + i);
		i++;
	}
	*(copy + i) = '\0';
	return (copy);
}
