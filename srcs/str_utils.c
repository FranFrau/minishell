#include "minishell.h"

char	*ft_strcdup(const char *src, char c)
{
	char	*str;
	int		len;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, src, len + 1);
	return (str);
}

char	*ft_charjoin(char *s1, char s2)
{
	size_t	i;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	str[i++] = s2;
	str[ft_strlen(s1) + 1] = '\0';
	free(s1);
	return (str);
}

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, src, len);
	return (str);
}

char	**ft_arrdup(char **src)
{
	int		i;
	char	**tmp;

	i = 0;
	while (src[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (src[++i])
		tmp[i] = ft_strdup(src[i]);
	tmp[i] = NULL;
	return (tmp);
}

void	ft_strappend(char **dst, char *to_append)
{
	int	i;

	i = -1;
	while (to_append[++i])
		*dst = ft_charjoin(*dst, to_append[i]);
}
